//---------------------------------------------------------------------------
//!	@file	SceneTitle.h
//!	@brief	�^�C�g���V�[��
//---------------------------------------------------------------------------
#pragma once
class SceneTitle : public Base
{
public:
	SceneTitle();
	~SceneTitle();

	void Initialize();
	void Update();
	void Move();
	void Draw();

public:   
	//-------------------------------------------------------------
	//!	@name	�Q�b�^�[
	//-------------------------------------------------------------

	//@{
	bool getIsMainGame() const { return isMainGame; }
	bool getIsRanking()  const { return isRanking; }
	//@}

private:
	//! �`�悷��l�p�`�̍���̒��_���W
	int x1, y1;
	//! �`�悷��l�p�`�̉E���{�P�̒��_���W
	int x2, y2;
	
	int titletScreen; //!< �^�C�g���̔w�i
	int fontSize;     //!< �t�H���g�T�C�Y
	bool isMainGame;  //!< �Q�[���X�^�[�g�t���O
	bool isRanking;   //!< �����L���O�ֈړ��t���O
};

