//---------------------------------------------------------------------------
//!	@file	SceneClear.h
//!	@brief	�N���A�V�[��
//---------------------------------------------------------------------------
#pragma once
class SceneClear : public Base 
{
public:
	SceneClear();
	~SceneClear() = default;

	void Initialize();
	void Update();
	void Draw();

public:
	//-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

   //@{
	bool getIsisTitle() const { return isTitle; }
	bool getIsOpacity() const { return isOpacity; }
	//@}


	//-------------------------------------------------------------
	//!	@name	�Z�b�^�[
	//-------------------------------------------------------------

	//@{
	void setScore(int score_);
	//@}

private:
	int clearScreen;//!< �N���A�V�[���̔w�i
	int score;      //!< �X�R�A�N���X����Ƃ��Ă���p
	int dispScore;  //!< �\������X�R�A
	int count;      //!< Push B�̓_�Ŏ���
	bool isTitle;   //!< �^�C�g���V�[���ɖ߂�t���O
	bool isOpacity; //!< �����x�̃t���O
};

