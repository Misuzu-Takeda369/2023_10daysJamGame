#include "SceneManager/GameCScene.h"

GameCScene::GameCScene() {}

GameCScene::~GameCScene() {}

void GameCScene::Initialize()
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	image1_ = Novice::LoadTexture("./Resources/Images/clear_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/clear.png");

	//音ならす用変数
	clearHandle_  = -1;
	soundClear_ = Novice::LoadAudio("./Resources/Sounds/GameClear.wav");
	//鳴らした数
	bgmCount_ = 0;

	soundDecision_ = Novice::LoadAudio("./Resources/Sounds/Decision.wav");
	decisionHandle_ = -1;
}


void GameCScene::Initialize(Vector2 effectpos)
{
	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();

	//シーン変換用エフェクト
	effectFlagEnd_ = false;
	effectFlagStart_ = true;
	effectPos_ = effectpos;

	image1_ = Novice::LoadTexture("./Resources/Images/clear_background.png");
	image2_ = Novice::LoadTexture("./Resources/Images/clear.png");

	//音ならす用変数
	clearHandle_ = -1;
	soundClear_ = Novice::LoadAudio("./Resources/Sounds/GameClear.wav");
	//鳴らした数
	bgmCount_ = 0;

	soundDecision_ = Novice::LoadAudio("./Resources/Sounds/Decision.wav");
	decisionHandle_ = -1;
}


void GameCScene::Update() 
{
	//ここのif文でシーン移行出来るかを判別
	//現在は0を押したときに移動
#ifdef _DEBUG
	if (inputchagekey_->TriggerKey(DIK_0)) {
		flagChange_ = true;
	}
#endif
	//解除
	if (effectFlagStart_) {
		GameCEffectStart();
	}

	if ((!effectFlagStart_&& !effectFlagEnd_)&& bgmCount_== 0) {
		if (Novice::IsPlayingAudio(clearHandle_) == 0 || clearHandle_ == -1) {
			clearHandle_ = Novice::PlayAudio(soundClear_, 0, 1);
			bgmCount_++;
		}
	}

	if ((inputchagekey_->TriggerKey(DIK_SPACE)) && !effectFlagStart_) {
		if (Novice::IsPlayingAudio(decisionHandle_) == 0 || decisionHandle_ == -1) {
			decisionHandle_ = Novice::PlayAudio(soundDecision_, 0, 1);
		}
		effectFlagEnd_ = true;
	}

	if (effectFlagEnd_) {
		GameCEffectEnd();
	}
}

void GameCScene::Draw()
{
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image1_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(MimWindowWidth, MimWindowHeight, image2_, 1, 1, 0.0f, WHITE);

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

