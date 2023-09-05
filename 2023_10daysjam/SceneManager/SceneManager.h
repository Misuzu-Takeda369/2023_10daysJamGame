#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
//#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
//ここからシーン変換
#include "TitleScene.h"
#include "GamePScene.h"
#include "GameCScene.h"
#include "GameOScene.h"

class SceneManager {
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

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
	/// ゲームモード
	/// </summary>
	enum SceneMode 
	{
		//タイトル、ゲームシーン、クリア、オーバー
		TitleMode, GPlayMode, GClearMode, GOverMode
	};

	/// <summary>
	/// シーン変換
	/// </summary>
	//void ChangeSceneMode();
	
	/// <summary>
	/// シーン管理変数のゲッター
	/// </summary>
	/// <returns></returns>
	uint32_t GetSceneNum() { return sceneNum_; };

	/// <summary>
	/// シーン管理変数のセッター
	/// </summary>
	/// <returns></returns>
	uint32_t SetSceneNum(uint32_t sceneNum) { this->sceneNum_ = sceneNum;};

	

private:
	// シーン
	uint32_t sceneNum_ = TitleMode;

	//上からタイトル、ゲームシーン、クリア、オーバー
	TitleScene* title_ = nullptr;
	GamePScene* gameP_ = nullptr;
	GameCScene* gameC_ = nullptr;
	GameOScene* gameO_ = nullptr;



	//仮シーン変換用キー
	Input* inputchagekey_ = nullptr;

	// シーン変更できるかどうか
	bool flagChange_ = false;
};
