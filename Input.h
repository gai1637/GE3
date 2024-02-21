#pragma once
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
private:
	ComPtr<IDirectInputDevice8> keyboard;
};

