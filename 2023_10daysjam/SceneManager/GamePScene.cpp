#include "GamePScene.h"
#include "Novice.h"

GamePScene::GamePScene() 
{

}

GamePScene::~GamePScene() {}

void GamePScene::Initialize() 
{
	CountNum_ = 0;
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}

void GamePScene::Update()
{
	//確認用
	CountNum_ += 1;

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

}

void GamePScene::Draw() 
{
	Novice::ScreenPrintf(500,500,"%d", CountNum_);
}
