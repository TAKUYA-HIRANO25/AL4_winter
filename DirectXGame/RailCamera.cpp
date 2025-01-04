#include "RailCamera.h"
#include "imgui.h"

using namespace KamataEngine;

void RailCamera::Initialize(Vector3& translate, Vector3& rotate)
{
	worldTransform_.translation_ = translate;
	worldTransform_.rotation_ = rotate;

	velocity_ = { 0.0f,0.0f,-0.0f };
	rotate_ = { 0.0f,0.0f,0.0f };

	camera_.Initialize();
	camera_.farZ = 100.0f;
	myMath_ = new myMath();
}

void RailCamera::Update()
{
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &velocity_.x,0.0f,20.0f);
	ImGui::SliderFloat3("rotate", &rotate_.x, 0.0f, 20.0f);
	ImGui::End();
	worldTransform_.translation_ += velocity_;
	worldTransform_.rotation_ += rotate_;
	worldTransform_.UpdateMatrix(false);

	camera_.matView = myMath_->Inverse(worldTransform_.matWorld_);

}
