#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"

/// <summary>
/// スクロール(背景)のクラス
/// </summary>
class BackGround
{
public:

	///関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	BackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGround();

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


	///getter&setter

	/// <summary>
	/// スクロールのの場所G
	/// </summary>
	Vector2 GetBackGroundPosition() { return position_; };

	/// <summary>
	/// スクロールののスピードG
	/// </summary>
	Vector2 GetBackGroundSpeed() { return speed_; };

private:

	/// <summary>
	/// スクロールの場所
	/// </summary>
	Vector2 position_ = { 0.0f,0.0f };
	
	/// <summary>
	/// スクロールのスピード
	/// </summary>
	Vector2 speed_ = { 0.0f,0.0f };

	uint32_t image_;

};
