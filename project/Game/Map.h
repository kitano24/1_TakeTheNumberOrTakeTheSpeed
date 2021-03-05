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
    int  skyDome;      //!< �X�J�C�h�[���̕`��
    bool isEnableLine; //!< ���C����ON�AOFF

//! ���C����`���͈�
#define LINE_AREA_SIZE 10000.0f

//! ���C���̐�
#define LINE_NUM 150
};

