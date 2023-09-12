#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"
#include "ScreenSize.h"
#include "UtilityStruct.h"

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
	void Update(char*keys);

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(char* keys);

	/// <summary>
	/// 当たった時の処理(子供(F))
	/// </summary>
	void OnFChildCollision();

	/// <summary>
	/// 当たった時の処理(敵)
	/// </summary>
	void OnEnemyCollision();

	/// <summary>
	/// 軍隊あてたときの処理
	/// </summary>
	void OnPbAttackCollision();

	///getter&setter

	/// <summary>
	/// プレイヤーの場所G
	/// </summary>
	Vector2 GetPlayerPosition() { return position_; };

	/// <summary>
	/// プレイヤーの半径G
	/// </summary>
	Vector2 GetPlayerRadius() { return radius_; };

	/// <summary>
	/// プレイヤーのスピードG
	/// </summary>
	Vector2 GetPlayerSpeed() { return speed_; };

	/// <summary>
	/// 子(F)のカウント
	/// </summary>
	/// <returns></returns>
	uint32_t GetEggCount() { return eggCount_; };

private:

	/// <summary>
	/// プレイヤーの場所
	/// </summary>
	Vector2 position_ = { 0.0f,0.0f };
	/// <summary>
	/// プレイヤーの半径
	/// </summary>
	const Vector2 radius_ = {64.0f,64.0f};
	/// <summary>
	/// プレイヤーの色
	/// </summary>
	uint32_t color_ = WHITE;
	/// <summary>
	/// プレイヤーのスピード
	/// </summary>
	Vector2 speed_ = { 4.0f,4.0f };

	UnitTexture8 image_ ;
	uint32_t nowImage_;
	uint32_t animNum_ = 0;
	const uint32_t animSpeed_ = 7;
	uint32_t animFream_ = animSpeed_;

	uint32_t eggCount_ = 0;

};

