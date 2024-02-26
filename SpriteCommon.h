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
	//���[�g�V�O�l�`���̐���
	void CreateRootsignature();
	//�O���t�B�b�N�X�p�C�v���C��
	void CreatePaipline();
	void CreateBlob();
private:
	 // ���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;
	 // ���[�g�p�����[�^�̐ݒ�
    D3D12_ROOT_PARAMETER rootParams[3] = {};
	DirectXCommon* dxCommon_;
	HRESULT result;
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// �p�C�v�����X�e�[�g�̐���
    ComPtr<ID3D12PipelineState> pipelineState;
	 // �f�X�N���v�^�����W�̐ݒ�
    D3D12_DESCRIPTOR_RANGE descriptorRange{};
	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g

};

