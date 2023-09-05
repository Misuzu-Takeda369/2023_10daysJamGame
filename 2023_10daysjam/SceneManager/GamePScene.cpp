#include "GamePScene.h"

GamePScene::GamePScene() 
{

}

GamePScene::~GamePScene() 
{
	delete player_;

}

void GamePScene::Initialize() 
{
	CountNum_ = 0;
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//プレイヤーの初期化
	//空じゃなければ一回デリートする
	if (player_ != nullptr) {
		delete player_;
	}
	player_ = new Player();
	player_->Initialize();

}

void GamePScene::Update()
{
	
	player_->Update();
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

}

void GamePScene::Draw() 
{
	Novice::ScreenPrintf(500,500,"%d", CountNum_);
	player_->Draw();
}

