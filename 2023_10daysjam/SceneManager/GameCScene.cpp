#include "SceneManager/GameCScene.h"

GameCScene::GameCScene() {}

GameCScene::~GameCScene() {}

void GameCScene::Initialize()
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}

void GameCScene::Update() 
{
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}
}

void GameCScene::Draw() {}

void GameCScene::BackDraw() {}
