#pragma once

#include "Input.h"
#include "Novice.h"
#include "ScreenSize.h"
/// <summary>
/// タイトルシーンのクラス
/// </summary>

class TitleScene 
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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
	bool SetFlagChange(bool flagChange) {  return this->flagChange_ = flagChange; };

	void TitleEffect();
private:

	//シーン変更できるかどうか
	bool flagChange_ = false; 

	// 仮シーン変換用キー
	Input* inputchagekey_ = nullptr;

	Vector2 effectPos_ = {0.0f,0.0f};

	bool EffectFlag_ = false;
};
