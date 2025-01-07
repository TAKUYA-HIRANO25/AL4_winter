#pragma once

#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <audio/Audio.h>
#include <input/Input.h>
#include <math/Vector3.h>
#include "PlayerBullet.h"
#include <list>

class Player {
public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	Player();

	/// <summary>
	/// 初期化
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Rotate();

	void Attack();

	KamataEngine::Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	bool IsDead() const { return isDead_; }

private: // メンバ変数
	KamataEngine::Audio* audio_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* bulletModel_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Input* input_ = nullptr;

	const float kMoveX = 34;
	const float kMoveY = 18;

	std::list<PlayerBullet*> bullets_;
	int bulletTime = 0;
	int bulletFlag = 0;

	float PlayerHP = 5.0f;
	bool isDead_ = false;

	//SE
	uint32_t ShotSound_ = 0;
	uint32_t ShotHandle_ = 0;
};