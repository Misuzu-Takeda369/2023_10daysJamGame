#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() 
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;
}

void TitleScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
	effectPos_ = effectpos;

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;
}

void TitleScene::Update() 
{

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}

	if (effectFlagStart_) {
		TitleEffectStart();
	}

	if ((inputchagekey_->TriggerKey(DIK_SPACE)) && !effectFlagStart_) {
		effectFlagEnd_ = true;
	}

	if (effectFlagEnd_) {
		TitleEffectEnd();
	}
}

void TitleScene::Draw()
{
	//Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight, 0.0f, 0x00000000 ,kFillModeSolid);

	
	Novice::DrawBox(int(khalfWidth- effectPos_.x), int(khalfHeight- effectPos_.y), int(effectPos_.x*2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
}

void TitleScene::TitleEffectEnd()
{
	effectPos_.x += 20.0f;
	effectPos_.y += 20.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		effectFlagEnd_ = false;
	}
}

void TitleScene::TitleEffectStart()
{
	effectPos_.x -= 20.0f;
	effectPos_.y -= 20.0f;

	if (effectPos_.x < 0.0f && (effectPos_.y < 0.0f)) {
		effectFlagStart_ = false;
		effectPos_.x = 0.0f;
		effectPos_.y = 0.0f;
	}
}


