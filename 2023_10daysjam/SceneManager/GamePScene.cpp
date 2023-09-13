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
	GameMove_ = false;

	AttackTime_ = 180;
	AttackFlag_ = true;
}


void GamePScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;

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

	GameMove_ = false;

	effectPos_ = effectpos;

	AttackTime_ = 180;
	AttackFlag_ = true;
}



void GamePScene::Update()
{
	if (!GameMove_) {

		//解除
		if (effectFlagStart_) {
			GamePEffectStart();
		}

		if (effectFlagEnd_) {
			GamePEffectEnd();
		}

	}
	else if (GameMove_) {


		//角度調整用のキー入力
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//プレイヤーの更新
		player_->Update(keys);
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

		//子供直接攻撃時に子供が一体減ったら暫くは減らないようにする
		if (!AttackFlag_) {
			AttackTime_--;
			if (AttackTime_ <= 0) {
				AttackFlag_ = true;
				AttackTime_ = 180;
			}
		}

		//ここのif文でシーン移行出来るかを判別
		//現在は0を押したときに移動 20でクリアシーンへ移動
		if (flagGameOver_) {
			effectFlagEnd_ = true;
			GameMove_ = false;

		}

		if ((player_->GetEggCount() >= 20)) {
			effectFlagEnd_ = true;
			GameMove_ = false;
		}

#ifdef _DEBUG
		if (((inputchagekey_->TriggerKey(DIK_0)) || player_->GetEggCount() >= 20)) {
			effectFlagEnd_ = true;
			GameMove_ = false;

		}
#endif // DEBUG

	}
}

void GamePScene::Draw()
{
#ifdef _DEBUG
	Novice::ScreenPrintf(500, 500, "%d", AttackTime_);
	Novice::ScreenPrintf(550, 550, "%d", AttackFlag_);
#endif
	//背景の描写
	backGround_->Draw();
	//プレイヤーの描写
	//player_->Draw();

	//UI作ったら消す(リリース用確認)
	//Novice::ScreenPrintf(550, 550, "%d", player_->GetEggCount());
	
	//子供(F)の描写
	for (FieldChild* fieldChild : fieldChild_) {

		fieldChild->Draw();
	}

	//子供(Back)の描写
	for (PlayerChild* playerChild : playerChild_) {
		playerChild->Draw();
	}
	//プレイヤーの描写
	player_->Draw();

	//enemy_->Draw
	for (Enemy* enemy : enemy_) {
		enemy->Draw();
	}

	//エフェクト
	Novice::DrawBox(int(khalfWidth - effectPos_.x), int(khalfHeight - effectPos_.y), int(effectPos_.x * 2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
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


		if (CircleCollision(cheakPpos.x, cheakPpos.y, (cheakPradish.x), cheakFCpos.x, cheakFCpos.y, cheakFCradish.x) == true) {
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

		if (CircleCollision(cheakPpos.x, cheakPpos.y, (cheakPradish.x/2), cheakEpos.x, cheakEpos.y, float(cheakEradish)) == true) {


			if (enemy->GetEffectFrag() == false) {
				player_->OnEnemyCollision();
				backGround_->MoveStop();
				//子供が減る
				PlayerChildLost();
			}

			//カウント
			enemy->OnCollision();
		}

	}

	//シーン変換のために(キー1押してたまごのカウントが0だった場合ゲームオーバーに行くようにフラグ) 


	if (player_->GetEggCount() < 0) {
		flagGameOver_ = true;
	}

#ifdef _DEBUG
	else if ((inputchagekey_->TriggerKey(DIK_1)) && player_->GetEggCount() == 0) {
		flagGameOver_ = true;
	}
#endif

#pragma endregion

#pragma region Enemyと子供(Bullet)の当たり判定
	for (Enemy* enemy : enemy_) {
		Vector2 cheakEpos = enemy->GetScreenPos();
		int cheakEradish = enemy->GetRadius();

		for (PlayerChild* playerChild : playerChild_) {
#pragma region 弾発射されてるやつ
			Vector2 cheakCbBpos = playerChild->GetScreenBulletPos();
			bool cheakBulletLive = playerChild->GetBulletLive();
			float cheakCbBradish = float(playerChild->GetRadius());

			if (cheakBulletLive) {
				if (CircleCollision(cheakEpos.x, cheakEpos.y, float(cheakEradish), cheakCbBpos.x, cheakCbBpos.y, cheakCbBradish) == true) {
					//カウント
					enemy->OnCollision();

				}
			}

#pragma endregion 

#pragma region 子供の直接攻撃
			Vector2 cheakCbpos = playerChild->GetPos();
			float cheakCbradish = float(playerChild->GetRadius());


			if (CircleCollision(cheakEpos.x, cheakEpos.y, float(cheakEradish), cheakCbpos.x, cheakCbpos.y, (cheakCbradish * 2)) == true) {
				//カウント
				if (enemy->GetEffectFrag() == false) {
					if (AttackFlag_) {

						if (player_->GetEggCount() >0) {
							PlayerChildLostAttack();
						}
						AttackFlag_ = false;
					}
				}
				enemy->OnCollision();

			}


#pragma endregion

		}

	}
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
			//1人目の子だけしかアニメーションが反応しないので変更しました
			//playerChild->SetDirection(preKeys);
			forwardPos = player_->GetPlayerPosition();
		}
		playerChild->SetDirection(preKeys);
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

void GamePScene::GamePEffectEnd()
{
	effectPos_.x += 20.0f;
	effectPos_.y += 20.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		effectFlagEnd_ = false;
	}
}

void GamePScene::GamePEffectStart()
{
	effectPos_.x -= 20.0f;
	effectPos_.y -= 20.0f;

	if (effectPos_.x <= 0.0f && (effectPos_.y <= 0.0f)) {
		effectFlagStart_ = false;
		effectPos_.x = 0.0f;
		effectPos_.y = 0.0f;
		GameMove_ = true;
	}
}

void GamePScene::PlayerChildLostAttack()
{
	for (PlayerChild* playerChild : playerChild_) {
		if (playerChild->GeisGrow() == false) {
			if (childCounter_ == uint32_t(playerChild->GetChildNumber())) {
				playerChild->SetIsArrive(false);
				childCounter_--;
				//カウント
				player_->OnPbAttackCollision();
			}
		}
	}
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

