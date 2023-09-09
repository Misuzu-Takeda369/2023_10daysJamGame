#include "Player.h"

#ifdef _DEBUG
#include "ImGuiManager.h"
#endif

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//プレイヤーのステータスの初期
	position_ = { 640.0f,360.0f };
	color_ = WHITE;
	speed_ = { 2.0f,2.0f };
	image_ = Novice::LoadTexture("./Resources/Images/bsorrow.png");

	eggCount_ = 0;
}

void Player::Update()
{
	/*
#pragma region Noviceのキー入力関連
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
#pragma endregion

	//プレイヤーの移動関数
	Move(keys);
	*/


#pragma region ImGui関連
#ifdef _DEBUG
	ImGui::Begin("eggCount_");
	ImGui::Text(" eggCount_ %d", eggCount_);
	ImGui::End();
#endif

#pragma endregion
}

void Player::Draw()
{
	//プレイヤーの範囲？(半径の2倍)
	Novice::DrawEllipse(int(position_.x), int(position_.y),int(radius_.x)*3, int(radius_.y)*3, 0.0f, color_, kFillModeWireFrame);
	//プレイヤーの描写(仮)
	Novice::DrawEllipse(int(position_.x), int(position_.y), int(radius_.x), int(radius_.y), 0.0f, color_, kFillModeSolid);
	//プレイヤーの画像(仮)
	Novice::DrawSprite(int(position_.x- radius_.x), int(position_.y- radius_.y), image_,1.0f,1.0f,0.0f,color_);
}

void Player::Move(char* keys)
{
	//斜め移動
	if (keys[DIK_LEFT] && keys[DIK_UP]) {
		position_.x -= (speed_.x / 1.41f);
		position_.y -= (speed_.y / 1.41f);
	}
	else if (keys[DIK_RIGHT] && keys[DIK_UP]) {
		position_.x += (speed_.x / 1.41f);
		position_.y -= (speed_.y / 1.41f);
	}
	else if (keys[DIK_LEFT] && keys[DIK_DOWN]) {
		position_.x -= (speed_.x / 1.41f);
		position_.y += (speed_.y / 1.41f);
	}
	else if (keys[DIK_RIGHT] && keys[DIK_DOWN]) {
		position_.x += (speed_.x / 1.41f);
		position_.y += (speed_.y / 1.41f);
	}

	//直線移動
	else if (keys[DIK_LEFT]) {
		position_.x -= speed_.x;
	}
	else if (keys[DIK_RIGHT]) {
		position_.x += speed_.x;
	}
	else if (keys[DIK_UP]) {
		position_.y -= speed_.y;
	}
	else if (keys[DIK_DOWN]) {
		position_.y += speed_.y;
	}
}

void Player::OnFChildCollision()
{
	color_ = RED;
	//ここで子供カウント
	eggCount_++;
}

void Player::OnEnemyCollision()
{
	eggCount_--;
}
