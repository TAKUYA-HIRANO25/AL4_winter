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
	audio_ = Audio::GetInstance();
	ShotSound_ = audio_->LoadWave("BGM/Shot.mp3");

	assert(model);

	model_ = model;

	objColor_.Initialize();
	bulletModel_ = Model::CreateFromOBJ("EnemyBullet", true);
	worldTransform_.Initialize();

	EnemyHp = 10.0f;

	isDead_ = false;

	FireTime();
	MoveTime();

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
		moveTime--;
		if (moveTime == 0) {
			move.x *= -1;
			moveTime = kMoveInterval;
		}

		worldTransform_.translation_ += move;

		Time--;

		if (Time == 0) {

			Fire();

			Time = kFireInterval;
		}

		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}

		if (EnemyHp <= 0) {
			isDead_ = true;
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
	ShotHandle_ = audio_->PlayWave(ShotSound_, false, 0.8f);

	const float kBulletSpeed = 0.5f;

	Vector3 velocity(0, 0, 0);
	//velocity = myMath::TransformNormal(velocity, worldTransform_.matWorld_);

	Vector3 playerPosition = player_->GetWorldPosition();
	Vector3 enemyPosition = GetWorldPosition();
	Vector3 goalPosition = playerPosition - enemyPosition;
	velocity = myMath::Normalize(goalPosition);
	velocity = { velocity.x * kBulletSpeed,velocity.y * kBulletSpeed, velocity.z * kBulletSpeed };
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(bulletModel_, worldTransform_.translation_, velocity);

	bullets_.push_back(newBullet);

}

void Enemy::FireTime()
{
	Time = kFireInterval;
}

void Enemy::MoveTime()
{
	moveTime = 180;
}

KamataEngine::Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;

	return worldPos;
}

void Enemy::OnCollision()
{
	EnemyHp -= 1;
}



