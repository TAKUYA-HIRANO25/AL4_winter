#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete model_;
	delete camera_;
	delete debugCamera_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_ = Model::Create();
	enemyModel_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);

	camera_ = new Camera;
	camera_->Initialize();
	camera_->farZ = 100.0f;
	enemyCamera_ = new Camera();
	enemyCamera_->Initialize();

	player_ = new Player();
	player_->Initialize(model_,camera_);
	
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_,enemyCamera_,Vector3(0, 0, 100));
	enemy_->setPlayer(player_);

	skydome_ = new Skydom();
	skydome_->Initialize(modelSkydome_, camera_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);
}

void GameScene::Update() {

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_SPACE)) {
			if (isDebugCameraActive_ == true)
				isDebugCameraActive_ = false;
			else
				isDebugCameraActive_ = true;
		}
#endif

	player_->Update();

	enemy_->Update();

	debugCamera_->Update();

	checkAllcollisions();

	// カメラ処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		camera_->matView = debugCamera_->GetCamera().matView;
		camera_->matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		camera_->TransferMatrix();
	}
	else {
		// ビュープロジェクション行列の更新と転送
		camera_->UpdateMatrix();
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw();
	enemy_->Draw();
	skydome_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::checkAllcollisions()
{
	Vector3 posA, posB;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region player
	posA = player_->GetWorldPosition(); 

	for (EnemyBullet* bullet : enemyBullets )
	{
		posB = bullet->GetWorldPosition();

		float coll = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);
		//	半径は１
		if (coll <= (1 + 1) * (1 + 1)) {
			player_->OnCollision();

			bullet->OnCollision();
		}


	}


#pragma endregion

#pragma region Enemy
	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets)
	{
		posB = bullet->GetWorldPosition();

		float coll = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);
		//	半径は１
		if (coll <= (1 + 1) * (1 + 1)) {
			enemy_->OnCollision();

			bullet->OnCollision();
		}

	}
#pragma endregion

#pragma region Bullet
	for (PlayerBullet* bulletP : playerBullets)
	{
		posA = bulletP->GetWorldPosition(); 

		for (EnemyBullet* bulletE : enemyBullets)
		{
			posA = bulletP->GetWorldPosition();
			posB = bulletE->GetWorldPosition();

			float coll = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);
			
			//	半径は１
			if (coll <= (1 + 1) * (1 + 1)) {
				bulletE->OnCollision();
				bulletP->OnCollision();

			}
		}
	}

#pragma endregion

}
