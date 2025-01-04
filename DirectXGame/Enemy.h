#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include "3d/Camera.h"
#include <math/Vector3.h>
#include "EnemyBullet.h"
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

	static const int kFireInterval = 180;

	void FireTime();

	void setPlayer(Player* player) { player_ = player; }

	KamataEngine::Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

private:

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Vector3 velocity_;

	Phase phase_ = Phase::Approach;

	std::list<EnemyBullet*> bullets_;

	int32_t Time = 0;

	Player* player_ = nullptr;

	

};
