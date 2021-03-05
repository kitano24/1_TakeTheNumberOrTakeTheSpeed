//---------------------------------------------------------------------------
//!	@file	CharaBase.h
//!	@brief	キャラクターのベース
//---------------------------------------------------------------------------
#pragma once
class PlayerBase : public Base
{
public:

    PlayerBase();
    ~PlayerBase() = default;

    virtual void Initialize() = 0; //!< 初期化
    virtual void Move() = 0;       //!< 移動処理
    virtual void Animation() = 0;  //!< アニメーション
    virtual void Update() = 0;     //!< 更新処理
    virtual void Draw() = 0;       //!< 描画
};
