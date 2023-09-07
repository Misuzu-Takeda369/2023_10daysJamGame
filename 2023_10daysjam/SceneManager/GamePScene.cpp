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
	backGround_ = new BackGround(player_->GetPlayerRadish());
	backGround_->Initialize();

	flagGameOver_ = false;
}

void GamePScene::Update()
{
	
	//プレイヤーの更新
	player_->Update();
	//背景の更新
	backGround_->Update();

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

	//ここに子供(Back)
	PlayerChildUpdate();

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
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

	//プレイヤーの描写
	player_->Draw();
	
}

void GamePScene::Attack()
{
#pragma region Playerと子供(F)の当たり判定
	
	//当たり判定用の変数
	Vector2 cheakPpos = player_->GetPlayerPosition();
	Vector2 cheakPradish = player_->GetPlayerRadish();

	for (FieldChild* fieldChild : fieldChild_) {

		Vector2 cheakFCpos = fieldChild->GetScreenPos();
		Vector2 cheakFCradish = fieldChild->GetRadish();
		

		if (CircleCollision(cheakPpos.x, cheakPpos.y, cheakPradish.x, cheakFCpos.x, cheakFCpos.y, cheakFCradish.x)==true) {
			//カウント
			player_->OnFChildCollision();
			fieldChild->OnCollision();
			//後ろにいる子供はここでnew入るのか?その1
			AddPlayeChild();
		}
		
		
	}
#pragma endregion

#pragma region PlayerとEnemyの当たり判定

	//シーン変換のために(キー1押してたまごのカウントが0だった場合ゲームオーバーに行くようにフラグ) 
	if ((inputchagekey_->TriggerKey(DIK_1))) {

		if (player_->GetEggCount() == 0) {
			flagGameOver_ = true;
		}

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

void GamePScene::AddPlayeChild()
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
