﻿#pragma once

#include "Input.h"
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

	//仮挙動
	uint32_t CountNum_ = 0;
};
