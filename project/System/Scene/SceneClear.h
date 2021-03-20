//---------------------------------------------------------------------------
//!	@file	SceneClear.h
//!	@brief	クリアシーン
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
    //!	@name	ゲッター
    //-------------------------------------------------------------

   //@{
	bool getIsisTitle() const { return isTitle; }
	bool getIsOpacity() const { return isOpacity; }
	//@}


	//-------------------------------------------------------------
	//!	@name	セッター
	//-------------------------------------------------------------

	//@{
	void setScore(int score_);
	//@}

private:
	int clearScreen;//!< クリアシーンの背景
	int score;      //!< スコアクラスからとってくる用
	int dispScore;  //!< 表示するスコア
	int count;      //!< Push Bの点滅時間
	bool isTitle;   //!< タイトルシーンに戻るフラグ
	bool isOpacity; //!< 透明度のフラグ
};

