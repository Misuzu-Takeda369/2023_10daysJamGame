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

	babyTexture_ = Novice::LoadTexture("./Resources/Images/childBaby.png");

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
		Novice::DrawSprite(int(pos_.x) - radius_, int(pos_.y) - radius_, adultTexture_, 1, 1, 0, color_.color);
	}
	else {
		//未成長
		Novice::DrawSprite(int(pos_.x) - radius_, int(pos_.y) - radius_, babyTexture_, 1, 1, 0, color_.color);
	}
	weapon_->Draw();
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
	if (preKeys[DIK_LEFT] && preKeys[DIK_UP]) {
		playerDirection_ = 45;
	}
	else if (preKeys[DIK_RIGHT] && preKeys[DIK_UP]) {
		playerDirection_ = 135;
	}
	else if (preKeys[DIK_LEFT] && preKeys[DIK_DOWN]) {
		playerDirection_ = 315;
	}
	else if (preKeys[DIK_RIGHT] && preKeys[DIK_DOWN]) {
		playerDirection_ = 225;
	}

	else if (preKeys[DIK_LEFT]) {
		playerDirection_ = 0;
	}
	else if (preKeys[DIK_RIGHT]) {
		playerDirection_ = 180;
	}
	else if (preKeys[DIK_UP]) {
		playerDirection_ = 90;
	}
	else if (preKeys[DIK_DOWN]) {
		playerDirection_ = 270;
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
	adultTexture_ = Novice::LoadTexture("./Resources/Images/childAdult.png");
	childType_ = Type(typeNum);
	weapon_->Initialize(childType_);
	color_.color = RED;
}
