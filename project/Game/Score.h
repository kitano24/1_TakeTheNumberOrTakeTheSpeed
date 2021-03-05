//---------------------------------------------------------------------------
//!	@file	Score.h
//!	@brief	�X�R�A�̏���
//---------------------------------------------------------------------------
#pragma once
class Score : public Base
{   
public:
    Score();
    ~Score() = default;

    void Initialize();
    void Update();
    void ImGui();
    void Draw();

public:
    //-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

    //@{
    int getScore() const { return score; }
    //@}
    
    //-------------------------------------------------------------
    //!	@name	�Z�b�^�[
    //-------------------------------------------------------------

    //@{
    void setEnemyScore(int enemyScore_) { score += enemyScore_; }
    //@}

private:
    int count; //!< �o�ߎ��Ԃ̌v��
    int score; //!< �X�R�A
};

