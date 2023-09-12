#include "SceneManager/GameCScene.h"

GameCScene::GameCScene() {}

GameCScene::~GameCScene() {}

void GameCScene::Initialize()
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}


void GameCScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;
	effectPos_ = effectpos;
}


void GameCScene::Update() 
{
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

	//解除
	if (effectFlagStart_) {
		GameCEffectStart();
	}
	

	if ((inputchagekey_->TriggerKey(DIK_SPACE)) && !effectFlagStart_) {
		effectFlagEnd_ = true;
	}

	if (effectFlagEnd_) {
		GameCEffectEnd();
	}
}

void GameCScene::Draw()
{
	Novice::DrawBox(int(khalfWidth - effectPos_.x), int(khalfHeight - effectPos_.y), int(effectPos_.x * 2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
}


void GameCScene::GameCEffectEnd()
{
	effectPos_.x += 20.0f;
	effectPos_.y += 20.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		effectFlagEnd_ = false;
	}
}

void GameCScene::GameCEffectStart()
{
	effectPos_.x -= 20.0f;
	effectPos_.y -= 20.0f;

	if (effectPos_.x <= 0.0f && (effectPos_.y <= 0.0f)) {
		effectFlagStart_ = false;
		effectPos_.x = 0.0f;
		effectPos_.y = 0.0f;
	}
}

