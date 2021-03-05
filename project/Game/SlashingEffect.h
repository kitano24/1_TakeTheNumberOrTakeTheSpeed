//---------------------------------------------------------------------------
//!	@file	SlashingEffect.h
//!	@brief	�a���G�t�F�N�g
//---------------------------------------------------------------------------
#pragma once
class SlashingEffect
{
public:
	SlashingEffect();
	~SlashingEffect() = default;

	void Update();
	void Draw();

	//-------------------------------------------------------------
	//!	@name	�Z�b�^�[
	//-------------------------------------------------------------

	//@{ 
	void setEffectPos(const VECTOR& pos);
	//@}

private:
	int effectResourceHandle;
	int playingEffectHandle;
	float effectSize;
};

