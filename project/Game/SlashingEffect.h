//---------------------------------------------------------------------------
//!	@file	SlashingEffect.h
//!	@brief	斬撃エフェクト
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
	//!	@name	セッター
	//-------------------------------------------------------------

	//@{ 
	void setEffectPos(const VECTOR& pos);
	//@}

private:
	int effectResourceHandle;
	int playingEffectHandle;
	float effectSize;
};

