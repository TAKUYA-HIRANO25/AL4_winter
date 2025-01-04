#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>

class Skydom {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);


	void Update();

	void Draw();


private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::ObjectColor objColor_;


};