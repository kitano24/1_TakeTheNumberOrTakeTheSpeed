//---------------------------------------------------------------------------
//!	@file	SceneRanking.h
//!	@brief	�����L���O�V�[��
//---------------------------------------------------------------------------
#pragma once
class SceneRanking : public Base
{
public:
	SceneRanking();
	~SceneRanking() = default;

	void Initialize();
	void NumericsInitialize(); //!< ���l�̏�����
	void Update();
	void DrawUpdate();
	void Draw();
	void SceneClearRank(class SceneClear* sceneClear);
	void DrawRanKing();   
	void Save();

public:
	//-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

    //@{
	bool getIsTitle() const { return isTitle; }
	//@}


    //-------------------------------------------------------------
	//!	@name	�Z�b�^�[
	//-------------------------------------------------------------

	//@{ 
	void  setScore(int scroe);
	//@}

private:
	int rankingScreen; //!< �����L���O�̔w�i
	//! txt�ɏ������ރX�R�A������p�̔z��(���3�ʂ܂�)
	std::array<int, 3> ranking;
	
	//! ���݃X�R�A
	int score;
	int score_;

	int rankingFontSize;   //!< ��RANKING���̕����T�C�Y
	int clearRankFontSize; //!< SceneClear�ŕ\�����镶���̃T�C�Y
	int blinkTimer;        //!< �����L���O�`���ʂł̓_�ŗp�ϐ��@
	int count;             //!< Back in B�̓_�Ŏ���
	int sceneClearOpacity; //!< �N���A�V�[���ŕ`�悷�郉���L���O�̕s�����x
	int now;               //!< �N���A���̃X�R�A
	int rankingOpacity;    //!< �����L���O�̕s�����x
	int firstOpacity;      //!< 1�ʂ̕s�����x
	int secondOpacity;     //!< 2�ʂ̕s�����x
	int thirdOpacity;      //!< 3�ʂ̕s�����x
	bool isTitle;          //!< �^�C�g���ɖ߂�t���O
	bool once;             //!< �N���A���̃X�R�A��1�񂾂��ʂ�

#define MAX_OPACITY 255    //!< �ő�s�����x
};

