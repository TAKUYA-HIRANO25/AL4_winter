#include "EnemyBullet.h"
#include <cassert>
#include "MathUilityForText.h"
#include "myMath.h"

using namespace KamataEngine;

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;

	objColor_.Initialize();

	worldTransform_.Initialize();

	velocity_ = velocity;

	worldTransform_.translation_ = position;
}

void EnemyBullet::Update()
{
	worldTransform_.translation_ += velocity_;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera, &objColor_);
}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

KamataEngine::Vector3 EnemyBullet::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;

	return worldPos;
}
