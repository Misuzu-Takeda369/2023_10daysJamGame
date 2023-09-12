﻿#include "GameOScene.h"

GameOScene::GameOScene() {}

GameOScene::~GameOScene() {}


void GameOScene::Initialize() 
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}

/*
void GameOScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;
}
*/
void GameOScene::Update() 
{
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

	if (effectFlagStart_) {
		GameOEffectStart();
	}

	if ((inputchagekey_->TriggerKey(DIK_SPACE)) && !effectFlagStart_) {
		effectFlagEnd_ = true;
	}

	if (effectFlagEnd_) {
		GameOEffectEnd();
	}
}

void GameOScene::Draw() 
{
	Novice::DrawBox(int(khalfWidth - effectPos_.x), int(khalfHeight - effectPos_.y), int(effectPos_.x * 2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
}

void GameOScene::GameOEffectEnd()
{
	effectPos_.x += 40.0f;
	effectPos_.y += 40.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		effectFlagEnd_ = false;
	}
}

void GameOScene::GameOEffectStart()
{
	effectPos_.x -= 40.0f;
	effectPos_.y -= 40.0f;

	if (effectPos_.x <= 0.0f && (effectPos_.y <= 0.0f)) {
		effectFlagStart_ = false;
		effectPos_.x = 0.0f;
		effectPos_.y = 0.0f;
	}
}

