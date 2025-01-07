#pragma once

#include <KamataEngine.h>
#include "Player.h"
#include "Enemy.h"
#include "Skydom.h"
#include "Fade.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void checkAllcollisions();

	bool IsFinished() const { return finished_; }

	void ChangePhase();

private: // メンバ変数
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::ObjectColor objColor_;
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	KamataEngine::Model* modelClear_ = nullptr;
	KamataEngine::Model* modelOver_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

	Player* player_ = nullptr;
	Skydom* skydome_ = nullptr;
	Enemy* enemy_ = nullptr;

	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::Camera* enemyCamera_ = nullptr;

	//フェード
	Fade* fade = nullptr;

	// 終了フラグ
	bool finished_ = false;

	// ゲームのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
		kPlay,
		kDeath,
		kClear,
	};
	// ゲームの現在のフェーズ
	Phase phase_;

	//BGM
	uint32_t GameSound_ = 0;
	uint32_t GameHandle_ = 0;
	// 決定音
	uint32_t DecisionSound_ = 0;
	uint32_t DecisionHandle_ = 0;
	//テクスチャー
	uint32_t texturOperation = 0;
	KamataEngine::Sprite* spriteOperation = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
