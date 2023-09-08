#pragma once
#include "Vector2.h"
#include "Novice.h"
#include <cstdint>

/// <summary>
/// 敵のクラス
/// </summary>
class Enemy
{
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たった時の処理
	/// </summary>
	void OnCollision();

private:

	Vector2 pos_ = { 0.f,0.f };
	int radius_ = 0;
	int speed_ = 0;
	uint32_t color_ = WHITE;

	uint32_t texture_;
};
