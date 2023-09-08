#include "Enemy.h"
#include "Novice.h"
#include "ScreenSize.h"
#include <stdlib.h>
#include <time.h>
#include "Function/Function.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(Vector2 PlayerPos, Vector2 ScrollPos)
{

#pragma region 敵の更新
	//スクロールした値分
	scrollPos_ = { ScrollPos.x ,ScrollPos.y };

	Vector2 plusRange = { 0.0f,0.0f };
	Vector2 sign = { 1.0f,1.0f };

	color_ = WHITE;

	srand(int(time(nullptr)));
	int random = rand() % 10;
	plusRange.x = float(rand() % 100 + 1);
	//posX設定
	if (random > 4) {
		sign.x = -1;
	}

	//子供生成位置をプレイヤーの位置＋背景が動いた分に変更
	pos_.x = PlayerPos.x + scrollPos_.x + (float(spawnDistance_ * sign.x)) + float(plusRange.x * sign.x);
	plusRange.y = float(rand() % 100 + 1);
	//posY設定
	//int random = rand() % 10;
	random = rand() % 10;
	if (random > 4) {
		sign.y = -1;
	}

	//子供生成位置をプレイヤーの位置＋背景が動いた分に変更
	pos_.y = PlayerPos.y + scrollPos_.y + (float(spawnDistance_ * sign.y)) + float(plusRange.y * sign.y);
	//スクリーンの座標
	screenPos_ = { pos_.x ,pos_.y };
	playerStalkingPos_ = { PlayerPos.x,PlayerPos.y };

#pragma endregion

#pragma region 敵のtype
	enemyMoveType_ = RandomRange(0, 3);

	switch (enemyMoveType_)
	{
	case sideway:

		speed_ = SpeedRam();
		break;
	case vertically:

		speed_ = SpeedRam();
		break;
	case stalking:

		speed_ = int(1.5f);
		break;
	default:
		speed_ = 0;
		break;
	}
#pragma endregion
	//pos_.x = 200;
	//pos_.y = 200;
	radius_ = 64;
	//speed_ = 3;
	color_ = WHITE;

	enemyMoveCheck_ = { 0.0f,0.0f };

	texture_ = Novice::LoadTexture("./Resources/Images/egg1.png");
	//texture2_ = Novice::LoadTexture("./Resources/Images/egg2.png");

}

void Enemy::Update(Vector2 ScrollPos)
{

	switch (enemyMoveType_)
	{
	case sideway:

		//横の移動
		pos_.x += speed_;
		enemyMoveCheck_.x += speed_;

		if (enemyMoveCheck_.x <= -khalfWidth) {
			//speed_ = speed_ + 3;
			speed_ = -speed_;
		}
		if (enemyMoveCheck_.x >= khalfWidth) {
			//speed_ = speed_ - 3;
			speed_ = -speed_;
		}

		break;
	case vertically:

		////縦の移動
		pos_.y += speed_;
		enemyMoveCheck_.y += speed_;

		
		if (enemyMoveCheck_.y <= -khalfHeight) {
			speed_ = -speed_;
		}
		else if (enemyMoveCheck_.y >= khalfHeight) {
			speed_ = -speed_;
		}
		

		break;
	case stalking:
	
		MoveStalking();

	default:
		//speed_ = 0;
		break;
	}


#pragma region 敵のアニメーション(後で関数作る)
	animationFrame_--;

	if (animationFrame_ <= 0) {
		animationNum_=AnimationNum(animationNum_);
		animationFrame_ = 30;
	}

#pragma endregion 

	secondCount_++;
	if (secondCount_ >= 60) {
		waitTime_++;
		secondCount_ = 0;
	}
	if (waitTime_ >= deadTime_) {
		isArrive_ = false;
	}

	//スクロールした値分(背景は毎フレーム変動するのでそのリカバリー)
	scrollPos_ = { ScrollPos.x ,ScrollPos.y };
	screenPos_ = { pos_.x - scrollPos_.x  ,pos_.y - scrollPos_.y };



}

void Enemy::Draw()
{
	Novice::DrawEllipse(int(screenPos_.x), int(screenPos_.y), int(radius_), int(radius_), 0.0f, int(color_), kFillModeSolid);

	//Novice::DrawSprite(int(pos_.x - radius_), int(pos_.y - radius_), texture_, 1, 1, 0.0f, color_);

	//画像その1
	Novice::DrawSpriteRect(int(screenPos_.x - radius_), int(screenPos_.y - radius_), 128 * animationNum_, 0, radius_ * 2, radius_ * 2, texture_, 0.333333333f, 1, 0.0f, color_);

	//画像その2
	//Novice::DrawSpriteRect(int(pos_.x - radius_), int(pos_.y - radius_)+128, 128 * animationNum_, 0, 128, 128, texture2_, 0.333333333f, 1, 0.0f, color_);

}

void Enemy::OnCollision()
{

}

int Enemy::SpeedRam()
{
	int speed = 0;
	enemySpeedType_ = RandomRange(0, 1);
	if (enemySpeedType_ == 0) {
		speed = 3;
	}
	else if (enemySpeedType_ == 1) {
		speed = 12;
	}

	return speed;

}

void Enemy::MoveStalking()
{
	
	if (screenPos_.x >= playerStalkingPos_.x && screenPos_.y >= playerStalkingPos_.y) {
		pos_.x -= speed_;
		pos_.y -= speed_;
	}
	else if (screenPos_.x < playerStalkingPos_.x && screenPos_.y >= playerStalkingPos_.y) {
		pos_.x += speed_;
		pos_.y -= speed_;
	}

	else if (screenPos_.x >= playerStalkingPos_.x && screenPos_.y < playerStalkingPos_.y) {
		pos_.x -= speed_;
		pos_.y += speed_;
	}
	else if (screenPos_.x < playerStalkingPos_.x && screenPos_.y < playerStalkingPos_.y) {
		pos_.x += speed_;
		pos_.y += speed_;
	}

	
}
