#pragma once
#include "Vector2.h"
#include <Novice.h>
#include <cstdint>
#include "ImGuiManager.h"

class FieldChild
{
public:
	~FieldChild();
	FieldChild();
	void Initialize(Vector2 PlayerPos, Vector2 ScrollPos);
	void Update(Vector2 ScrollPos);
	void Draw();
	bool GetIsArrive() {return isArrive_;}
	static const int spawnWaitTime_ = 1 * 60; //スポーンするまでの時間

	/// <summary>
	/// スクロール入った分位置のgetter
	/// </summary>
	Vector2 GetScreenPos() { return this->screenPos_; };

	/// <summary>
	/// 半径のgetter
	/// </summary>
	/// <returns></returns>
	Vector2 GetRadius() { return this->radius_; };

	/// <summary>
	/// 当たった時の処理
	/// </summary>
	void OnCollision();

private:
	Vector2 pos_;
	const int spawnDistance_ = 200; //プレイヤーからの半径距離(近すぎるところにスポーンしないように)
	uint32_t texture_ = Novice::LoadTexture("./Resources/Images/FieldChild.png");

	uint32_t color_ = WHITE;
	
	int waitTime_ = 0; //待機時間
	int secondCount_ = 0; //秒カウント用
	const int deadTime_ = 7; //デスポーンする時間(秒)
	bool isArrive_ = true;

	/// <summary>
	/// スクロール入った分位置(スクリーンでの位置) 
	/// </summary>
	Vector2 screenPos_ = {0.0f,0.0f};

	/// <summary>
	/// スクロール入った分位置(スクリーンでの位置) 
	/// </summary>
	Vector2 scrollPos_ = { 0.0f,0.0f };

	//半径(画像サイズ的に多分) 
	Vector2 radius_ = {16.0f,16.0f};
};

