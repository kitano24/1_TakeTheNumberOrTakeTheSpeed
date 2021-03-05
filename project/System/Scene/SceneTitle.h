//---------------------------------------------------------------------------
//!	@file	SceneTitle.h
//!	@brief	タイトルシーン
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
	//!	@name	ゲッター
	//-------------------------------------------------------------

	//@{
	bool getIsMainGame() const { return isMainGame; }
	bool getIsRanking()  const { return isRanking; }
	//@}

private:
	//! 描画する四角形の左上の頂点座標
	int x1, y1;
	//! 描画する四角形の右下＋１の頂点座標
	int x2, y2;
	
	int titletScreen; //!< タイトルの背景
	int fontSize;     //!< フォントサイズ
	bool isMainGame;  //!< ゲームスタートフラグ
	bool isRanking;   //!< ランキングへ移動フラグ
};

