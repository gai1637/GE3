#pragma once
#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<vector>
#include"WinApp.h"

class DirectXCommon
{
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	void Initialize(WinApp*winApp);

	//描画
	void PreDraw();
	void PostDraw();

	//Getter
	ID3D12Device* GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc(){return swapChainDesc; }

	D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc() { return rtvDesc; }

	ID3D12DescriptorHeap* GetSrvDescriptorHeap() { return srvDescriptorHeap.Get(); }

private:
	//デバイス
	void DeviceInitialize();
	//コマンド
	void CommandInitialize();
	//スワップチェーン
	void SwapChainInitialize();
	//レンダーターゲット
	void RenderTargetInitialize();
	//震度バッファ
	void DepthBufferInitialize();
	//フェンス
	void FenceInitialize();

	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripots,bool shaderVisible);

public:
	static const uint32_t kMaxSRVCount;

private:
	WinApp* winApp = nullptr;

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7>dxgiFactory;

	ComPtr<ID3D12CommandAllocator>commandAllocator;
    ComPtr<ID3D12GraphicsCommandList>commandList;
    ComPtr<ID3D12CommandQueue>commandQueue;

   DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ComPtr<IDXGISwapChain4> swapChain;

	 D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap>rtvHeap;
	 std::vector<ComPtr<ID3D12Resource>>backBuffers;

	  ComPtr<ID3D12Resource>depthBuff;
	  D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	   ComPtr<ID3D12DescriptorHeap>dsvHeap;

	   ComPtr<ID3D12Fence>fence;
	   UINT64 fenceVal = 0;

	   D3D12_RESOURCE_BARRIER barrierDesc{};

	     // レンダーターゲットビューの設定
        D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	   ComPtr<ID3D12DescriptorHeap>rtvDesctiptorHeap;

	   ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap;
};

