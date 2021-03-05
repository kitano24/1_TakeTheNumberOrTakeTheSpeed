//---------------------------------------------------------------------------
//!	@file	CharaBase.h
//!	@brief	�L�����N�^�[�̃x�[�X
//---------------------------------------------------------------------------
#pragma once
class PlayerBase : public Base
{
public:

    PlayerBase();
    ~PlayerBase() = default;

    virtual void Initialize() = 0; //!< ������
    virtual void Move() = 0;       //!< �ړ�����
    virtual void Animation() = 0;  //!< �A�j���[�V����
    virtual void Update() = 0;     //!< �X�V����
    virtual void Draw() = 0;       //!< �`��
};