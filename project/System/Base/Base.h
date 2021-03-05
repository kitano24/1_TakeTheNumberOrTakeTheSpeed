//---------------------------------------------------------------------------
//!	@file	Base.h
//!	@brief	�S�N���X�̃x�[�X
//---------------------------------------------------------------------------
#pragma once
class Base
{
public:
	Base();
	~Base() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	//! Imgui���J�����������ł���֐�
	void OpenAndCloseImGui();

protected:

	//! �ʒu
	VECTOR pos;	

	//! �����蔻��p�ϐ�
	VECTOR hitPos;
	float hitSize;

	bool isImGui;        //!< imgui�̋N���t���O
	bool isEnableDebug;  //!< imgui�̃`�F�b�N�{�b�N�X�t���O
	int fontSize;        //!< �����̃T�C�Y
};

