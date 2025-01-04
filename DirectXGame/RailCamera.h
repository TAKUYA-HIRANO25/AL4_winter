#pragma once
#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include "MathUilityForText.h"
#include "myMath.h"

class RailCamera {
public:
	void Initialize(KamataEngine::Vector3& translate, KamataEngine::Vector3& rotate);

	void Update();

	const KamataEngine::Camera& GetCamera() { return camera_; }

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera camera_;

	KamataEngine::Vector3 velocity_;
	KamataEngine::Vector3 rotate_;

	myMath* myMath_ = nullptr;
};