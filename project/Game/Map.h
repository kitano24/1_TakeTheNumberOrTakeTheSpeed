//---------------------------------------------------------------------------
//!	@file	Map.cpp
//!	@brief	
//---------------------------------------------------------------------------
#pragma once
class Map : public Base
{
public:
    Map();
    ~Map();

    void Initialize();
    void Update();
    void ImGui();
    void Draw();

private:
    int  skyDome;      //!< スカイドームの描画
    bool isEnableLine; //!< ラインのON、OFF

//! ラインを描く範囲
#define LINE_AREA_SIZE 10000.0f

//! ラインの数
#define LINE_NUM 150
};

