#include "GameOScene.h"

GameOScene::GameOScene() {}

GameOScene::~GameOScene() {}


void GameOScene::Initialize() 
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;

	image1_ = Novice::LoadTexture("./Resources/Images/over_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/over.png");

	//音ならす用変数
	overHandle_ = -1;
	soundOver_ = Novice::LoadAudio("./Resources/Sounds/GameOver.wav");
	//鳴らした数
	bgmCount_ = 0;
}


void GameOScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;

	effectPos_ = effectpos;

	image1_ = Novice::LoadTexture("./Resources/Images/over_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/over.png");

	//音ならす用変数
	overHandle_ = -1;
	soundOver_ = Novice::LoadAudio("./Resources/Sounds/GameOver.wav");
	//鳴らした数
	bgmCount_ = 0;
}

void GameOScene::Update() 
{
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
#ifdef _DEBUG
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}
#endif

	if (effectFlagStart_) {
		GameOEffectStart();
	}

	if ((!effectFlagStart_ && !effectFlagEnd_) && bgmCount_ == 0) {
		if (Novice::IsPlayingAudio(overHandle_) == 0 ||overHandle_ == -1) {
			overHandle_ = Novice::PlayAudio(soundOver_, 0, 1);
			bgmCount_++;
		}
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
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image1_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image2_, 1, 1, 0.0f, WHITE);

	Novice::DrawBox(int(khalfWidth - effectPos_.x), int(khalfHeight - effectPos_.y), int(effectPos_.x * 2), int(effectPos_.y * 2), 0, 0x13141AFF, kFillModeSolid);
}

void GameOScene::GameOEffectEnd()
{
	effectPos_.x += 20.0f;
	effectPos_.y += 20.0f;

	if (effectPos_.x >= 550.0f && (effectPos_.y >= 300.0f)) {
		flagChange_ = true;
		effectFlagEnd_ = false;
	}
}

void GameOScene::GameOEffectStart()
{
	effectPos_.x -= 20.0f;
	effectPos_.y -= 20.0f;

	if (effectPos_.x <= 0.0f && (effectPos_.y <= 0.0f)) {
		effectFlagStart_ = false;
		effectPos_.x = 0.0f;
		effectPos_.y = 0.0f;
	}
}

