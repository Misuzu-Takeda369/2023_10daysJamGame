#include "GamePScene.h"
#include "Novice.h"

GamePScene::GamePScene() 
{
	
}

GamePScene::~GamePScene() 
{
	delete player_;
	delete backGround_;
	//子(F)のデリート
	for (FieldChild* fieldChild : fieldChild_) {
		delete fieldChild;
	}
	//子(back)のデリート
	for (PlayerChild* playerChild : playerChild_) {
		delete playerChild;
	}

	//敵のデリート
	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
	//delete enemy_;
}

void GamePScene::Initialize() 
{
	
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//プレイヤーの初期化
	//空じゃなければ一回デリートする
	if (player_ != nullptr) {
		delete player_;
	}
	player_ = new Player();
	player_->Initialize();

	//背景の初期化
	//空じゃなければ一回デリートする
	if (backGround_ != nullptr) {
		delete backGround_;
	}
	backGround_ = new BackGround(player_->GetPlayerRadius());
	backGround_->Initialize();

	//ゲームオーバーフラグ
	flagGameOver_ = false;

	//敵の初期化
	//enemy_ = new Enemy();
	//enemy_->Initialize();
	

}

void GamePScene::Update()
{

	//角度調整用のキー入力
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	
	//プレイヤーの更新
	player_->Update();
	//背景の更新
	backGround_->Update();

	//敵の更新
	//enemy_->Update();

	Attack();

#pragma region 子供(F)のゲームシーン内の処理
	//子供(F)のゲームシーン内の処理
	fieldChildWaitTimer_++;
	if (fieldChildWaitTimer_ >= FieldChild::spawnWaitTime_) {
		AddFieldChild(player_->GetPlayerPosition());
		fieldChildWaitTimer_ = 0;
	}
	FieldChildUpdate();
#pragma endregion

#pragma region 敵のゲームシーン内の処理
	
	enemiesWaitTimer_++;
	if (enemiesWaitTimer_ >= Enemy::spawnWaitTime_) {
		AddEnemies(player_->GetPlayerPosition());
		enemiesWaitTimer_ = 0;
	}
	EnemiesUpdate();
#pragma endregion



	//ここに子供(Back)の更新
	PlayerChildUpdate();

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動 20でクリアシーンへ移動
	if (((inputchagekey_->TriggerKey(DIK_0))|| player_->GetEggCount() >= 20)  || flagGameOver_) {
		flagChange_ = true;
	}


}

void GamePScene::Draw() 
{
	Novice::ScreenPrintf(500, 500, "%d", CountNum_);
	//背景の描写
	backGround_->Draw();
	//プレイヤーの描写
	player_->Draw();


	//子供(F)の描写
	for (FieldChild* fieldChild : fieldChild_) {
		
		fieldChild->Draw();
	}

	//子供(Back)の描写
	for (PlayerChild* playerChild : playerChild_) {
		playerChild->Draw();
	}

	//enemy_->Draw
	for (Enemy* enemy : enemy_) {
		enemy->Draw();
	}
	
}

void GamePScene::Attack()
{

	//当たり判定用の変数(Player) 
	Vector2 cheakPpos = player_->GetPlayerPosition();
	Vector2 cheakPradish = player_->GetPlayerRadius();

#pragma region Playerと子供(F)の当たり判定
	

	for (FieldChild* fieldChild : fieldChild_) {

		Vector2 cheakFCpos = fieldChild->GetScreenPos();
		Vector2 cheakFCradish = fieldChild->GetRadius();
		

		if (CircleCollision(cheakPpos.x, cheakPpos.y, cheakPradish.x, cheakFCpos.x, cheakFCpos.y, cheakFCradish.x)==true) {
			//カウント
			player_->OnFChildCollision();
			fieldChild->OnCollision();
			//後ろにいる子供はここでnew入るのか?その1
			AddPlayerChild();
		}
		
		
	}
#pragma endregion

#pragma region PlayerとEnemyの当たり判定


	for (Enemy* enemy : enemy_) {

		Vector2 cheakEpos = enemy->GetScreenPos();
		int cheakEradish = enemy->GetRadius();

		if (CircleCollision(cheakPpos.x, cheakPpos.y, cheakPradish.x, cheakEpos.x, cheakEpos.y, float(cheakEradish)) == true) {
			//カウント
			player_->OnEnemyCollision();
			enemy->OnCollision();
			//子供が減る
			PlayerChildLost();
		}

	}

	//シーン変換のために(キー1押してたまごのカウントが0だった場合ゲームオーバーに行くようにフラグ) 
	

		if (player_->GetEggCount() < 0) {
			flagGameOver_ = true;
		}
		else if ((inputchagekey_->TriggerKey(DIK_1)) && player_->GetEggCount() == 0) {
			flagGameOver_ = true;
		}

#pragma endregion

#pragma region Enemyと子供(Bullet)の当たり判定

#pragma endregion

}

void GamePScene::AddFieldChild(Vector2 playerPos)
{
	FieldChild* obj = new FieldChild;

	obj->Initialize(playerPos, backGround_->GetScrollPosition());
	fieldChild_.push_back(obj);
}


void GamePScene::FieldChildUpdate()
{
	fieldChild_.remove_if([](FieldChild* fieldChild) {
		if (fieldChild->GetIsArrive() == false) {
			delete fieldChild;
			return true; //returnをつける
		}
		return false;
		});

	for (FieldChild* fieldChild : fieldChild_) {
		fieldChild->Update(backGround_->GetScrollPosition());
	}
}

void GamePScene::AddPlayerChild()
{
	PlayerChild* obj = new PlayerChild;
	Vector2 forwardPos;
	if (childCounter_ == 0) {
		forwardPos = player_->GetPlayerPosition();
	}
	else {
		for (PlayerChild* playerChild : playerChild_) {
			forwardPos = playerChild->GetPos();
		}
	}
	childCounter_++;
	CountNum_++;
	obj->Initialize(forwardPos, player_->GetPlayerPosition(), backGround_->GetScrollPosition());
	obj->SetChildNumber(childCounter_);
	playerChild_.push_back(obj);
}

void GamePScene::PlayerChildUpdate()
{
	playerChild_.remove_if([](PlayerChild* playerChild) {
		if (playerChild->GetIsArrive() == false) {
			delete playerChild;
			return true; //returnをつける
		}
		return false;
		});

	Vector2 forwardPos;
	for (PlayerChild* playerChild : playerChild_) {

		if (playerChild->GetChildNumber() == 1) {
			playerChild->SetDirection(preKeys);
			forwardPos = player_->GetPlayerPosition();
		}
		playerChild->Update(forwardPos, player_->GetPlayerPosition(), backGround_->GetScrollPosition());
		forwardPos = playerChild->GetPos();
	}
}

void GamePScene::PlayerChildLost()
{
	for (PlayerChild* playerChild : playerChild_) {
		if (childCounter_ == uint32_t(playerChild->GetChildNumber())) {
			playerChild->SetIsArrive(false);
		}
	}
	childCounter_--;

}


void GamePScene::AddEnemies(Vector2 playerPos)
{
	Enemy* obj = new Enemy;

	obj->Initialize(playerPos, backGround_->GetScrollPosition());
	enemy_.push_back(obj);

}

void GamePScene::EnemiesUpdate()
{

	enemy_.remove_if([](Enemy* enemy) {
		if (enemy->GetIsArrive() == false) {
			delete enemy;
			return true; //returnをつける
		}
		return false;
		});

	for (Enemy* enemy : enemy_) {
		enemy->Update(backGround_->GetScrollPosition());
	}
}
