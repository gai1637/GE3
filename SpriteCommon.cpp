#include "SpriteCommon.h"
#include<cassert>
#include<d3dcompiler.h>
void SpriteCommon::Initialize(DirectXCommon* dxCommon)
{
    dxCommon_ = dxCommon;
    CreateBlob();
    CreateRootsignature();
    CreatePaipline();
}

void SpriteCommon::SpritePreDraw()
{
    // パイプラインステートとルートシグネチャの設定コマンド
        dxCommon_->GetCommandList()->SetPipelineState(pipelineState.Get());
        dxCommon_->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
         // プリミティブ形状の設定コマンド
        dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

}

void SpriteCommon::CreateRootsignature()
{
   // ルートパラメータの設定
    D3D12_ROOT_PARAMETER rootParams[3] = {};
    // 定数バッファ0番
    rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;   // 種類
    rootParams[0].Descriptor.ShaderRegister = 0;                   // 定数バッファ番号
    rootParams[0].Descriptor.RegisterSpace = 0;                    // デフォルト値
    rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;  // 全てのシェーダから見える
    // テクスチャレジスタ0番
    rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;   //種類
    rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;
    rootParams[1].DescriptorTable.NumDescriptorRanges = 1;              //デスクリプタレンジ数
    rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;       //全てのシェーダから見える
    // 定数バッファ1番
    rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;   // 種類
    rootParams[2].Descriptor.ShaderRegister = 1;                   // 定数バッファ番号
    rootParams[2].Descriptor.RegisterSpace = 0;                    // デフォルト値
    rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;  // 全てのシェーダから見える
     // テクスチャサンプラーの設定
    D3D12_STATIC_SAMPLER_DESC samplerDesc{};
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //横繰り返し（タイリング）
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //縦繰り返し（タイリング）
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //奥行繰り返し（タイリング）
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;  //ボーダーの時は黒
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;                   //全てリニア補間
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;                                 //ミップマップ最大値
    samplerDesc.MinLOD = 0.0f;                                              //ミップマップ最小値
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;           //ピクセルシェーダからのみ使用可能

    // ルートシグネチャの設定
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    rootSignatureDesc.pParameters = rootParams; //ルートパラメータの先頭アドレス
    rootSignatureDesc.NumParameters = _countof(rootParams);        //ルートパラメータ数
    rootSignatureDesc.pStaticSamplers = &samplerDesc;
    rootSignatureDesc.NumStaticSamplers = 1;
    // ルートシグネチャのシリアライズ
    ID3DBlob* rootSigBlob = nullptr;
    
    result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
    assert(SUCCEEDED(result));
    result = dxCommon_->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
    assert(SUCCEEDED(result));
    rootSigBlob->Release();
}

void SpriteCommon::CreatePaipline()
{
    // 頂点レイアウト
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { // xyz座標(1行で書いたほうが見やすい)
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
        { // 法線ベクトル(1行で書いたほうが見やすい)
            "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
        { // uv座標(1行で書いたほうが見やすい)
            "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
    };
    // シェーダーの設定
    pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
    pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
    pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
    pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
    // サンプルマスクの設定
    pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
    // ラスタライザの設定
    pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // カリングしない
    pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;  // 背面をカリング
    pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
    //pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // ワイヤーフレーム
    pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に
    // ブレンドステート
    pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA全てのチャンネルを描画
    // pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    // レンダーターゲットのブレンド設定
    D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
    blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画
    blenddesc.BlendEnable = true;                   // ブレンドを有効にする
    blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;    // 加算
    blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;      // ソースの値を100% 使う
    blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;    // デストの値を  0% 使う

    // 半透明合成
    blenddesc.BlendOp = D3D12_BLEND_OP_ADD;             // 加算
    blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;         // ソースのアルファ値
    blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;    // 1.0f-ソースのアルファ値

    // デプスステンシルステートの設定
    pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テストを行う
    pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
    pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
    pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

    // 頂点レイアウトの設定
    pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
    pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
    // 図形の形状設定
    pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    // その他の設定
    pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
    pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
    pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

   
    descriptorRange.NumDescriptors = 1;         //一度の描画に使うテクスチャが1枚なので1
    descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    descriptorRange.BaseShaderRegister = 0;     //テクスチャレジスタ0番
    descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    
   
     // パイプラインにルートシグネチャをセット
    pipelineDesc.pRootSignature = rootSignature.Get();
    
    result = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
    assert(SUCCEEDED(result));

}

void SpriteCommon::CreateBlob()
{
    
    // 頂点シェーダの読み込みとコンパイル
    result = D3DCompileFromFile(
        L"BasicVS.hlsl",  // シェーダファイル名
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
        "main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
        0,
        &vsBlob, &errorBlob);
    // エラーなら
    if (FAILED(result)) {
        // errorBlobからエラー内容をstring型にコピー
        std::string error;
        error.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            error.begin());
        error += "\n";
        // エラー内容を出力ウィンドウに表示
        OutputDebugStringA(error.c_str());
        assert(0);
    }

    // ピクセルシェーダの読み込みとコンパイル
    result = D3DCompileFromFile(
        L"BasicPS.hlsl",   // シェーダファイル名
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
        "main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
        0,
        &psBlob, &errorBlob);
    // エラーなら
    if (FAILED(result)) {
        // errorBlobからエラー内容をstring型にコピー
        std::string error;
        error.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            error.begin());
        error += "\n";
        // エラー内容を出力ウィンドウに表示
        OutputDebugStringA(error.c_str());
        assert(0);
    }

    

    
    
}
