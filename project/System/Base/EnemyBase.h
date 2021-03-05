//---------------------------------------------------------------------------
//!	@file	EnemyBase.h
//!	@brief	エネミーのベース
//---------------------------------------------------------------------------
#pragma once
class EnemyBase : public Base
{
public:
	EnemyBase();
	~EnemyBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void RandPos(); //!< 敵の位置をランダム
	virtual void Draw() = 0;

public:
    //-------------------------------------------------------------
    //!	@name	ゲッター
    //-------------------------------------------------------------

    //@{
	VECTOR getPos()       const { return pos; }
	bool getIsAttackHit() const { return isAttackHit; }
	//@}


	//-------------------------------------------------------------
    //!	@name	セッター
    //-------------------------------------------------------------

    //@{ 
	void setIsAttackHit(bool isAttackHit_){ isAttackHit = isAttackHit_ ; }
	void setIsHit(bool isHit_) { isHit = isHit_; }
	//@}

protected:

	bool isAttackHit;//!< 敵とプレイヤーの攻撃の当たり判定フラグ
	bool isHit;      //!< 敵とプレイヤーの当たり判定フラグ

	//! MATRIXの初期化
	MATRIX EnemyMat = MGetIdent();
};

