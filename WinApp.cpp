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
    // ���b�Z�[�W�����ăQ�[���ŗL�̏������s��
    switch (msg) {
        // �E�B���h�E���j�����ꂽ
    case WM_DESTROY:
        // OS�ɑ΂��āA�A�v���̏I����`����
        PostQuitMessage(0);
        return 0;
    }

    // �W���̃��b�Z�[�W�������s��
    return DefWindowProc(hwnd, msg, wparam, lparam);

}

void WinApp::Initialize()
{
    HRESULT result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	 
   
    wc.lpfnWndProc = (WNDPROC)WindowProc; // �E�B���h�E�v���V�[�W����ݒ�
    wc.lpszClassName = L"DirectXGame"; // �E�B���h�E�N���X��
    wc.hInstance = GetModuleHandle(nullptr); // �E�B���h�E�n���h��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

    // �E�B���h�E�N���X��OS�ɓo�^����
    RegisterClass(&wc);

   
     // �E�B���h�E�T�C�Y{ X���W Y���W ���� �c�� }
    RECT wrc = { 0, 0, window_width, window_height };
    // �����ŃT�C�Y��␳����
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

     // �E�B���h�E�I�u�W�F�N�g�̐���
    hwnd = CreateWindow(
        wc.lpszClassName, // �N���X��
        L"DirectXGame",         // �^�C�g���o�[�̕���
        WS_OVERLAPPEDWINDOW,        // �W���I�ȃE�B���h�E�X�^�C��
        CW_USEDEFAULT,              // �\��X���W�iOS�ɔC����j
        CW_USEDEFAULT,              // �\��Y���W�iOS�ɔC����j
        wrc.right - wrc.left,       // �E�B���h�E����
        wrc.bottom - wrc.top,   // �E�B���h�E�c��
        nullptr,                // �e�E�B���h�E�n���h��
        nullptr,                // ���j���[�n���h��
        wc.hInstance,            // �Ăяo���A�v���P�[�V�����n���h��
        nullptr);               // �I�v�V����

    // �E�B���h�E��\����Ԃɂ���
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
