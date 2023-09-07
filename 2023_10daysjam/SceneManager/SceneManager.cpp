#include "SceneManager/SceneManager.h"

#ifdef _DEBUG
#include "ImGuiManager.h"
#endif // DEBUG

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
	// それぞれデリート
	delete title_;
	delete gameP_;
	delete gameC_;
	delete gameO_;
}

void SceneManager::Initialize() {

	//シーン番号の初期化
	sceneNum_ = TitleMode;

	//インスタンス作成
	title_ = new TitleScene();
	gameP_ = new GamePScene();
	gameC_ = new GameCScene();
	gameO_ = new GameOScene();

	//初期化
	title_->Initialize();
	gameP_->Initialize();
	gameC_->Initialize();
	gameO_->Initialize();

	// 仮シーン変換用キー
	inputchagekey_ = Input::GetInstance();
}

void SceneManager::Update() {

	// シーン毎の更新
	switch (sceneNum_) {

	case TitleMode:

		title_->Update();

		//シーン変換
		//タイトルのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//ゲームプレイモードに移行する
		if (title_->GetFlagChange()) {
			sceneNum_ = GPlayMode;
			title_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			delete title_;
			title_ = new TitleScene();
			title_->Initialize();
		}
		break;

	case GPlayMode:
		gameP_->Update();

		//シーン変換
		//プレイモードのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameP_->GetFlagChange()) {

			if (gameP_->GetFlagGameOver()) {
				sceneNum_ = GOverMode;
			}
			else {
				sceneNum_ = GClearMode;
			}

			gameP_->SetFlagChange(false);
			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ(クリアとかでスコア作って表示するなら...) 
			delete gameP_;
			gameP_ = new GamePScene();
			gameP_->Initialize();

		}
		break;

	case GClearMode:
		gameC_->Update();

		//シーン変換
		//クリアシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameC_->GetFlagChange()) {
			sceneNum_ = TitleMode;
			gameC_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			delete gameC_;
			gameC_ = new GameCScene();
			gameC_->Initialize();
		}
		break;

	case GOverMode:
		gameO_->Update();

		//シーン変換
		//オーバーシーンのクラスから変更出来るか否かフラグ貰ってきてtrueだった場合
		//別のシーンに移行する
		if (gameO_->GetFlagChange()) {
			sceneNum_ = TitleMode;
			gameO_->SetFlagChange(false);

			//deleteとnewと初期化(初期化だけでもよさそう感)
			//動きによっては別な場所へ
			delete gameO_;
			gameO_ = new GameOScene();
			gameO_->Initialize();
		}
		break;

	default:
		break;
	}

#pragma region ImGui関連

#ifdef _DEBUG
	ImGui::Begin("SceneModeCheck");
	ImGui::Text("[DIK_0] sceneNum_ %d", sceneNum_);
	ImGui::Text("[DIK_1] if(EggCount=0)_1to3(GameOver)");
	ImGui::Text("[EggCount=20] 1to2(GameClear)");
	ImGui::End();
#endif // DEBUG

#pragma endregion


}

void SceneManager::Draw() {

	// シーン毎の描写
	switch (sceneNum_) {

	case TitleMode:
		title_->Draw();

		break;

	case GPlayMode:
		gameP_->Draw();

		break;

	case GClearMode:
		gameC_->Draw();

		break;

	case GOverMode:
		gameO_->Draw();

		break;

	default:
		break;
	}
}

