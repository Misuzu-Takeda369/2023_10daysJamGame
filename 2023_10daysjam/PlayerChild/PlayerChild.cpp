#include "PlayerChild.h"
#include "Function/Function.h"
#include <cmath>

PlayerChild::~PlayerChild()
{
	delete weapon_;
}

PlayerChild::PlayerChild()
{
}

void PlayerChild::Initialize(const Vector2& forwardPos,const Vector2& playerPos, Vector2 ScrollPos)
{
	float directionRadian;
	float directionDegree;
	//一番最後にいるのやつのおしりに出てくるようにしたい
	if (forwardPos.x - playerPos.x == 0 && forwardPos.y - playerPos.y == 0) {
		//とりあえずプレイヤーの上方向に出す
		//方向用の変数あればこの辺書き換える
		pos_.x = playerPos.x+ScrollPos.x;
		pos_.y = (playerPos.y - distanceRadius)+ScrollPos.y;
		directionDegree = float(playerDirection_);
		directionRadian = DegreeToRadian(directionDegree);
	}
	else {
		 directionRadian = std::atan2(forwardPos.y - playerPos.y, forwardPos.x - playerPos.x);
		 directionDegree = RadianToDegree(directionRadian);
		childDirection_ = int(directionDegree);
		directionDegree = 180 + directionDegree;
		directionRadian = DegreeToRadian(directionDegree);
		pos_.x = (forwardPos.x + std::cos(directionRadian) * distanceRadius);
		pos_.y = (forwardPos.y + std::sin(directionRadian) * distanceRadius);
		screenPos_.x = pos_.x + ScrollPos.x;
		screenPos_.y = pos_.y + ScrollPos.y;
	}
	//成長速度が-1～+2秒変わる 
	growTime_ = growTimeBase_ + RandomRange(-60, 120);

	babyTexture_ = Novice::LoadTexture("./Resources/Images/bird_child_B.png");
	adultTexture_ = Novice::LoadTexture("./Resources/Images/bird_child_A.png");
	adultTextureHorn_ = Novice::LoadTexture("./Resources/Images/bird_child_Type.png");
	animationNum_ = 0;
	//animationFrame_ = 30;
	weapon_ = new PlayerChildWeapon();
	
	SetChildType();
}

void PlayerChild::Update(const Vector2& forwardPos, const Vector2& playerPos, Vector2 ScrollPos)
{
	//初期化の座標決定と似た感じの処理
	float directionRadian = std::atan2(forwardPos.y - playerPos.y, forwardPos.x - playerPos.x);
	float direction;
	if (forwardPos.x - playerPos.x == 0 && forwardPos.y - playerPos.y == 0) {
		direction = float(playerDirection_);
	}
	else {
		float childDirect = std::atan2(pos_.y - forwardPos.y, pos_.x - forwardPos.x);
		childDirection_ = int(RadianToDegree(childDirect));
		direction = RadianToDegree(directionRadian);
		direction = direction;
	}
	directionRadian = DegreeToRadian(direction);
	pos_.x = (forwardPos.x + std::cos(directionRadian) * distanceRadius);
	pos_.y = (forwardPos.y + std::sin(directionRadian) * distanceRadius);
	screenPos_.x = pos_.x + ScrollPos.x;
	screenPos_.y = pos_.y + ScrollPos.y;

	//成長
	if (isGrow_ != true) {
		growCountTimer_++;
	}
	if (growCountTimer_ >= growTime_) {
		isGrow_ = true;
	}
	//攻撃
	if (isGrow_) {
		Attack();
	}
	SetBulletLive(weapon_->GetBulletLive());
	SetScreenBulletPos(weapon_->GetScreenBulletPos());


}

void PlayerChild::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), 100, 100, 0, WHITE, kFillModeWireFrame);
	if (isGrow_) {
		//成長済み
		//Novice::DrawSprite(int(pos_.x) - radius_, int(pos_.y) - radius_, adultTextureLeg_, 1, 1, 0, color_.color);
		Novice::DrawSpriteRect(int(pos_.x) - radius_, int(pos_.y) - radius_, textureSize_ * animationNum_, 0, textureSize_, textureSize_, adultTexture_, 0.25, 1, 0.0f, color_.color);
		Novice::DrawSpriteRect(int(pos_.x) - radius_, int(pos_.y) - radius_, textureSize_ * 1, 0, textureSize_, textureSize_, adultTextureHorn_, 0.25, 1, 0.0f, color_.color);
		weapon_->Draw();
	}
	else {
		//未成長
		//Novice::DrawSprite(int(pos_.x) - radius_, int(pos_.y) - radius_, babyTexture_, 1, 1, 0, color_.color);
		Novice::DrawSpriteRect(int(pos_.x) - radius_, int(pos_.y) - radius_, textureSize_ * animationNum_, 0, textureSize_, textureSize_, babyTexture_, 0.25, 1, 0.0f, color_.color);

	}
}

void PlayerChild::Attack()
{
	if (attackCoolTimer_ >= attackCoolTime_) {
		attackTimer_++;
	}
	else {
		attackCoolTimer_++;
	}
	if (attackTimer_ >= attackTime_) {
		weapon_->SetIsAttacking(true);
		attackTimer_ = 0;
		attackCoolTimer_ = 0;
	}
	weapon_->Update(pos_);
}

void PlayerChild::SetDirection(char* preKeys)
{

	//角度設定
	if ((preKeys[DIK_LEFT] && preKeys[DIK_UP]) || (preKeys[DIK_A] && preKeys[DIK_W])) {
		playerDirection_ = 45;
		animationNum_ = 1;
	}
	else if ((preKeys[DIK_RIGHT] && preKeys[DIK_UP]) || (preKeys[DIK_D] && preKeys[DIK_W])) {
		playerDirection_ = 135;
		animationNum_ = 1;
	}
	else if ((preKeys[DIK_LEFT] && preKeys[DIK_DOWN]) || (preKeys[DIK_A] && preKeys[DIK_S])) {
		playerDirection_ = 315;
		animationNum_ = 0;
	}
	else if ((preKeys[DIK_RIGHT] && preKeys[DIK_DOWN]) || (preKeys[DIK_D] && preKeys[DIK_S])) {
		playerDirection_ = 225;
		animationNum_ = 0;
	}

	else if (preKeys[DIK_LEFT] || preKeys[DIK_A]) {
		playerDirection_ = 0;
		animationNum_ = 3;
	}
	else if (preKeys[DIK_RIGHT] || preKeys[DIK_D]) {
		playerDirection_ = 180;
		animationNum_ = 2;
	}
	else if (preKeys[DIK_UP] || preKeys[DIK_W]) {
		playerDirection_ = 90;
		animationNum_ = 1;
	}
	else if (preKeys[DIK_DOWN] || preKeys[DIK_S]) {
		playerDirection_ = 270;
		animationNum_ = 0;
	}
}

void PlayerChild::SetChildNumber(int num)
{
	childNumber_ = num;
}

void PlayerChild::SetIsArrive(bool flag)
{
	isArrive_ = flag;
}

void PlayerChild::SetChildType()
{
	int typeNum = RandomRange(1, typeTotal_);
	adultTexture_ = Novice::LoadTexture("./Resources/Images/bird_child_A.png");
	childType_ = Type(typeNum);
	weapon_->Initialize(childType_);
	color_.color = WHITE;
}
