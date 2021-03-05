//---------------------------------------------------------------------------
//!	@file	SceneRanking.h
//!	@brief	ランキングシーン
//---------------------------------------------------------------------------
#pragma once
class SceneRanking : public Base
{
public:
	SceneRanking();
	~SceneRanking() = default;

	void Initialize();
	void NumericsInitialize(); //!< 数値の初期化
	void Update();
	void DrawUpdate();
	void Draw();
	void SceneClearRank(class SceneClear* sceneClear);
	void DrawRanKing();   
	void Save();

public:
	//-------------------------------------------------------------
    //!	@name	ゲッター
    //-------------------------------------------------------------

    //@{
	bool getIsTitle() const { return isTitle; }
	//@}


    //-------------------------------------------------------------
	//!	@name	セッター
	//-------------------------------------------------------------

	//@{ 
	void  setScore(int scroe);
	//@}

private:
	int rankingScreen; //!< ランキングの背景
	//! txtに書き込むスコアを入れる用の配列(上位3位まで)
	std::array<int, 3> ranking;
	
	//! 現在スコア
	int score;
	int score_;

	int rankingFontSize;   //!< 〓RANKING〓の文字サイズ
	int clearRankFontSize; //!< SceneClearで表示する文字のサイズ
	int blinkTimer;        //!< ランキング描画画面での点滅用変数　
	int count;             //!< Back in Bの点滅時間
	int sceneClearOpacity; //!< クリアシーンで描画するランキングの不透明度
	int now;               //!< クリア時のスコア
	int rankingOpacity;    //!< ランキングの不透明度
	int firstOpacity;      //!< 1位の不透明度
	int secondOpacity;     //!< 2位の不透明度
	int thirdOpacity;      //!< 3位の不透明度
	bool isTitle;          //!< タイトルに戻るフラグ
	bool once;             //!< クリア時のスコアを1回だけ通す

#define MAX_OPACITY 255    //!< 最大不透明度
};

