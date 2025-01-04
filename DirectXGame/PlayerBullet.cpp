#include "PlayerBullet.h"
#include <cassert>
#include "MathUilityForText.h"
#include "myMath.h"
using namespace KamataEngine;

void PlayerBullet::Initialize(Model* model, const Vector3& position, const KamataEngine::Vector3& velocity)
{
	assert(model);

	model_ = model;


	objColor_.Initialize();

	worldTransform_.Initialize();

	velocity_ = velocity;

	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{

	worldTransform_.translation_ += velocity_;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera, &objColor_);
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

KamataEngine::Vector3 PlayerBullet::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;

	return worldPos;
}
