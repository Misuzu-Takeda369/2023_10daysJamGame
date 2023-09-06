#include "GamePScene.h"

GamePScene::GamePScene() 
{

}

GamePScene::~GamePScene() 
{
	delete player_;
	delete backGround_;

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
	

}

void GamePScene::Update()
{
	
	//プレイヤーの更新
	player_->Update();
	//背景の更新
	backGround_->Update();

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

}

void GamePScene::Draw() 
{
	//背景の描写
	backGround_->Draw();
	//プレイヤーの描写
	player_->Draw();
}

