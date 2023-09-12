#include "BackGround.h"

#ifdef _DEBUG
#include "ImGuiManager.h"
#endif

BackGround::BackGround(Vector2 playerRadish)
{
	playerRadish_ = { playerRadish.x,playerRadish.y };
	image_ = Novice::LoadTexture("./Resources/Images/BackGround.png");
}

BackGround::~BackGround()
{
}

void BackGround::Initialize()
{
	wouldPosition_ = { 0.0f,0.0f };
	scrollPosition_ = { 0.0f,0.0f };
	speed_ = { 2.0f,2.0f };

	//複数の画像初期位置
	scrollBacksPos_[0] = { scrollPosition_.x - kWindowWidth,  scrollPosition_.y - kWindowHeight };
	scrollBacksPos_[1] = { scrollPosition_.x, scrollPosition_.y - kWindowHeight };
	scrollBacksPos_[2] = { scrollPosition_.x + kWindowWidth,scrollPosition_.y - kWindowHeight };
	scrollBacksPos_[3] = { scrollPosition_.x - kWindowWidth,scrollPosition_.y };
	scrollBacksPos_[4] = { scrollPosition_.x,scrollPosition_.y };
	scrollBacksPos_[5] = { scrollPosition_.x + kWindowWidth,scrollPosition_.y };
	scrollBacksPos_[6] = { scrollPosition_.x -kWindowWidth, scrollPosition_.y + kWindowHeight };
	scrollBacksPos_[7] = { scrollPosition_.x,scrollPosition_.y + kWindowHeight };
	scrollBacksPos_[8] = { scrollPosition_.x + kWindowWidth,scrollPosition_.y + kWindowHeight };

	//scrollBacksPos_;
	//}
	//スクロールした値初期位置
	for (uint32_t now = 0; now < 9; now++) {
		wouldBacksPos_[now] = { wouldPosition_.x,wouldPosition_.y };

		ScreensPos_[now] = { wouldBacksPos_[now].x - scrollBacksPos_[now].x, wouldBacksPos_[now].y - scrollBacksPos_[now].y };
	}

}

void BackGround::Update()
{

#pragma region Noviceのキー入力関連
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
#pragma endregion

	//背景の移動関数
	Move(keys);

	ChangeBackGround();
#pragma region ImGui関連
#ifdef _DEBUG
	ImGui::Begin("BackGroundMove");
	ImGui::Text("screenPos0_ %f,%f scrollPos0_ %f,%f", ScreensPos_[0].x, wouldBacksPos_[0].y, scrollBacksPos_[0].x, scrollBacksPos_[0].y);
	ImGui::Text("screenPos1_ %f,%f scrollPos1_ %f,%f", ScreensPos_[1].x, wouldBacksPos_[1].y, scrollBacksPos_[0].x, scrollBacksPos_[0].y);
	ImGui::Text("screenPos2_ %f,%f scrollPos2_ %f,%f", ScreensPos_[2].x, wouldBacksPos_[2].y, scrollBacksPos_[0].x, scrollBacksPos_[0].y);
	ImGui::End();

#endif

#pragma endregion
}

void BackGround::Draw()
{
	//Novice::DrawBox(uint32_t(wouldPosition_.x - scrollPosition_.x), uint32_t(wouldPosition_.y - scrollPosition_.y), 1280, 720, 0.0f, RED, kFillModeWireFrame);


	//画像設置(まだ仮)
	//Novice::DrawSprite(uint32_t(wouldPosition_.x - scrollPosition_.x), uint32_t(wouldPosition_.y - scrollPosition_.y), image_,1.0f,1.0f,0.0f,WHITE);

	for (uint32_t now = 0; now < 9; now++) {
		Novice::DrawSprite(uint32_t(ScreensPos_[now].x), uint32_t(ScreensPos_[now].y), image_, 1.0f, 1.0f, 0.0f, WHITE);
	}
}


void BackGround::Move(char* keys)
{
	//MoveStop(keys);
	//斜め移動

	if ((keys[DIK_LEFT] && keys[DIK_UP]) || (keys[DIK_A] && keys[DIK_W])) {
		scrollPosition_.x -= (speed_.x / 1.41f);
		scrollPosition_.y -= (speed_.y / 1.41f);

		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x -= (speed_.x / 1.41f);
			scrollBacksPos_[now].y -= (speed_.y / 1.41f);
		}

	}
	else if ((keys[DIK_RIGHT] && keys[DIK_UP]) || (keys[DIK_D] && keys[DIK_W])) {
		scrollPosition_.x += (speed_.x / 1.41f);
		scrollPosition_.y -= (speed_.y / 1.41f);


		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x += (speed_.x / 1.41f);
			scrollBacksPos_[now].y -= (speed_.y / 1.41f);
		}

	}
	else if ((keys[DIK_LEFT] && keys[DIK_DOWN] )|| (keys[DIK_A] && keys[DIK_S])) {
		scrollPosition_.x -= (speed_.x / 1.41f);
		scrollPosition_.y += (speed_.y / 1.41f);


		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x -= (speed_.x / 1.41f);
			scrollBacksPos_[now].y += (speed_.y / 1.41f);
		}

	}
	else if ((keys[DIK_RIGHT] && keys[DIK_DOWN]) || (keys[DIK_D] && keys[DIK_S])) {
		scrollPosition_.x += (speed_.x / 1.41f);
		scrollPosition_.y += (speed_.y / 1.41f);


		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x += (speed_.x / 1.41f);
			scrollBacksPos_[now].y += (speed_.y / 1.41f);
		}
	}


	//直線移動
	else if (keys[DIK_LEFT]|| keys[DIK_A]) {
		scrollPosition_.x -= speed_.x;

		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x -= speed_.x;
			//scrollBacksPos_[now].y += scrollPosition_.y;
		}
	}
	else if (keys[DIK_RIGHT] || keys[DIK_D]) {
		scrollPosition_.x += speed_.x;

		for (uint32_t now = 0; now < 9; now++) {
			scrollBacksPos_[now].x += speed_.x;
			//scrollBacksPos_[now].y += scrollPosition_.y;
		}

	}
	else if (keys[DIK_UP] || keys[DIK_W]) {
		scrollPosition_.y -= speed_.y;

		for (uint32_t now = 0; now < 9; now++) {
			//scrollBacksPos_[now].x -= speed_.x;
			scrollBacksPos_[now].y -= speed_.y;
		}

	}
	else if (keys[DIK_DOWN] || keys[DIK_S]) {
		scrollPosition_.y += speed_.y;

		for (uint32_t now = 0; now < 9; now++) {
			//scrollBacksPos_[now].x -= speed_.x;
			scrollBacksPos_[now].y += speed_.y;
		}

	}

	WorldtoScreen();


	

}

void BackGround::MoveStop(char* keys)
{

	//スクロールが止まる条件
	//真ん中から画面の半分分動いたら止まる(画面の半分のサイズ＋プレイヤーの半径の調整)
	//条件あったらスピードが0、それ以外ならそのまま
	if ((scrollPosition_.x <= -HalfBackGroundSize_.x + playerRadish_.x) && keys[DIK_LEFT]) {
		speed_.x = 0.0f;
		scrollPosition_.x = -HalfBackGroundSize_.x + playerRadish_.x;
	}
	else if ((scrollPosition_.x >= HalfBackGroundSize_.x - playerRadish_.x) && keys[DIK_RIGHT]) {
		speed_.x = 0.0f;
		scrollPosition_.x = HalfBackGroundSize_.x - playerRadish_.x;
	}
	else {
		speed_.x = 2.0f;
	}

	if ((scrollPosition_.y <= -HalfBackGroundSize_.y + playerRadish_.y) && keys[DIK_UP]) {
		speed_.y = 0.0f;
		scrollPosition_.y = -HalfBackGroundSize_.y + playerRadish_.y;
	}
	else if ((scrollPosition_.y >= HalfBackGroundSize_.y - playerRadish_.y) && keys[DIK_DOWN]) {
		speed_.y = 0.0f;
		scrollPosition_.y = HalfBackGroundSize_.y - playerRadish_.y;
	}
	else {
		speed_.y = 2.0f;
	}
}

void BackGround::ChangeBackGround()
{


	for (uint32_t now = 0; now < 9; now++) {

		//横方向のループ
		if (ScreensPos_[now].x > kWindowWidth * 2) {
			scrollBacksPos_[now].x = kWindowWidth;
		}
		else if (ScreensPos_[now].x < -(kWindowWidth)) {
			scrollBacksPos_[now].x = ( - (kWindowWidth * 2));

		}

		
		//縦方向のループ
		if (ScreensPos_[now].y > kWindowHeight * 2)  {
			scrollBacksPos_[now].y = kWindowHeight;
		}
		else if (ScreensPos_[now].y < -(kWindowHeight)) {
			scrollBacksPos_[now].y = -(kWindowHeight * 2);
		}
		
	}

}

void BackGround::WorldtoScreen() {

	for (uint32_t now = 0; now < 9; now++) {
		ScreensPos_[now].x = wouldBacksPos_[now].x - scrollBacksPos_[now].x;
		ScreensPos_[now].y = wouldBacksPos_[now].y - scrollBacksPos_[now].y;
	}
}
