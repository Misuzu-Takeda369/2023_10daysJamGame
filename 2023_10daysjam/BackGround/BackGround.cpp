#include "BackGround.h"

BackGround::BackGround(Vector2 playerRadish)
{
	playerRadish_ = { playerRadish.x,playerRadish.y };
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
	wouldPosition_ = { 0.0f,0.0f };
	scrollPosition_ = { 0.0f,0.0f };
	speed_ = { 2.0f,2.0f };
	image_ = 0;
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

	//スクロールが止まる条件
	//真ん中から画面の半分分動いたら止まる(画面の半分のサイズ＋プレイヤーの半径の調整)
	//条件あったらスピードが0、それ以外ならそのまま
	if ((scrollPosition_.x <= -HalfBackGroundSize_.x + playerRadish_.x) && keys[DIK_LEFT]) {
		speed_.x = 0.0f;
		scrollPosition_.x = -HalfBackGroundSize_.x + playerRadish_.x;
	}
	else if ((scrollPosition_.x >= HalfBackGroundSize_.x - playerRadish_.x) && keys[DIK_RIGHT]) {
		speed_.x = 0.0f;
		scrollPosition_.x = HalfBackGroundSize_.x - playerRadish_.x;
	}
	else if ((scrollPosition_.y <= -HalfBackGroundSize_.y + playerRadish_.y) && keys[DIK_UP]) {
		speed_.y = 0.0f;
		scrollPosition_.y = -HalfBackGroundSize_.y + playerRadish_.y;
	}
	else if ((scrollPosition_.y >= HalfBackGroundSize_.y - playerRadish_.y) && keys[DIK_DOWN]) {
		speed_.y = 0.0f;
		scrollPosition_.y = HalfBackGroundSize_.y - playerRadish_.y;
	}
	else {
		speed_.x = 2.0f;
		speed_.y = 2.0f;
	}
}
