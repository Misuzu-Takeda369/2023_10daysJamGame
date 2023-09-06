#include "FieldChild.h"
#include <stdlib.h>
#include <time.h>

FieldChild::~FieldChild()
{
}

FieldChild::FieldChild()
{
}

void FieldChild::Initialize(Vector2 PlayerPos)
{
	srand(int(time(nullptr)));
	int random = rand() % 10;
	Vector2 plusRange;
	plusRange.x = float(rand() % 100 + 1);
	plusRange.y = float(rand() % 100 + 1);
	Vector2 sign = {1.0f,1.0f};
	//posX設定
	if (random > 4) {
		sign.x = -1;
	}
	pos_.x = PlayerPos.x + (float(spawnDistance_ * sign.x))+float(plusRange.x*sign.x);
	//posY設定
	random = rand() % 10;
	if (random > 4) {
		sign.y = -1;
	}
	pos_.y = PlayerPos.y + (float(spawnDistance_ * sign.y))+float(plusRange.y*sign.y);

	
}

void FieldChild::Update(Vector2 ScrollPos)
{
	secondCount_++;
	if (secondCount_ >= 60) {
		waitTime_++;
		secondCount_ = 0;
	}
	if (waitTime_ >= deadTime_) {
		isArrive_ = false;
	}

	scrollPos_ = { ScrollPos.x ,ScrollPos.y };
	screenPos_ = { pos_.x - scrollPos_.x ,pos_.y - scrollPos_.y };
	
}

void FieldChild::Draw()
{
	if (isArrive_) {
		Novice::DrawSprite(int(screenPos_.x), int(screenPos_.y), texture_, 1, 1, 0, WHITE);
	}
}
