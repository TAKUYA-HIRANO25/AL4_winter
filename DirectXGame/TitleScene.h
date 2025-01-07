#pragma once
#include <KamataEngine.h>
#include "Fade.h"
#include "Skydom.h"

class TitleScene {
public:
	// シーンのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::Camera* camera_;
	KamataEngine::Model* TitleModel_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* modelSkydome_ = nullptr;
	Skydom* skydome_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	// 画面フェード
	Fade* fade_ = nullptr;

	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	KamataEngine::ObjectColor objColor_;

	//BGM
	uint32_t TitleSound_ = 0;
	uint32_t TitleHandle_ = 0;
	//決定音
	uint32_t DecisionSound_ = 0;
	uint32_t DecisionHandle_ = 0;

};