#include "Enemy.h"
#include "Novice.h"
#include "ScreenSize.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pos_.x = 200;
	pos_.y = 200;
	radius_ = 25;
	speed_ = 3;
	color_ = WHITE;

	//texture_ = Novice::LoadTexture("./Resources/Images/.png");
}

void Enemy::Update()
{
	//横の移動
	pos_.x += speed_;
	if (pos_.x <= 0 + radius_) {
		speed_ = speed_ + 3;
	}
	if (pos_.x >= kWindowWidth - radius_) {
		speed_ = speed_ - 3;
	}

	////縦の移動
	//pos_.y += speed_;
	//if (pos_.y <= 0 + radius_) {
	//	speed_ = speed_ + 3;
	//}
	//if (pos_.y >= kWindowHeight - radius_) {
	//	speed_ = speed_ - 3;
	//}


}

void Enemy::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, int(color_), kFillModeSolid);
	
	//Novice::DrawSprite(int(pos_.x - radius_), int(pos_.y - radius_), texture_, 1, 1, 0.0f, color_);
}

void Enemy::OnCollision()
{

}
