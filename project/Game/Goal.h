//---------------------------------------------------------------------------
//!	@file	Goal.h
//!	@brief	ゴールの処理
//---------------------------------------------------------------------------
#pragma once
class Goal : public Base
{
public:
    Goal();
    ~Goal();

    void Initialize();
    void Update();
    void ImGui();
    void Draw();

public:
    //-------------------------------------------------------------
    //!	@name	ゲッター
    //-------------------------------------------------------------

   //@{
    VECTOR getPos()       const { return pos; }
    float getHitSize()    const { return hitSize; }
    bool getIsHit()       const { return isHit; }
    bool getIsAppearing() const { return isAppearing; }
    //@}

    //-------------------------------------------------------------
    //!	@name	セッター
    //-------------------------------------------------------------

    //@{
    void setIsHit(bool isHit_) { isHit = isHit_; }
    //@}

private:
    //! matrixの初期化
    MATRIX GoalMat = MGetIdent();

#define GOAL_Y 100.0f //!< ゴールのY座標
#define GOAL_SIZE_X 1.5f
#define GOAL_SIZE_Y 0.5f
#define GOAL_SIZE_Z 1.5f 

    int modelGoal;      //!< ゴールのモデル
    int count;          //!< ゴールの出現するまでのカウント
    int time;           //!< ゲームオーバーまでのカウント 
    int messageFontSize;//!< 見逃し警告の文字サイズ
    int countFontSize;  //!< 見逃し回数のフォントサイズ
    int missedCount;    //!< ゴールを見逃した回数
    int flashingCount;  //!< ゴールが出現中の点滅カウント
    bool isAppearing;   //!< ゴールの出現フラグ
    bool isHit;         //!< 当たり判定のフラグ

    int textureNum; //!< ゴールのテクスチャ数
    std::vector<std::string> textureName;
};

