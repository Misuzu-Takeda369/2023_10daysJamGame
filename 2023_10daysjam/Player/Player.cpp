#include "Player.h"
#include "Function/Function.h"

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
	position_ = { float(khalfWidth),float(khalfHeight) };
	color_ = WHITE;
	speed_ = { 2.0f,2.0f };
	image_.down = Novice::LoadTexture("./Resources/Images/bird_front.png");
	image_.downLeft= Novice::LoadTexture("./Resources/Images/bird_FL.png");
	image_.downRight= Novice::LoadTexture("./Resources/Images/bird_FR.png");
	image_.left= Novice::LoadTexture("./Resources/Images/bird_left.png");
	image_.right= Novice::LoadTexture("./Resources/Images/bird_right.png");
	image_.up= Novice::LoadTexture("./Resources/Images/bird_back.png");
	image_.upLeft= Novice::LoadTexture("./Resources/Images/bird_BL.png");
	image_.upRight= Novice::LoadTexture("./Resources/Images/bird_BR.png");
	nowImage_ = image_.down;
	eggCount_ = 0;


	effectOn_ = false;

	effeFrame_ = 60;
}

void Player::Update(char*keys)
{
	/*
#pragma region Noviceのキー入力関連
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
#pragma endregion
*/
	//プレイヤーの移動関数
	Move(keys);
	

	animFream_--;
	if (animFream_ <= 0) {
		animNum_ = AnimationNum(animNum_, 6);
		animFream_ = animSpeed_;
	}

	if (effectOn_) {
		effeFrame_--;
	}
	PlayerEffect();
#pragma region ImGui関連
#ifdef _DEBUG
	ImGui::Begin("eggCount_");
	ImGui::Text(" eggCount_ %d", eggCount_);
	ImGui::Text(" effeFrame_ %d", effeFrame_);

	ImGui::End();
#endif

#pragma endregion
}

void Player::Draw()
{
	//プレイヤーの範囲？(半径の2倍)
	Novice::DrawEllipse(int(position_.x), int(position_.y),int(radius_.x), int(radius_.y), 0.0f, color_, kFillModeWireFrame);
	//プレイヤーの描写(仮)
	//Novice::DrawEllipse(int(position_.x), int(position_.y), int(radius_.x), int(radius_.y), 0.0f, color_, kFillModeSolid);
	//プレイヤーの画像(仮)
	//Novice::DrawSprite(int(position_.x- radius_.x), int(position_.y- radius_.y), image_,1.0f,1.0f,0.0f,color_);
	Novice::DrawSpriteRect(int(position_.x - radius_.x), int(position_.y - radius_.y), 128 * animNum_, 0, 128, 128, nowImage_, (128.0f/(128.0f*6.0f)), 1, 0, color_);
}

void Player::Move(char* keys)
{
	//斜め移動
	if ((keys[DIK_LEFT] && keys[DIK_UP]) || (keys[DIK_A] && keys[DIK_W])) {
		//position_.x -= (speed_.x / 1.41f);
		//position_.y -= (speed_.y / 1.41f);
		nowImage_ = image_.upLeft;
	}
	else if ((keys[DIK_RIGHT] && keys[DIK_UP]) || (keys[DIK_D] && keys[DIK_W])) {
		//position_.x += (speed_.x / 1.41f);
		//position_.y -= (speed_.y / 1.41f);
		nowImage_ = image_.upRight;
	}
	else if ((keys[DIK_LEFT] && keys[DIK_DOWN]) || (keys[DIK_A] && keys[DIK_S])) {
		//position_.x -= (speed_.x / 1.41f);
		//position_.y += (speed_.y / 1.41f);
		nowImage_ = image_.downLeft;
	}
	else if ((keys[DIK_RIGHT] && keys[DIK_DOWN]) || (keys[DIK_D] && keys[DIK_S])) {
		//position_.x += (speed_.x / 1.41f);
		//position_.y += (speed_.y / 1.41f);
		nowImage_ = image_.downRight;
	}

	//直線移動
	else if (keys[DIK_LEFT]||keys[DIK_A]) {
		//position_.x -= speed_.x;
		nowImage_ = image_.left;
	}
	else if (keys[DIK_RIGHT]||keys[DIK_D]) {
		//position_.x += speed_.x;
		nowImage_ = image_.right;
	}
	else if (keys[DIK_UP]||keys[DIK_W]) {
		//position_.y -= speed_.y;
		nowImage_ = image_.up;
	}
	else if (keys[DIK_DOWN]||keys[DIK_S]) {
		//position_.y += speed_.y;
		nowImage_ = image_.down;
	}
}

void Player::OnFChildCollision()
{
	//color_ = RED;
	//ここで子供カウント
	eggCount_++;
}

void Player::OnEnemyCollision()
{
	color_ = 0x4D6996FF;
	eggCount_--;
	effectOn_ = true;
}

void Player::OnPbAttackCollision()
{
	eggCount_--;
}

void Player::PlayerEffect()
{

	if (effeFrame_ <= 0) {
		color_ = WHITE;
		effectOn_ = false;
		effeFrame_ = 60;
	}
}

