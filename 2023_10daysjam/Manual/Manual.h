#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "DirectXCommon.h"
#include "ScreenSize.h"
#include "Input.h"


class Manual
{
public:
	/// <summary>
/// コンストクラタ
/// </summary>
	Manual();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Manual();

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

	/// getterとsetter

	/// <summary>
	/// 説明が出てくるフラグ
	/// </summary>
	/// <param name="frag"></param>
	void SetFrag(bool frag) {  frag_ = frag; };

	/// <summary>
	/// 説明が出てくるフラグ
	/// </summary>
	/// <param name="frag"></param>
	bool GetFrag() { return frag_ ; };

private:

	//z押したら
	bool frag_ = false;

	bool returnfrag_=false;

	//初期位置
	Vector2 pos_ = {0.0f,0.0f};

	//動いた距離
	Vector2 movePos_ = { 0.0f,0.0f };

	//スピード
	Vector2 speed_ = {0.0f,0.0f};

	//画像
	uint32_t image1_ = 0;
	uint32_t image2_ = 0;

	Input* inputchagekey_ = nullptr;

	uint32_t cooltime_ =60;

};

