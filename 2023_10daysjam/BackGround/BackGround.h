#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"

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


	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(char* keys);

	/// <summary>
	/// 背景が動かなくなる条件
	/// </summary>
	void MoveStop(char* keys);


	///getter&setter

	/// <summary>
	/// スクロールのの場所G
	/// </summary>
	Vector2 GetWorldPosition() { return wouldPosition_; };

	/// <summary>
	/// スクロールののスピードG
	/// </summary>
	Vector2 GetBackGroundSpeed() { return speed_; };

private:

	/// <summary>
	/// ワールド座標のポジション(画像の初期位置)
	/// </summary>
	Vector2 wouldPosition_ = { 0.0f,0.0f };

	/// <summary>
	/// スクロールのポジション
	/// </summary>
	Vector2 scrollPosition_ = { 0.0f,0.0f };

	/// <summary>
	/// スクロールのスピード
	/// </summary>
	Vector2 speed_ = { 2.0f,2.0f };

	/// <summary>
	/// 画像
	/// </summary>
	uint32_t image_ = 0;

};
