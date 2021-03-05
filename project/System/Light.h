//---------------------------------------------------------------------------
//!	@file	Light.h
//!	@brief	ライト
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
	float difR, difG;  //!< ディフューズカラー赤、緑
	float difB, difA;  //!< ディフューズカラー青、透明度
	bool isLightEnable;//!< ライトのON,OFFフラグ
	VECTOR direction;  //!< ライトの向き
};

