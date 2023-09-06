#pragma once
#include "Vector2.h"
#include <Novice.h>
#include <cstdint>
class FieldChild
{
public:
	~FieldChild();
	FieldChild();
	void Initialize(Vector2 PlayerPos);
	void Update();
	void Draw();
	bool GetIsArrive() {return isArrive_;}
	static const int spawnWaitTime_ = 1 * 60; //スポーンするまでの時間
private:
	Vector2 pos_;
	const int spawnDistance_ = 200; //プレイヤーからの半径距離(近すぎるところにスポーンしないように)
	uint32_t texture_ = Novice::LoadTexture("./Resources/Images/FieldChild.png");
	
	int waitTime_ = 0; //待機時間
	int secondCount_ = 0; //秒カウント用
	const int deadTime_ = 7; //デスポーンする時間(秒)
	bool isArrive_ = true;

};

