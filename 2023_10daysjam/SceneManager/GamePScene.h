#pragma once

#include "Novice.h"
#include "Input.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"
#include <list>
#include "FieldChild/FieldChild.h"
#include "Function/Function.h"

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
	/// たまごの個数(クリアとgameoverの判定用)ゲッター
	/// </summary>
	/// <returns></returns>
	//uint32_t GetEggNum() { return eggNum_; };

private:
	// シーン変更できるかどうか
	bool flagChange_ = false;
	//たまごの個数(クリアとoverを判別するため)
	//uint32_t eggNum_ = 0;

	// 仮シーン変換用キー
	Input* inputchagekey_ = nullptr;

	//プレイヤーのクラス
	Player* player_ = nullptr;
	

	//背景のクラス
	BackGround* backGround_ = nullptr;

	//子(フィールド)関連
	void AddFieldChild(Vector2 playerPos);
	void FieldChildUpdate();
	std::list<FieldChild*> fieldChild_;
	int fieldChildWaitTimer_ = 0;

};
