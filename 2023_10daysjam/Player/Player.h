#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"

/// <summary>
/// プレイヤーのクラス
/// </summary>
class Player
{
public:

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

private:

	/// <summary>
	/// プレイヤーの場所、半径、色、スピード
	/// </summary>
	Vector2 position_ = { 0.0f,0.0f };
	const Vector2 radish_ = {32.0f,32.0f};
	uint32_t color_ = WHITE;
	Vector2 speed_ = { 4.0f,4.0f };

};

