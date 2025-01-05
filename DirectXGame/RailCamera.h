#pragma once
#include <3d/WorldTransform.h>

class RailCamera {
public:
	void Initialize();

	void Update();


private:
	KamataEngine::WorldTransform worldTransform_;


};