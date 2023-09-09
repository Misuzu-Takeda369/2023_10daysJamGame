#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"
#include "ScreenSize.h"

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
	BackGround(Vector2 playerRadish);

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

	/// <summary>
	/// 背景のループ用(ここに来たら移動するよーってやつ)
	/// </summary>
	void ChangeBackGround();

	/// <summary>
	///　画面に映る変数に変換関数
	/// </summary>
	void WorldtoScreen();

	///getter&setter

	/// <summary>
	/// スクロールの場所(初期位置)G
	/// </summary>
	Vector2 GetWorldPosition() { return wouldPosition_; };

	/// <summary>
	/// スクロールののスピードG
	/// </summary>
	Vector2 GetBackGroundSpeed() { return speed_; };

	/// <summary>
	/// スクロールした距離G
	/// </summary>
	Vector2 GetScrollPosition() { return scrollPosition_; };

	


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
	/// プレイヤーの半径
	/// </summary>
	Vector2 playerRadish_ = {0.0f,0.0f};

	/// <summary>
	/// 背景のサイズ
	/// </summary>
	Vector2 backGroundSize_ = { kWindowWidth,kWindowHeight };
	Vector2 HalfBackGroundSize_ = { khalfWidth,khalfHeight };

	/// <summary>
	/// 画像
	/// </summary>
	uint32_t image_ = 0;

	/// <summary>
	/// ワールド座標のポジション(画像の初期位置)複数
	/// </summary>
	Vector2 wouldBacksPos_[9] = {

	};

	/// <summary>
	/// スクロールのポジション(複数)
	/// </summary>
	Vector2 scrollBacksPos_[9] = {

	};

	/// <summary>
	/// 画面に適応されるやつの変数(複数)
	/// </summary>
	Vector2 ScreensPos_[9] = {

	};


};
