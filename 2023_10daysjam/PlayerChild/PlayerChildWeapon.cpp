#include "PlayerChildWeapon.h"
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
}

void PlayerChildWeapon::Update(Vector2 child)
{
	pos_ = child;

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
	
}

void PlayerChildWeapon::Draw()
{
	Novice::DrawSprite(int(pos_.x), int(pos_.y), texture_, 1, 1, 0, WHITE);
	if (isAttacking_) {
		Novice::DrawSprite(int(pos_.x), int(pos_.y), effectTexture_, 1, 1, 0, WHITE);
	}
}

void PlayerChildWeapon::SetIsAttacking(bool flag)
{
	isAttacking_ = flag;
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
