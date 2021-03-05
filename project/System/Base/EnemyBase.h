//---------------------------------------------------------------------------
//!	@file	EnemyBase.h
//!	@brief	�G�l�~�[�̃x�[�X
//---------------------------------------------------------------------------
#pragma once
class EnemyBase : public Base
{
public:
	EnemyBase();
	~EnemyBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void RandPos(); //!< �G�̈ʒu�������_��
	virtual void Draw() = 0;

public:
    //-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

    //@{
	VECTOR getPos()       const { return pos; }
	bool getIsAttackHit() const { return isAttackHit; }
	//@}


	//-------------------------------------------------------------
    //!	@name	�Z�b�^�[
    //-------------------------------------------------------------

    //@{ 
	void setIsAttackHit(bool isAttackHit_){ isAttackHit = isAttackHit_ ; }
	void setIsHit(bool isHit_) { isHit = isHit_; }
	//@}

protected:

	bool isAttackHit;//!< �G�ƃv���C���[�̍U���̓����蔻��t���O
	bool isHit;      //!< �G�ƃv���C���[�̓����蔻��t���O

	//! MATRIX�̏�����
	MATRIX EnemyMat = MGetIdent();
};

