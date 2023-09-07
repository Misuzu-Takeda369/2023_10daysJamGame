#pragma once
#include "Vector2.h"
#include <cstdint>
#include "UtilityStruct.h"
#include "PlayerChild/PlayerChildWeapon.h"
#include <Novice.h>
class PlayerChild
{
public:
	~PlayerChild();
	PlayerChild();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="forwardPos">最後尾の座標 いなければプレイヤーの座標がはいるように</param>
	/// <param name="playerPos">プレイヤーの座標</param>
	void Initialize(const Vector2& forwardPos, const Vector2& playerPos, Vector2 ScrollPos);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="forwardPos">前の子の座標 いなければプレイヤーの座標</param>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="playerDirection">プレイヤーの向き</param>
	void Update(const Vector2& forwardPos, const Vector2& playerPos, Vector2 ScrollPos);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	void SetDirection(char* preKeys);

	Vector2 GetPos() { return pos_; }
	void SetChildNumber(int num);
	int GetChildNumber() { return childNumber_; }
	void SetIsArrive(bool flag);
	bool GetIsArrive() { return isArrive_; }

private:


	static const int typeTotal_ = 1; //  タイプ総数
	/// <summary>
	/// 子のタイプ
	/// </summary>
	enum Type
	{
		None, //0 
		DefaultType, //1 あとで名前変える
	};

	/// <summary>
	/// Initializeの中に入れる
	/// </summary>
	void SetChildType();

	Vector2 pos_;
	Vector2 screenPos_;
	const float distanceRadius = 32; //他の子やプレイヤーとの距離
	UnitColor color_;
	Type childType_ = None;
	int childDirection_ = 0;//向き

	int growCountTimer_ = 0; //成長タイマー
	int growTime_ = 0; //成長時間の設定に使う変数
	static const int growTimeBase_ = 5 * 60; //成長時間の基準用 定数
	bool isArrive_ = true; //生存フラグ
	bool isGrow_ = false; //成長フラグ

	bool isSpawning_ = true; //スポーンモーション用(リソース作る余裕があれば使う)

	uint32_t babyTexture_ = 0; //成長前
	uint32_t adultTexture_ = 0; //成長後
	int textureSize_ = 64;
	int radius_ = textureSize_ / 2;

	PlayerChildWeapon* weapon_ = nullptr;
	int playerDirection_ = 1;
	int childNumber_ = 0;


};

