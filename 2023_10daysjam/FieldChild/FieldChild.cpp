#include "FieldChild.h"
#include <stdlib.h>
#include <time.h>

FieldChild::~FieldChild()
{
}

FieldChild::FieldChild()
{
}

void FieldChild::Initialize(Vector2 PlayerPos, Vector2 ScrollPos)
{

	//スクロールした値分
	scrollPos_ = { ScrollPos.x ,ScrollPos.y };
	


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

	//子供生成位置をプレイヤーの位置＋背景が動いた分に変更
	pos_.x = PlayerPos.x+ scrollPos_.x + (float(spawnDistance_ * sign.x))+float(plusRange.x*sign.x);
	//posY設定
	random = rand() % 10;
	if (random > 4) {
		sign.y = -1;
	}

	//子供生成位置をプレイヤーの位置＋背景が動いた分に変更
	pos_.y = PlayerPos.y + scrollPos_.y + (float(spawnDistance_ * sign.y))+float(plusRange.y*sign.y);

	//スクリーンの座標
	screenPos_ = { pos_.x - scrollPos_.x ,pos_.y - scrollPos_.y };
}

void FieldChild::Update(Vector2 ScrollPos)
{
	//子供(F)が現存している時間(60になったら消える)
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
	screenPos_ = { pos_.x - scrollPos_.x ,pos_.y - scrollPos_.y };
	
}

void FieldChild::Draw()
{
	if (isArrive_) {
		//スクロール入れた分に変更
		Novice::DrawSprite(int(screenPos_.x), int(screenPos_.y), texture_, 1, 1, 0, WHITE);
	}
}
