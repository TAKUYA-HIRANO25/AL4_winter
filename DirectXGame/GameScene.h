#pragma once

#include <KamataEngine.h>
#include "Player.h"
#include "Enemy.h"
#include "Skydom.h"

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

private: // メンバ変数

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

	Player* player_ = nullptr;
	Skydom* skydome_ = nullptr;
	Enemy* enemy_ = nullptr;

	KamataEngine::Model* enemyModel_ = nullptr;
	KamataEngine::Camera* enemyCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
