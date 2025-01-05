#include "Enemy.h"
#include <cassert>
#include "MathUilityForText.h"
#include "myMath.h"
#include "Player.h"
using namespace KamataEngine;

Enemy::Enemy()
{


}

Enemy::~Enemy()
{
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, Camera* camera, const KamataEngine::Vector3& position)
{
	assert(model);

	model_ = model;

	objColor_.Initialize();

	worldTransform_.Initialize();

	FireTime();

	camera_ = camera;

	worldTransform_.translation_ = position;
}

void Enemy::Update()
{
	switch (phase_)
	{
	case Phase::Approach:

		bullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
			});

		worldTransform_.translation_ += Vector3(0, 0, -0.1f);

		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		
		Time--;

		if (Time == 0) {

			Fire();

			Time = kFireInterval;
		}

		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}

		break;
	case Phase::Leave:
	worldTransform_.translation_+= Vector3(0, 1.0f, 0.0f);

		break;
	default:

		break;
	}

	worldTransform_.UpdateMatrix();

}

void Enemy::Draw()
{
	model_->Draw(worldTransform_, *camera_, &objColor_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(*camera_);
	}
}



void Enemy::Fire()
{
	const float kBulletSpeed = 0.5f;

	Vector3 velocity(0, 0, 0);
	//velocity = myMath::TransformNormal(velocity, worldTransform_.matWorld_);

	Vector3 playerPosition = player_->GetWorldPosition();
	Vector3 enemyPosition = GetWorldPosition();
	Vector3 goalPosition = playerPosition - enemyPosition;
	velocity = myMath::Normalize(goalPosition);
	velocity = { velocity.x * kBulletSpeed,velocity.y * kBulletSpeed, velocity.z * kBulletSpeed };
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);

}

void Enemy::FireTime()
{
	Time = kFireInterval;
}

KamataEngine::Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;

	return worldPos;
}

void Enemy::OnCollision()
{
}



