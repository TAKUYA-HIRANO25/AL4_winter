#include "Player.h"
#include <imgui.h>
#include <algorithm>
#include "myMath.h"
#include "MathUilityForText.h"

using namespace KamataEngine;

Player::Player()
{

}

Player::~Player()
{
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(Model* model, Camera* camera)
{
	audio_ = Audio::GetInstance();
	model_ = model;
	bulletModel_ = Model::CreateFromOBJ("Bullet", true);
	camera_ = camera;

	isDead_ = false;

	ShotSound_ = audio_->LoadWave("BGM/Shot.mp3");
	PlayerHP = 3.0f;

	objColor_.Initialize();

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void Player::Update()
{

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Vector3 move = { 0,0,0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}

	Rotate();

	Attack();

	if (PlayerHP <= 0) {
		isDead_ = true;
	}

	for(PlayerBullet* bullet : bullets_){
		bullet->Update();
	}

	worldTransform_.translation_ += move;

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveX, kMoveX);

	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveY, kMoveY);

	worldTransform_.UpdateMatrix();

}

void Player::Draw()
{
	model_->Draw(worldTransform_, *camera_, &objColor_);

	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(*camera_);
	}
}

void Player::Rotate() 
{
	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {
		ShotHandle_ = audio_->PlayWave(ShotSound_, false, 0.8f);

		const float kBulletSpeed = 1.0f;

		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = myMath::TransformNormal(velocity, worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(bulletModel_, worldTransform_.translation_, velocity);

		bullets_.push_back(newBullet);
	}

}

KamataEngine::Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;

	return worldPos;
}

void Player::OnCollision()
{
	PlayerHP -= 1;
}
