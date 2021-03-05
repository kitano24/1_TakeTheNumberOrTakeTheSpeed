//---------------------------------------------------------------------------
//!	@file	EnemyManager.h
//!	@brief	�G�l�~�[�S�̂̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

class EnemyManager
{

public:
	EnemyManager();
	~EnemyManager();

	void Initialize();
	void Update();
	void Draw();

public:
	//-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

    //@{
	int getEnemyMax() const { return enemyMax; }
	EnemyBase* getEnemy(int num) const { return enemys[num]; }
	void addEnemyCount() { enemyCount++; } //!< �|���ꂽ�G�̃J�E���g
	//@}

private:
#define ENEMY_MAX 100

	std::vector<EnemyBase*> enemys; //!< �G�̉ϒ��z��
	const int enemyMax = ENEMY_MAX; //!< �G�̍ő吔

	int fontSize;      //!< �����̃T�C�Y
	int countFontSize; //!< �G���|���ꂽ���̃t�H���g�T�C�Y
	int enemyCount;    //!< �|���ꂽ�G�̃J�E���g
};

