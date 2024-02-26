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
    // �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
        dxCommon_->GetCommandList()->SetPipelineState(pipelineState.Get());
        dxCommon_->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
         // �v���~�e�B�u�`��̐ݒ�R�}���h
        dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

}

void SpriteCommon::CreateRootsignature()
{
   // ���[�g�p�����[�^�̐ݒ�
    D3D12_ROOT_PARAMETER rootParams[3] = {};
    // �萔�o�b�t�@0��
    rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;   // ���
    rootParams[0].Descriptor.ShaderRegister = 0;                   // �萔�o�b�t�@�ԍ�
    rootParams[0].Descriptor.RegisterSpace = 0;                    // �f�t�H���g�l
    rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;  // �S�ẴV�F�[�_���猩����
    // �e�N�X�`�����W�X�^0��
    rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;   //���
    rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;
    rootParams[1].DescriptorTable.NumDescriptorRanges = 1;              //�f�X�N���v�^�����W��
    rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;       //�S�ẴV�F�[�_���猩����
    // �萔�o�b�t�@1��
    rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;   // ���
    rootParams[2].Descriptor.ShaderRegister = 1;                   // �萔�o�b�t�@�ԍ�
    rootParams[2].Descriptor.RegisterSpace = 0;                    // �f�t�H���g�l
    rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;  // �S�ẴV�F�[�_���猩����
     // �e�N�X�`���T���v���[�̐ݒ�
    D3D12_STATIC_SAMPLER_DESC samplerDesc{};
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //���J��Ԃ��i�^�C�����O�j
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //�c�J��Ԃ��i�^�C�����O�j
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;                 //���s�J��Ԃ��i�^�C�����O�j
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;  //�{�[�_�[�̎��͍�
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;                   //�S�ă��j�A���
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;                                 //�~�b�v�}�b�v�ő�l
    samplerDesc.MinLOD = 0.0f;                                              //�~�b�v�}�b�v�ŏ��l
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;           //�s�N�Z���V�F�[�_����̂ݎg�p�\

    // ���[�g�V�O�l�`���̐ݒ�
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    rootSignatureDesc.pParameters = rootParams; //���[�g�p�����[�^�̐擪�A�h���X
    rootSignatureDesc.NumParameters = _countof(rootParams);        //���[�g�p�����[�^��
    rootSignatureDesc.pStaticSamplers = &samplerDesc;
    rootSignatureDesc.NumStaticSamplers = 1;
    // ���[�g�V�O�l�`���̃V���A���C�Y
    ID3DBlob* rootSigBlob = nullptr;
    
    result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
    assert(SUCCEEDED(result));
    result = dxCommon_->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
    assert(SUCCEEDED(result));
    rootSigBlob->Release();
}

void SpriteCommon::CreatePaipline()
{
    // ���_���C�A�E�g
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        { // xyz���W(1�s�ŏ������ق������₷��)
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
        { // �@���x�N�g��(1�s�ŏ������ق������₷��)
            "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
        { // uv���W(1�s�ŏ������ق������₷��)
            "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
        },
    };
    // �V�F�[�_�[�̐ݒ�
    pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
    pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
    pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
    pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
    // �T���v���}�X�N�̐ݒ�
    pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
    // ���X�^���C�U�̐ݒ�
    pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // �J�����O���Ȃ�
    pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;  // �w�ʂ��J�����O
    pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
    //pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; // ���C���[�t���[��
    pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����
    // �u�����h�X�e�[�g
    pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA�S�Ẵ`�����l����`��
    // pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    // �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
    D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
    blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��
    blenddesc.BlendEnable = true;                   // �u�����h��L���ɂ���
    blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;    // ���Z
    blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;      // �\�[�X�̒l��100% �g��
    blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;    // �f�X�g�̒l��  0% �g��

    // ����������
    blenddesc.BlendOp = D3D12_BLEND_OP_ADD;             // ���Z
    blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;         // �\�[�X�̃A���t�@�l
    blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;    // 1.0f-�\�[�X�̃A���t�@�l

    // �f�v�X�X�e���V���X�e�[�g�̐ݒ�
    pipelineDesc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g���s��
    pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
    pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
    pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g

    // ���_���C�A�E�g�̐ݒ�
    pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
    pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
    // �}�`�̌`��ݒ�
    pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    // ���̑��̐ݒ�
    pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
    pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
    pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

   
    descriptorRange.NumDescriptors = 1;         //��x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
    descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    descriptorRange.BaseShaderRegister = 0;     //�e�N�X�`�����W�X�^0��
    descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    
   
     // �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
    pipelineDesc.pRootSignature = rootSignature.Get();
    
    result = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
    assert(SUCCEEDED(result));

}

void SpriteCommon::CreateBlob()
{
    
    // ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"BasicVS.hlsl",  // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &vsBlob, &errorBlob);
    // �G���[�Ȃ�
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string error;
        error.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            error.begin());
        error += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(error.c_str());
        assert(0);
    }

    // �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"BasicPS.hlsl",   // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0,
        &psBlob, &errorBlob);
    // �G���[�Ȃ�
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string error;
        error.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            error.begin());
        error += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(error.c_str());
        assert(0);
    }

    

    
    
}
