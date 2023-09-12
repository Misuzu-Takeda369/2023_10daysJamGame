#include "Manual.h"

Manual::Manual()
{
	frag_ = false;
	pos_ = { 0.0f,-kWindowHeight };
	movePos_ = { 0.0f,0.0f };
	speed_ = { 0.0f,10.0f };
	image1_ = Novice::LoadTexture("./Resources/Images/manual.png");
	image2_ = 0;

	inputchagekey_ = Input::GetInstance();
	cooltime_ = 60;
}

Manual::~Manual()
{
}

void Manual::Initialize()
{
	frag_ = false;
	pos_ = { 0.0f,-kWindowHeight };
	movePos_ = { 0.0f,0.0f };
	speed_ = { 0.0f,10.0f };
	image1_ = Novice::LoadTexture("./Resources/Images/manual.png");
	image2_ = 0;

	inputchagekey_ = Input::GetInstance();
	
}

void Manual::Update()
{
	if (frag_) {
		
		if (!returnfrag_) {
			movePos_.y += speed_.y;
			speed_.y += 2.0f;

			if ((pos_.y + movePos_.y) >= MimWindowHeight) {
				speed_.y = 0.0f;
				movePos_.y = kWindowHeight;
			}

			if (movePos_.y == kWindowHeight) {

				if ((inputchagekey_->TriggerKey(DIK_Z))) {

					returnfrag_ = true;
					speed_.y = 10.0f;

				}
			}
		}
		if (returnfrag_) {
			movePos_.y -= speed_.y;
			speed_.y += 2.0f;

			if ((pos_.y + movePos_.y) <= -kWindowHeight) {
				speed_.y = 0.0f;
				movePos_.y = 0.0f;
				frag_ = false;
				returnfrag_ = false;
			}
		}

	}

	
}

void Manual::Draw()
{
#ifdef _DEBUG
	Novice::ScreenPrintf(0,0,"flag %d",frag_);
	Novice::ScreenPrintf(0, 10, "returnfrag_ %d", returnfrag_);
	//Novice::ScreenPrintf(0, 40, "cooltime_ %d", cooltime_);
#endif

	if (frag_) {
		Novice::DrawSprite(int(pos_.x+ movePos_.x), int(pos_.y+ movePos_.y),image1_,1,1,0.0f,WHITE);
	}
}
