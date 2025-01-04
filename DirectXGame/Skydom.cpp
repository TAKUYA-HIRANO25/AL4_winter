#include "Skydom.h"

using namespace KamataEngine;

void Skydom::Initialize(Model* model, Camera* camera)
{
	worldTransform_.Initialize();
	model_ = model;
	objColor_.Initialize();
	camera_ = camera;
}

void Skydom::Update()
{

}

void Skydom::Draw()
{
	model_->Draw(worldTransform_, *camera_, &objColor_);
}
