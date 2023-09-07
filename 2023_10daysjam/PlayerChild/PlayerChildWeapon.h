#pragma once
/// <summary>
/// 子の攻撃用のクラス
/// </summary>
class PlayerChildWeapon
{
public:
	PlayerChildWeapon();
	~PlayerChildWeapon();
	void Initialize(int type);
	void Update();
private:
	int typeNum_ = 0;
};

