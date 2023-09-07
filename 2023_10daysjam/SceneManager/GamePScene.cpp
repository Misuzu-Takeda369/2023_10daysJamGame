#include "GamePScene.h"

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

	eggNum_ = 0;
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

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if ((inputchagekey_->TriggerKey(DIK_0))|| player_->GetEggCount() >= 20) {
		flagChange_ = true;
	}

}

void GamePScene::Draw() 
{
	//背景の描写
	backGround_->Draw();
	//プレイヤーの描写
	player_->Draw();

	//子供(F)の描写
	for (FieldChild* fieldChild : fieldChild_) {
		
		fieldChild->Draw();
	}
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
			//現状プレイヤーが赤くなるぐらい(本来入らない？カウントぐらい)
			player_->OnFChildCollision();
			fieldChild->OnCollision();
			//後ろにいる子供はここでnew入るのか?その1
		}
		
		
	}
#pragma endregion

#pragma region PlayerとEnemyの当たり判定

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

