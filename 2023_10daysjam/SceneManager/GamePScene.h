#pragma once

#include "Novice.h"
#include "Input.h"
#include "Player/Player.h"

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
	/// シーン変更管理のゲッター
	/// </summary>
	/// <returns></returns>
	bool GetFlagChange() { return flagChange_; };

	/// <summary>
	/// シーン変更管理のセッター
	/// </summary>
	/// <returns></returns>
	bool SetFlagChange(bool flagChange) { return this->flagChange_ = flagChange; };


private:
	// シーン変更できるかどうか
	bool flagChange_ = false;

	// 仮シーン変換用キー
	Input* inputchagekey_ = nullptr;


	//プレイヤーのクラス
	Player* player_ = nullptr;

	
};
