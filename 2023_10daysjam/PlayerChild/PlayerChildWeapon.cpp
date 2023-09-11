#include "PlayerChildWeapon.h"
#include "Function/Function.h"
#include <Novice.h>

PlayerChildWeapon::PlayerChildWeapon()
{
}

PlayerChildWeapon::~PlayerChildWeapon()
{
}

void PlayerChildWeapon::Initialize(Type type)
{
	type_ = type;
	GetTexture();

	bulletPos_ = { pos_ };
	bulletMovePos_ = { 0.0f,0.0f };
	bulletLive_ = false;
	bulletDirection_ = none;
	bulletSpeed_ = { 6.0f,6.0f };
	movePos_ = { 0.0f,0.0f };
	screenBulletPos_ = { bulletPos_.x + bulletMovePos_.x ,bulletPos_.y + bulletMovePos_.y };
}

void PlayerChildWeapon::Update(Vector2 child)
{
	pos_ = child;
	BulletMove();
	switch (type_)
	{
	case None:
		break;
	case DefaultType:
		//攻撃しない あとで変える
		isAttacking_ = false;
		break;
	case Circle:
		//鎌を振り回す　当たり判定はまだ
		if (isAttacking_) {

			if (!bulletLive_) {
				bulletLive_ = true;
				BulletBorn();
			}

			attackTimer_++;
			if (attackTimer_ >= 10) {
				attackTimer_ = 0;
				isAttacking_ = false;
			}
		}

		break;
	default:
		break;
	}

	screenBulletPos_ = { bulletPos_.x + bulletMovePos_.x ,bulletPos_.y + bulletMovePos_.y };
}

void PlayerChildWeapon::Draw()
{
	Novice::DrawSprite(int(pos_.x), int(pos_.y), texture_, 1, 1, 0, WHITE);
	if (isAttacking_) {
		Novice::DrawSprite(int(pos_.x), int(pos_.y), effectTexture_, 1, 1, 0, WHITE);
	}

	
	if (bulletLive_){
		Novice::DrawSprite(int(screenBulletPos_.x), int(screenBulletPos_.y), effectTexture_, 1, 1, 0, WHITE);
	}
	
}

void PlayerChildWeapon::SetIsAttacking(bool flag)
{
	isAttacking_ = flag;
}


void PlayerChildWeapon::BulletMove()
{
	if (bulletLive_) {

		bulletMovePos_.x += bulletSpeed_.x * movePos_.x;
		bulletMovePos_.y -= bulletSpeed_.y * movePos_.y;

		if ((bulletMovePos_.x* bulletMovePos_.x)+ (bulletMovePos_.y * bulletMovePos_.y) >= ((khalfWidth* khalfHeight)+ (khalfWidth * khalfHeight))) {
			bulletLive_ = false;
			bulletMovePos_ = {0.0f,0.0f};
			screenBulletPos_ = { pos_.x, pos_.y };
		}
	}
}

void PlayerChildWeapon::BulletBorn()
{
	//方向を決める
	bulletDirection_ = RandomRange(0,7);
	bulletPos_ = { pos_ };
#pragma region 角度決定
	switch (bulletDirection_)
	{
	case up:
		theta = 90.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	case right:
		theta = 0.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	case down:

		theta = 270.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	case left:

		theta = 180.0f;
		movePos_ = { cosf(theta),sinf(theta) };
	
		break;

	case upRight:
		theta = 45.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	case downRight:
		theta = 225.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		

		break;

	case downLeft:

		theta = 315.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	case upLeft:

		theta = 135.0f;
		movePos_ = { cosf(theta),sinf(theta) };
		
		break;

	default:
		break;
	}
#pragma endregion 
}

void PlayerChildWeapon::GetTexture()
{
	switch (type_)
	{
	case None:
		break;
	case DefaultType:
		texture_ = Novice::LoadTexture("./Resources/Images/weapon1.png");
		effectTexture_ = Novice::LoadTexture("./Resources/Images/weapon1Effect.png");
		break;
	case Circle:
		texture_ = Novice::LoadTexture("./Resources/Images/weapon1.png");
		effectTexture_ = Novice::LoadTexture("./Resources/Images/weapon1Effect.png");
		break;
	default:
		break;
	}
}
