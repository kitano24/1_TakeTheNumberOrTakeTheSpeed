//---------------------------------------------------------------------------
//!	@file	Light.h
//!	@brief	���C�g
//---------------------------------------------------------------------------

#pragma once
class Light : public Base
{
public:
	Light();
	~Light() = default;

	void Initialize();
	void Update();
	void ImGui();
	void Draw();

private:
	float difR, difG;  //!< �f�B�t���[�Y�J���[�ԁA��
	float difB, difA;  //!< �f�B�t���[�Y�J���[�A�����x
	bool isLightEnable;//!< ���C�g��ON,OFF�t���O
	VECTOR direction;  //!< ���C�g�̌���
};

