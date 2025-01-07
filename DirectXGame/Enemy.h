#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include "3d/Camera.h"
#include <math/Vector3.h>
#include "EnemyBullet.h"
#include <audio/Audio.h>
#include <list>

enum class Phase {
	Approach,
	Leave,
};

class Player;

class Enemy {
public:

	Enemy();

	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Fire();

	static const int kFireInterval = 90;

	static const int kMoveInterval = 360;

	void FireTime();

	void MoveTime();

	void setPlayer(Player* player) { player_ = player; }

	KamataEngine::Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	bool IsDead() const { return isDead_; }

private:
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* bulletModel_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Vector3 velocity_;

	Phase phase_ = Phase::Approach;

	std::list<EnemyBullet*> bullets_;

	int32_t Time = 0;

	KamataEngine::Vector3 move = { 0.2f,0.0f,0.0f };

	int32_t moveTime = 0;

	Player* player_ = nullptr;

	float EnemyHp = 10.0f;

	bool isDead_ = false;

	//SE
	uint32_t ShotSound_ = 0;
	uint32_t ShotHandle_ = 0;
};
