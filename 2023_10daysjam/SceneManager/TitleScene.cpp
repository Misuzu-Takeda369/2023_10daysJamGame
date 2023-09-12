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

	image1_ = Novice::LoadTexture("./Resources/Images/start_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/start1.png");


	if (manual_ != nullptr) {
		delete manual_;
	}
	manual_ = new Manual();
	manual_->Initialize();

}

void TitleScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
	effectPos_ = effectpos;

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;

	image1_ = Novice::LoadTexture("./Resources/Images/start_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/start1.png");


	if (manual_ != nullptr) {
		delete manual_;
	}
	manual_ = new Manual();
	manual_->Initialize();
}

void TitleScene::Update()
{

	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動

#ifdef _DEBUG
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}
#endif

	if (effectFlagStart_) {
		TitleEffectStart();
	}

	//マニュアルだすやつ
	if (!manual_->GetFrag()) {
		if ((inputchagekey_->TriggerKey(DIK_Z)) && !effectFlagStart_) {
			manual_->SetFrag(true);

		}


		if ((inputchagekey_->TriggerKey(DIK_SPACE)) && !effectFlagStart_) {
			effectFlagEnd_ = true;
		}

	}
	if (effectFlagEnd_) {
		TitleEffectEnd();
	}

	manual_->Update();
}

void TitleScene::Draw()
{
	//Novice::DrawBox(MimWindowWidth, MimWindowHeight, kWindowWidth, kWindowHeight, 0.0f, 0x00000000 ,kFillModeSolid);
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image1_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image2_, 1, 1, 0.0f, WHITE);

	manual_->Draw();

	///シーン変換エフェクト
	Novice::DrawBox(int(khalfWidth - effectPos_.x), int(khalfHeight - effectPos_.y), int(effectPos_.x * 2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
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


