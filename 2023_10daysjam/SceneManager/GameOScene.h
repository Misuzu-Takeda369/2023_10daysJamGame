#pragma once

#include "Input.h"
/// <summary>
/// ゲームオーバーシーンのクラス
/// </summary>

class GameOScene 
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameOScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameOScene();

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
};
