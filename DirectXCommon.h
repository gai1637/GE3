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
    //�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

    void ImGuiUpdate();

    void EndImGui();

	ID3D12Device*GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }
    //FPS�Œ菉����
    void InitializeFixFPS();
    //FPS�Œ�X�V
    void UpdateFixFPS();


   /* ComPtr<IDxcBlob> CompilShader(
        const std::wstring& filePath,
        const wchar_t* profile
    );*/

    ComPtr<ID3D12Resource> CreateTexture(const DirectX::TexMetadata& metadata);
    ID3D12DescriptorHeap* CreateDescriptorHeap(
    ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
    
private:
    //�f�o�C�X
	void DeviceInitialize();
    //�R�}���h
	void CommandInitialize();
    //�X���b�v�`�F�[��
	void SwapChainInitialize();
    //�[�x�o�b�t�@
	void DepthBufferInitialize();
    //�����_�[�^�[�Q�b�g
	void RenderTargetInitialize();
    //�t�F���X
	void FenceInitialize();
    //ImGui
    void ImGuiInitialize();
private:
     // �f�X�N���v�^�q�[�v�̐ݒ�
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
    // �[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    // �o�b�N�o�b�t�@
    std::vector<ComPtr<ID3D12Resource>> backBuffers;
	D3D12_RESOURCE_BARRIER barrierDesc{};
    // �t�F���X�̐���
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceVal = 0;
    // ���\�[�X����
    ComPtr<ID3D12Resource> depthBuff;
    // �����_�[�^�[�Q�b�g�r���[�̐ݒ�
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

