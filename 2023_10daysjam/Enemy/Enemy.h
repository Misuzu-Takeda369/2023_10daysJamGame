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
	void Initialize(Vector2 PlayerPos, Vector2 ScrollPos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Vector2 ScrollPos);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たった時の処理
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 敵が現存しているか確認
	/// </summary>
	/// <returns></returns>
	bool GetIsArrive() { return isArrive_; };

	static const int spawnWaitTime_ = 2 * 60; //スポーンするまでの時間

	/// <summary>
	/// 普通か遅いかを決める関数
	/// </summary>
	/// <returns></returns>
	int SpeedRam();

	/// <summary>
	/// 敵のストーキングする動き用の関数
	/// </summary>
	void MoveStalking();

	/// <summary>
	/// スクロール入った分位置のgetter
	/// </summary>
	Vector2 GetScreenPos() { return this->screenPos_; };

	/// <summary>
	/// 半径のgetter
	/// </summary>
	/// <returns></returns>
	int GetRadius() { return this->radius_; };

	void EnemyEffect();

	bool GetEffectFrag() { return effectFrag_; };

	
private:

	Vector2 pos_ = { 0.f,0.f };
	int radius_ = 64;
	int speed_ = 0;
	uint32_t color_ = WHITE;

	uint32_t texture_ =0;
	uint32_t texture2_ = 0;

	//アニメーション関連
	uint32_t animationNum_ = 0;
	uint32_t animationFrame_ = 30;



	
	int waitTime_ = 0; //待機時間
	int secondCount_ = 0; //秒カウント用
	const int deadTime_ = 10; //デスポーンする時間(秒)
	bool isArrive_ = true;
	const int spawnDistance_ = 200; //プレイヤーからの半径距離(近すぎるところにスポーンしないように)

	/// <summary>
	/// スクロール入った分位置(スクリーンでの位置) 
	/// </summary>
	Vector2 screenPos_ = { 0.0f,0.0f };

	/// <summary>
	/// スクロール入った分位置(スクリーンでの位置) 
	/// </summary>
	Vector2 scrollPos_ = { 0.0f,0.0f };

	/// <summary>
	/// 敵の動き
	/// </summary>
	enum EnemyMovetype {
		//縦、横、ストーキング、動かん(ない)
		sideway, vertically,stalking,notMove,
	};
	///敵type
	uint32_t enemyMoveType_ = notMove;

	///スピードtype (0が普通、1が速い)
	uint32_t enemySpeedType_ = 0;

	/// <summary>
	/// 移動量
	/// </summary>
	Vector2 enemyMoveCheck_ = {0.0f,0.0f};

	/// <summary>
	/// ストーキング用のプレイヤーの位置
	/// </summary>
	Vector2 playerStalkingPos_ = { 0.0f,0.0f };

	/// <summary>
	/// エフェクトを起動できるか
	/// </summary>
	bool effectFrag_ = false;
	int effectFrame = 10;

	Vector2 rand_ = {0.0f,0.0f};

	int checkRang_ = 12;

	//音楽

	uint32_t soundEnemyhit_ = 0;

	//音ならす用変数
	int enemyhittHandle_ = -1;
};
