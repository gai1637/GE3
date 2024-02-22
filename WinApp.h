#pragma once
#include<Windows.h>
#include<wrl.h>
#define DIRECTION_VERSION 0x0800
#include<dinput.h>

class WinApp
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	void Initialize();
	void Draw();
};

