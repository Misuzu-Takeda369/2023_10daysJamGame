﻿#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"

/// <summary>
/// プレイヤーのクラス
/// </summary>
class Player
{
public:

	///関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(char* keys);

	/// <summary>
	/// 当たった時の処理
	/// </summary>
	void OnCollision();

	///getter&setter

	/// <summary>
	/// プレイヤーの場所G
	/// </summary>
	Vector2 GetPlayerPosition() { return position_; };

	/// <summary>
	/// プレイヤーの半径G
	/// </summary>
	Vector2 GetPlayerRadish() { return radish_; };

	/// <summary>
	/// プレイヤーのスピードG
	/// </summary>
	Vector2 GetPlayerSpeed() { return speed_; };

private:

	/// <summary>
	/// プレイヤーの場所
	/// </summary>
	Vector2 position_ = { 0.0f,0.0f };
	/// <summary>
	/// プレイヤーの半径
	/// </summary>
	const Vector2 radish_ = {32.0f,32.0f};
	/// <summary>
	/// プレイヤーの色
	/// </summary>
	uint32_t color_ = WHITE;
	/// <summary>
	/// プレイヤーのスピード
	/// </summary>
	Vector2 speed_ = { 4.0f,4.0f };

	uint32_t image_ ;

};
