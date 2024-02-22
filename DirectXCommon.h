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
    //�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	ID3D12Device*GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

    
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

