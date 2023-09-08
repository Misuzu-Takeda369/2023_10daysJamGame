#pragma once

/// <summary>
/// 敵の攻撃
/// </summary>
class EnemyBullet
{
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	EnemyBullet();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBullet();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たった時の処理
	/// </summary>
	void OnCollision();

private:


};

