//---------------------------------------------------------------------------
//!	@file	EnemyManager.h
//!	@brief	エネミー全体の管理
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
    //!	@name	ゲッター
    //-------------------------------------------------------------

    //@{
	int getEnemyMax() const { return enemyMax; }
	EnemyBase* getEnemy(int num) const { return enemys[num]; }
	void addEnemyCount() { enemyCount++; } //!< 倒された敵のカウント
	//@}

private:
#define ENEMY_MAX 100

	std::vector<EnemyBase*> enemys; //!< 敵の可変長配列
	const int enemyMax = ENEMY_MAX; //!< 敵の最大数

	int fontSize;      //!< 文字のサイズ
	int countFontSize; //!< 敵が倒された数のフォントサイズ
	int enemyCount;    //!< 倒された敵のカウント
};

