#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
}

void BackGround::Update()
{
#pragma region Noviceのキー入力関連
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
#pragma endregion

	//背景の移動関数
	Move(keys);

	
#pragma region ImGui関連

	ImGui::Begin("BackGroundMove");
	ImGui::Text("scrollPosition_ %f,%f", scrollPosition_.x, scrollPosition_.y);
	ImGui::End();

#pragma endregion
}

void BackGround::Draw()
{
	Novice::DrawBox(uint32_t(wouldPosition_.x - scrollPosition_.x), uint32_t(wouldPosition_.y - scrollPosition_.y), 1280, 720, 0.0f, RED, kFillModeWireFrame);
}


void BackGround::Move(char* keys)
{
	//斜め移動
	if (keys[DIK_LEFT] && keys[DIK_UP]) {
		MoveStop(keys);
		scrollPosition_.x -= (speed_.x / 1.41f);
		scrollPosition_.y -= (speed_.y / 1.41f);
	}
	else if (keys[DIK_RIGHT] && keys[DIK_UP]) {
		MoveStop(keys);
		scrollPosition_.x += (speed_.x / 1.41f);
		scrollPosition_.y -= (speed_.y / 1.41f);
	}
	else if (keys[DIK_LEFT] && keys[DIK_DOWN]) {
		MoveStop(keys);
		scrollPosition_.x -= (speed_.x / 1.41f);
		scrollPosition_.y += (speed_.y / 1.41f);
	}
	else if (keys[DIK_RIGHT] && keys[DIK_DOWN]) {
		MoveStop(keys);
		scrollPosition_.x += (speed_.x / 1.41f);
		scrollPosition_.y += (speed_.y / 1.41f);
	}

	//直線移動
	else if (keys[DIK_LEFT]) {
		MoveStop(keys);
		scrollPosition_.x -= speed_.x;
	}
	else if (keys[DIK_RIGHT]) {
		MoveStop(keys);
		scrollPosition_.x += speed_.x;
	}
	else if (keys[DIK_UP]) {
		MoveStop(keys);
		scrollPosition_.y -= speed_.y;
	}
	else if (keys[DIK_DOWN]) {
		MoveStop(keys);
		scrollPosition_.y += speed_.y;
	}
}

void BackGround::MoveStop(char* keys)
{

	if ((scrollPosition_.x <= -640.0f+32.0f) && keys[DIK_LEFT]) {
		speed_.x = 0.0f;
	}
	else if ((scrollPosition_.x >= 640.0f - 32.0f) && keys[DIK_RIGHT]) {
		speed_.x = 0.0f;
	}
	else if ((scrollPosition_.y <= -360.0f + 32.0f) && keys[DIK_UP]) {
		speed_.y = 0.0f;
	}
	else if ((scrollPosition_.y >= 360.0f - 32.0f) && keys[DIK_DOWN]) {
		speed_.y = 0.0f;
	}
	else {
		speed_.x = 2.0f;
		speed_.y = 2.0f;
	}
}
