#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() 
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}

void TitleScene::Update() 
{

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

	if (inputchagekey_->TriggerKey(DIK_SPACE)) {
		EffectFlag_ = true;
	}

	if (EffectFlag_) {
		TitleEffect();
	}
}

void TitleScene::Draw()
{
	//Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight, 0.0f, 0x00000000 ,kFillModeSolid);

	
	Novice::DrawBox(int(khalfWidth- effectPos_.x), int(khalfHeight- effectPos_.y), int(effectPos_.x*2), int(effectPos_.y * 2), 0, 0x363747FF, kFillModeSolid);
}

void TitleScene::TitleEffect()
{
	effectPos_.x += 40.0f;
	effectPos_.y += 40.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		EffectFlag_ = false;
	}
}


