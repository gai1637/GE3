#pragma once
#include<wrl.h>
#include<dxgi1_6.h>
#include<d3d12.h>
#include<vector>
#include<chrono>
#include"WinApp.h"
using namespace Microsoft::WRL;
class DirectXCommon
{
public:
	
	void Initialize(WinApp* winApp);
    //描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	ID3D12Device*GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

    
private:
    //デバイス
	void DeviceInitialize();
    //コマンド
	void CommandInitialize();
    //スワップチェーン
	void SwapChainInitialize();
    //深度バッファ
	void DepthBufferInitialize();
    //レンダーターゲット
	void RenderTargetInitialize();
    //フェンス
	void FenceInitialize();
private:
     // デスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
    // 深度ビュー用デスクリプタヒープ作成
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    // バックバッファ
    std::vector<ComPtr<ID3D12Resource>> backBuffers;
	D3D12_RESOURCE_BARRIER barrierDesc{};
    // フェンスの生成
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceVal = 0;

    ComPtr<ID3D12Device> device;
    ComPtr<IDXGIFactory7> dxgiFactory;
    ComPtr<IDXGISwapChain4> swapChain;
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;

   
    WinApp* winApp_ = nullptr;
};

