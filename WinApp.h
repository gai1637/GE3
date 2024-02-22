#pragma once
#include<Windows.h>
#include<wrl.h>
#define DIRECTION_VERSION 0x0800
#include<dinput.h>
#include<stdint.h>
class WinApp
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	 // ウィンドウサイズ
    static const int32_t window_height = 720;  // 縦幅
    static const int32_t window_width = 1280;  // 横幅

public:
	void Initialize();
	void Draw();
	//getter
	HWND GetHwnd()const { return hwnd; }
	HINSTANCE GetHinstance()const { return wc.hInstance; }
	void Finalize();
private:
	// ウィンドウオブジェクトの生成
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
    WNDCLASS wc{};
};

