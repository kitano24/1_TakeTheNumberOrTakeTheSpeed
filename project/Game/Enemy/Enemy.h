//---------------------------------------------------------------------------
//!	@file	Enemy.h
//!	@brief	コウモリの敵
//---------------------------------------------------------------------------
#pragma once
class Enemy :public EnemyBase
{
public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Draw();

private:
	int modelBat;     //!< 敵のモデル（コウモリ）

#define ENEMY_SIZE 3 //!< エネミーのサイズ 
#define ENEMY_Y 105  //!< エネミーのY座標
};

