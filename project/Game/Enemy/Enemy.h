//---------------------------------------------------------------------------
//!	@file	Enemy.h
//!	@brief	�R�E�����̓G
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
	int modelBat;     //!< �G�̃��f���i�R�E�����j

#define ENEMY_SIZE 3 //!< �G�l�~�[�̃T�C�Y 
#define ENEMY_Y 105  //!< �G�l�~�[��Y���W
};

