#pragma once

#include "Input.h"
#include "Novice.h"
#include "ScreenSize.h"
/// <summary>
/// ゲームクリアシーンのクラス
/// </summary>

class GameCScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameCScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCScene();

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
	/// エフェクト関連
	/// </summary>
	void GameCEffectEnd();

	/// <summary>
	/// エフェクト関連
	/// </summary>
	void GameCEffectStart();


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

	// 仮シーン変換用キー
	Input* inputchagekey_ = nullptr;

	//エフェクトに使った位置
	Vector2 effectPos_ = { 0.0f,0.0f };

	//エフェクトに使ったフラグその1
	bool effectFlagEnd_ = false;
	//エフェクトに使ったフラグその2
	bool effectFlagStart_ = true;

	uint32_t image1_ = 0;
	uint32_t image2_ = 0;

};
