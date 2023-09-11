#pragma once
#include <cstdint>
#include "Vector2.h"
#include "UtilityStruct.h"
#include "ScreenSize.h"
/// <summary>
/// 子の攻撃用のクラス
/// </summary>
class PlayerChildWeapon
{
public:
	PlayerChildWeapon();
	~PlayerChildWeapon();
	void Initialize(Type type);
	void Update(Vector2 child);
	void Draw();
	void SetIsAttacking(bool flag);

	/// <summary>
	///	弾の動き関連
	/// </summary>
	void BulletMove();

	/// <summary>
	/// 弾生成
	/// </summary>
	void BulletBorn();

	/// <summary>
	/// スクリーンに写る位置のゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetScreenBulletPos() { return screenBulletPos_; };

	/// <summary>
	/// 弾が生存しているかのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetBulletLive() { return bulletLive_; };

private:
	//攻撃出来るかのモード？
	Type type_ = Type(0);
	void GetTexture();
	Vector2 pos_;
	uint32_t texture_ = 0;
	uint32_t effectTexture_ = 0;
	bool isAttacking_ = false;
	int attackTimer_ = 0;

	//打たれた弾の位置
	Vector2 bulletPos_ = {0.0f,0.0f};

	//スクリーン用位置(ほぼゲッター用)
	Vector2 screenBulletPos_ = { 0.0f,0.0f };

	//移動した分
	Vector2 bulletMovePos_ = {0.0f,0.0f};

	//弾が現存しているか
	bool bulletLive_ = false;

	//方向のtype
	enum BulletDirection
	{
		 up,  right,  down, left, upRight, downRight, downLeft,upLeft,none
	};

	//方向のtype管理する奴
	uint32_t bulletDirection_ = none;

	//スピード
	Vector2 bulletSpeed_ = {0.0f,0.0f};

	//角度ごとの大きさ(スピード)
	Vector2 movePos_ = {0.0f,0.0f};
	//角度
	float theta = 0.0f;
};

