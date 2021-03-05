//---------------------------------------------------------------------------
//!	@file	Camera.h
//!	@brief	�J����
//---------------------------------------------------------------------------
#pragma once
class Camera : public Base
{
public:
	Camera();
	~Camera() = default;

	virtual void Update();
	virtual void Draw() = 0;

	void setPerspective(const float fovY_);
	void setPositionAndTarget(const VECTOR& pos_, const VECTOR& target);

private:

	MATRIX matWorld;     //!< �J�����̃��[���h�s��
	MATRIX matView;      //!< �r���[�s��
	MATRIX matProj;      //!< ���e�s��
	VECTOR lookAt;       //!< �����_
	VECTOR rot;          //!< ��]

	float fovY;			  //!< ��p
	float aspectRatio;    //!< �A�X�y�N�g��
	float zNear;          //!< �߃N���b�v��
	float zFar;           //!< ���N���b�v��
};

