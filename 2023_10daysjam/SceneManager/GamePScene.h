#pragma once

#include "Novice.h"
#include "Input.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"
#include <list>
#include "FieldChild/FieldChild.h"
#include "Function/Function.h"
#include "PlayerChild/PlayerChild.h"
#include "Enemy/Enemy.h"


/// <summary>
/// プレイシーンのクラス
/// </summary>

class GamePScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GamePScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 初期化(変数あり)
	/// </summary>
	void Initialize(Vector2 effectpos);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 前景描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たり判定管理関数
	/// </summary>
	void Attack();


	/// <summary>
	/// 敵の生成？
	/// </summary>
	void AddEnemies(Vector2 playerPos);
	
	/// <summary>
	/// 複数の敵の更新
	/// </summary>
	void EnemiesUpdate();

	/// <summary>
	/// 子供(Back)の生成
	/// </summary>
	void AddPlayerChild();
	/// <summary>
	/// 子供(Back)の更新
	/// </summary>
	void PlayerChildUpdate();

	/// <summary>
	/// 子供(F)の生成
	/// </summary>
	void AddFieldChild(Vector2 playerPos);
	/// <summary>
	/// 子供(F)敵の更新
	/// </summary>
	void FieldChildUpdate();

	/// <summary>
	/// プレイヤーと敵の衝突がtrueの時に使う
	/// </summary>
	void PlayerChildLost();

	/// <summary>
	/// エフェクト関連
	/// </summary>
	void GamePEffectEnd();

	/// <summary>
	/// エフェクト関連
	/// </summary>
	void GamePEffectStart();


	void PlayerChildLostAttack();

	///getter&setter
	
	/// <summary>
	/// シーン変更管理のゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagChange() { return flagChange_; };

	/// <summary>
	/// シーン変更管理のセッター
	/// </summary>
	/// <returns></returns>
	bool SetFlagChange(bool flagChange) { return this->flagChange_ = flagChange; };


	/// <summary>
	/// クリアとoverを判別するためのフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagGameOver() { return flagGameOver_; };

	/// <summary>
	/// エフェクト用の位置ゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetEffectPos() { return effectPos_; };

	/// <summary>
	/// エフェクト用の位置セッター
	/// </summary>
	/// <returns></returns>
	Vector2 SetEffectPos(Vector2 effectpos) { effectPos_ = effectpos; };


private:
	// シーン変更できるかどうか
	bool flagChange_ = false;
	//クリアとoverを判別するためのフラグ
	bool flagGameOver_ = false;

	// 仮シーン変換用キー
	Input* inputchagekey_ = nullptr;

	//プレイヤーのクラス
	Player* player_ = nullptr;
	

	//背景のクラス
	BackGround* backGround_ = nullptr;

	//子(フィールド)関連
	std::list<FieldChild*> fieldChild_;
	int fieldChildWaitTimer_ = 0;

	//子(プレイヤー)
	std::list<PlayerChild*> playerChild_;
	uint32_t childCounter_ = 0;

	
	

	//敵関連のクラス
	//Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemy_;
	int enemiesWaitTimer_ = 0;

	//仮挙動(多分再利用されてる)
	uint32_t CountNum_ = 0;

	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	//エフェクトに使った位置
	Vector2 effectPos_ = { 0.0f,0.0f };

	//エフェクトに使ったフラグその1
	bool effectFlagEnd_ = false;
	//エフェクトに使ったフラグその2
	bool effectFlagStart_ = true;

	//ゲームをうごかしているか
	bool GameMove_ = false;

	bool AttackFlag_ = true;
	
	uint32_t AttackTime_ = 180;

	//何故か直接参照すると数が莫大に増えあがったの(プレイヤーが管理していたやつも子供数える用のやつも)で受け渡し用
	int eggCountNum_ = 0;

	//音楽
	uint32_t soundBGM_ = 0;

	//音ならす用変数
	int bgmHandle_ = 0;

};
