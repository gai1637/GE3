#include "Input.h"
#include<cassert>
using namespace Microsoft::WRL;


void Input::Initialize(WinApp*winApp)
{
    winApp_ = winApp;

    HRESULT result;
    // DirectInputの初期化
    result = DirectInput8Create(
        winApp_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイスの生成
    
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // 排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(
       winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
   //keyPreの中にkeyの情報をコピーする
    memcpy(keyPre, key, sizeof(key));

   // キーボード情報の取得開始
    keyboard->Acquire();
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    //任意のボタンが押されているか
    if (key[keyNumber]) {
        return true;
    }
    //任意のボタンが押されていなかったとき
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //任意のボタンが押されているか
    if (key[keyNumber] && keyPre[keyNumber]==0) {
        return true;
    }
    //任意のボタンが押されていなかったとき
    return false;
}
