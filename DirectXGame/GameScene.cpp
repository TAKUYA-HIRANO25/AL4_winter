#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete model_;
	delete camera_;
	delete fade;
	delete enemy_;
	delete debugCamera_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	objColor_.Initialize();
	worldTransform_.Initialize();
	worldTransform_.translation_.z = -40;
	model_ = Model::CreateFromOBJ("Plyer",true);
	enemyModel_ = Model::CreateFromOBJ("Enemy",true);
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);
	modelClear_ = Model::CreateFromOBJ("Clear", true);
	modelOver_ = Model::CreateFromOBJ("Over", true);
	camera_ = new Camera;
	camera_->Initialize();
	camera_->farZ = 1500.0f;
	enemyCamera_ = new Camera();
	enemyCamera_->Initialize();

	texturOperation = TextureManager::Load("Operation.png");
	spriteOperation = Sprite::Create(texturOperation, { 0.0f,0.0f });

	player_ = new Player();
	player_->Initialize(model_,camera_);
	
	enemy_ = new Enemy();
	enemy_->Initialize(enemyModel_,enemyCamera_,Vector3(0, 0, 40));
	enemy_->setPlayer(player_);

	skydome_ = new Skydom();
	skydome_->Initialize(modelSkydome_, camera_);

	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	// フェードの作成
	fade = new Fade();
	fade->Initialize();
	fade->Start(Fade::Status::FadeIn, 1.0f);

	GameSound_ = audio_->LoadWave("BGM/GameBGM.mp3");
	GameHandle_ = audio_->PlayWave(GameSound_, true, 0.2f);
	DecisionSound_ = audio_->LoadWave("BGM/Decision.mp3");

}

void GameScene::Update() {
	ChangePhase();


	switch (phase_) {
	case GameScene::Phase::kPlay:
		player_->Update();

		enemy_->Update();

		fade->Update();

		debugCamera_->Update();
		break;

	case GameScene::Phase::kFadeIn:

		fade->Start(Fade::Status::FadeOut, 1.0f);
		phase_ = Phase::kMain;

		break;

	case GameScene::Phase::kMain:
		fade->Update();

		break;


	case GameScene::Phase::kDeath:
		

		break;
	case GameScene::Phase::kClear:

		break;
	default:
		break;
	}
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
	worldTransform_.UpdateMatrix();
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
	switch (phase_) {
	case GameScene::Phase::kPlay:
		player_->Draw();
		enemy_->Draw();
		break;
	case GameScene::Phase::kDeath:
		modelOver_->Draw(worldTransform_, *camera_, &objColor_);

		break;
	case GameScene::Phase::kClear:
		modelClear_->Draw(worldTransform_, *camera_, &objColor_);

		break;
	}
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
	switch (phase_) {
	case GameScene::Phase::kPlay:
		spriteOperation->Draw();
	}

	fade->Draw(commandList);

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
		if (coll <= (0.5f + 1.0f) * (0.5f + 1.0f)) {
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
		if (coll <= (0.5f + 3.5f) * (0.5f + 3.5f)) {
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
			if (coll <= (0.5f + 0.5f) * (0.5f + 0.5f)) {
				bulletE->OnCollision();
				bulletP->OnCollision();

			}
		}
	}

#pragma endregion

}

void GameScene::ChangePhase()
{
	switch (phase_) {
	case GameScene::Phase::kPlay:
		if (player_->IsDead() == true) {
			phase_ = Phase::kDeath;
		}

		if (enemy_->IsDead() == true) {
			phase_ = Phase::kClear;
		}
		break;

	case GameScene::Phase::kFadeIn:

		fade->Start(Fade::Status::FadeOut, 1.0f);
		phase_ = Phase::kMain;

		break;

	case GameScene::Phase::kMain:
		if (fade->IsFinished()) {
			phase_ = Phase::kFadeOut;
		}

		break;

	case GameScene::Phase::kFadeOut:
		audio_->StopWave(GameHandle_);
		finished_ = true;

		break;
	case GameScene::Phase::kDeath:
		if (input_->TriggerKey(DIK_TAB)) {
			DecisionHandle_ = audio_->PlayWave(DecisionSound_, false, 0.8f);
			phase_ = Phase::kFadeIn;
		}
		break;

	case GameScene::Phase::kClear:
		if (input_->TriggerKey(DIK_TAB)) {
			DecisionHandle_ = audio_->PlayWave(DecisionSound_, false, 0.8f);
			phase_ = Phase::kFadeIn;
		}

		break;
	default:
		break;
	}
}
