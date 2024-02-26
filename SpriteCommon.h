#pragma once
#include<wrl.h>
#include<dxgi1_6.h>
#include<d3d12.h>
using namespace Microsoft::WRL;
#include"DirectXCommon.h"

class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxCommon);
	DirectXCommon* GetDxCommon()const { return dxCommon_; }
	void SpritePreDraw();
private:
	//ルートシグネチャの生成
	void CreateRootsignature();
	//グラフィックスパイプライン
	void CreatePaipline();
	void CreateBlob();
private:
	 // ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;
	 // ルートパラメータの設定
    D3D12_ROOT_PARAMETER rootParams[3] = {};
	DirectXCommon* dxCommon_;
	HRESULT result;
	// グラフィックスパイプライン設定
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// パイプランステートの生成
    ComPtr<ID3D12PipelineState> pipelineState;
	 // デスクリプタレンジの設定
    D3D12_DESCRIPTOR_RANGE descriptorRange{};
	ComPtr<ID3DBlob> vsBlob = nullptr; // 頂点シェーダオブジェクト
    ComPtr<ID3DBlob> psBlob = nullptr; // ピクセルシェーダオブジェクト
    ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

};

