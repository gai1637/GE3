#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"Sprite.h"
#include"SpriteCommon.h"

#include"ImGuiManager.h"
#include<vector>

#include"TextureManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    //ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;
#pragma region WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();
#pragma endregion

#pragma region DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);
#pragma endregion
    //Input生成、初期化
    input_ = new Input();
    input_->Initialize(winApp_);

    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp_->GetHwnd(), dxCommon_);

    //スプライトコモン
    SpriteCommon* common = new SpriteCommon();
    common->Initialize(dxCommon_);

    TextureManager::Getinstance()->Initialize(dxCommon_);
    TextureManager::Getinstance()->LoadTexture(L"Resources/mario.jpg");
        TextureManager::Getinstance()->LoadTexture(L"Resources/reimu.png");

   std::vector<Sprite*> sprite ;
    for (int i = 0; i < 1; i++) {
        Sprite* temp = new Sprite();
        if (i % 2 == 0) temp->Initialize(common, L"Resources/mario.jpg");
        else if (i % 2 == 1)temp->Initialize(common, { L"Resources/reimu.png" });
        temp->SetPosition({400,200 });
        sprite.push_back(temp);
    }

    // ゲームループ
    while (true) {
        if (winApp_->Update() == true) {
            break;
      }
        ImGuiManager::NewFrame();
        imgui->ShowDemo();

        input_->Update();

    /*    DirectX::XMFLOAT2 pos = sprite->GetPosition();
        pos.x += 0.01f;
        sprite->SetPosition(pos);

        float rot = sprite->GetRotation();
        rot += 0.005f;
        sprite->SetRotation(rot);

        DirectX::XMFLOAT4 color = sprite->GetColor();
        color.x -= 0.01f;
        if (color.x < 0)
        {
            color.x = 1.0f;
        }
        sprite->SetColor(color);

        DirectX::XMFLOAT2 size = sprite->GetSize();
        size.y += 0.01f;
        sprite->SetSize(size);*/

        for (int i = 0; i < 1; i++)
        {
            sprite[i]->Update();
        }

        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();
        common->SpritePreDraw();

        for (int i = 0; i < 1; i++) {
            sprite[i]->Draw();
        }

        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();

        // DirectX毎フレーム処理　ここまで

    }

    //for (int i = 0; i < 5; i++) {
    //    delete sprite[i];
    //}
    TextureManager::Getinstance()->Finalize();
    delete common;
    delete imgui;
    delete input_;
    delete dxCommon_;
    winApp_->Finalize();
    delete winApp_;
   

    return 0;
}
