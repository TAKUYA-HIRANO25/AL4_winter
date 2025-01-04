#include <3d/WorldTransform.h>
#include "myMath.h"

using namespace KamataEngine;

void WorldTransform::UpdateMatrix(bool isTranslate) {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	if (parent_) {
		//matWorld_ *= parent_->matWorld_;
	}
	if (isTranslate) {
		TransferMatrix();
	}
}



