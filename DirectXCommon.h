#pragma once
#include<wrl.h>
#include<dxgi1_6.h>
#include<d3d12.h>
#include<vector>
#include<chrono>
#include"WinApp.h"
#include<dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include<string>
#include <DirectXTex.h>
#include<memory>
#include<chrono>
using namespace Microsoft::WRL;
HRESULT Present(
UINT SyncInterval,
UINT flags
);
class DirectXCommon
{
public:
	
	void Initialize(WinApp* winApp);
    //描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

    void ImGuiUpdate();

    void EndImGui();

	ID3D12Device*GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }
    //FPS固定初期化
    void InitializeFixFPS();
    //FPS固定更新
    void UpdateFixFPS();


   /* ComPtr<IDxcBlob> CompilShader(
        const std::wstring& filePath,
        const wchar_t* profile
    );*/

    ComPtr<ID3D12Resource> CreateTexture(const DirectX::TexMetadata& metadata);
    ID3D12DescriptorHeap* CreateDescriptorHeap(
    ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
    
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
    //ImGui
    void ImGuiInitialize();
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
    // リソース生成
    ComPtr<ID3D12Resource> depthBuff;
    // レンダーターゲットビューの設定
    D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

    ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;

    ComPtr<ID3D12Device> device;
    ComPtr<IDXGIFactory7> dxgiFactory;
    ComPtr<IDXGISwapChain4> swapChain;
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;

   
    WinApp* winApp_ = nullptr;
    std::chrono::steady_clock::time_point reference_;
};

