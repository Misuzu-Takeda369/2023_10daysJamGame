#pragma once
#include <cstdint>
#include "Vector2.h"
#include "UtilityStruct.h"
/// <summary>
/// 子の攻撃用のクラス
/// </summary>
class PlayerChildWeapon
{
public:
	PlayerChildWeapon();
	~PlayerChildWeapon();
	void Initialize(Type type);
	void Update(Vector2 child);
	void Draw();
	void SetIsAttacking(bool flag);
private:
	Type type_ = Type(0);
	void GetTexture();
	Vector2 pos_;
	uint32_t texture_ = 0;
	uint32_t effectTexture_ = 0;
	bool isAttacking_ = false;
	int attackTimer_ = 0;

	Vector2 BulletPos_ = {0.0f,0.0f};
};

