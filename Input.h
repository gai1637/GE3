﻿#pragma once
#include<Windows.h>
#include<wrl.h>
#define DIRECTION_VERSION 0x0800
#include<dinput.h>


class Input
{
public:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();
/// <summary>
/// キーの押下をチェック
/// </summary>
/// <param name="keyNumber">キー番号(DIK_0等)</param>
/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);
	/// <summary>
/// キーのトリガーをチェック
/// </summary>
/// <param name="keyNumber">キー番号(DIK_0等)</param>
/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

private:
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	ComPtr<IDirectInput8> directInput;
};

