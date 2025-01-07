#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete fade_;

}

void TitleScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_.z = -40;
	camera_ = new Camera;
	camera_->Initialize();
	camera_->farZ = 1500.0f;
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);
	TitleModel_ = Model::CreateFromOBJ("Title", true);
	skydome_ = new Skydom();
	skydome_->Initialize(modelSkydome_, camera_);
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
	objColor_.Initialize();
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);
	TitleSound_ = audio_->LoadWave("BGM/Title.wav");
	TitleHandle_ = audio_->PlayWave(TitleSound_, true);
	DecisionSound_ = audio_->LoadWave("BGM/Decision.mp3");

}

void TitleScene::Update() {
	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			phase_ = Phase::kMain;
			DecisionHandle_ = audio_->PlayWave(DecisionSound_, false);
		}
		camera_->UpdateMatrix();
		worldTransform_.UpdateMatrix();
		fade_->Update();
		break;
	case TitleScene::Phase::kMain:
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = Phase::kFadeOut;
		}
		break;
	case TitleScene::Phase::kFadeOut:
		
		audio_->StopWave(TitleHandle_);
		finished_ = true;
		break;
	default:
		break;
	}
}

void TitleScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに背景スプライトの処理を追加できる
	/// </summary>


	// スプライト処理後描画
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	TitleModel_->Draw(worldTransform_, *camera_, &objColor_);
	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	///< summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	/// 
	fade_->Draw(commandList);
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}