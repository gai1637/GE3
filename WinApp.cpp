#include "WinApp.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"externals/imgui/imgui.h"
#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT Imgui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (Imgui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
        return true;
    }
    // メッセージ応じてゲーム固有の処理を行う
    switch (msg) {
        // ウィンドウが破棄された
    case WM_DESTROY:
        // OSに対して、アプリの終了を伝える
        PostQuitMessage(0);
        return 0;
    }

    // 標準のメッセージ処理を行う
    return DefWindowProc(hwnd, msg, wparam, lparam);

}

void WinApp::Initialize()
{
    HRESULT result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	 
   
    wc.lpfnWndProc = WindowProc; // ウィンドウプロシージャを設定
    wc.lpszClassName = L"DirectXGame"; // ウィンドウクラス名
    wc.hInstance = GetModuleHandle(nullptr); // ウィンドウハンドル
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // カーソル指定

    // ウィンドウクラスをOSに登録する
    RegisterClass(&wc);

   
     // ウィンドウサイズ{ X座標 Y座標 横幅 縦幅 }
    RECT wrc = { 0, 0, window_width, window_height };
    // 自動でサイズを補正する
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

     // ウィンドウオブジェクトの生成
    hwnd = CreateWindow(
        wc.lpszClassName, // クラス名
        L"DirectXGame",         // タイトルバーの文字
        WS_OVERLAPPEDWINDOW,        // 標準的なウィンドウスタイル
        CW_USEDEFAULT,              // 表示X座標（OSに任せる）
        CW_USEDEFAULT,              // 表示Y座標（OSに任せる）
        wrc.right - wrc.left,       // ウィンドウ横幅
        wrc.bottom - wrc.top,   // ウィンドウ縦幅
        nullptr,                // 親ウィンドウハンドル
        nullptr,                // メニューハンドル
        wc.hInstance,            // 呼び出しアプリケーションハンドル
        nullptr);               // オプション

    // ウィンドウを表示状態にする
    ShowWindow(hwnd, SW_SHOW);

}

void WinApp::Draw()
{

}

void WinApp::Finalize()
{
    CloseWindow(hwnd);
    CoUninitialize();
}

bool WinApp::ProcessMessage()
{
    MSG msg{}; 
     // メッセージがある？
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg); // キー入力メッセージの処理
            DispatchMessage(&msg); // プロシージャにメッセージを送る
        }

        // ✖ボタンで終了メッセージが来たらゲームループを抜ける
        if (msg.message == WM_QUIT) {
            return true;
        }

    return false;
}
