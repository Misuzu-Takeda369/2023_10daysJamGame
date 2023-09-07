#pragma once
#include <cstdint>

/// <summary>
/// 色用の構造体
/// </summary>
struct UnitColor	
{	int R; int G; int B; int A;
	unsigned int color;
	
};

//以下ユニットの向きを変える場合に画像を複数使う時用
/*

/// <summary>
/// 4方向 上向きから右回り順
/// </summary>
struct UnitTexture4
{
	uint32_t up;
	uint32_t right;
	uint32_t down;
	uint32_t left;
};
/// <summary>
/// 8方向 上向きから右回り順
/// </summary>
struct UnitTexture8
{
	uint32_t up; uint32_t upRight;
	uint32_t right; uint32_t downRight;
	uint32_t down; uint32_t downLeft;
	uint32_t left; uint32_t upLeft;
};

*/
