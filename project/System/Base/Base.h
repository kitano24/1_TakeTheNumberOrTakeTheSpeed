//---------------------------------------------------------------------------
//!	@file	Base.h
//!	@brief	全クラスのベース
//---------------------------------------------------------------------------
#pragma once
class Base
{
public:
	Base();
	~Base() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	//! Imguiを開いたり閉じたりできる関数
	void OpenAndCloseImGui();

protected:

	//! 位置
	VECTOR pos;	

	//! 当たり判定用変数
	VECTOR hitPos;
	float hitSize;

	bool isImGui;        //!< imguiの起動フラグ
	bool isEnableDebug;  //!< imguiのチェックボックスフラグ
	int fontSize;        //!< 文字のサイズ
};

