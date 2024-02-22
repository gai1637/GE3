#pragma once
#include<wrl.h>
#define DIRECTION_VERSION 0x0800
#include<dinput.h>
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

