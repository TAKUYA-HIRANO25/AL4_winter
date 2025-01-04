#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <math/Vector3.h>

class PlayerBullet {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const KamataEngine::Camera& camera);

	bool IsDead() const { return isDead_; }

	void OnCollision();
	
	KamataEngine::Vector3 GetWorldPosition();

private:

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;

	int32_t deathTimer_ = kLifeTime;

	bool isDead_ = false;
};
