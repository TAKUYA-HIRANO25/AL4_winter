#include <math/Vector3.h>

// 2項演算子オーバーロード
// Vextor3の足算
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

const KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float s);

const KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s);

KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

const KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);


// イージング関数の宣言
float Lerp(float x1, float x2, float t);

KamataEngine::Vector3 Lerp(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2, float t);

float EaseInOut(float x1, float x2, float t);
