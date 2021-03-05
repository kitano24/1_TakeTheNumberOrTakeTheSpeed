//---------------------------------------------------------------------------
//!	@file	Goal.h
//!	@brief	�S�[���̏���
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
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

   //@{
    VECTOR getPos()       const { return pos; }
    float getHitSize()    const { return hitSize; }
    bool getIsHit()       const { return isHit; }
    bool getIsAppearing() const { return isAppearing; }
    //@}

    //-------------------------------------------------------------
    //!	@name	�Z�b�^�[
    //-------------------------------------------------------------

    //@{
    void setIsHit(bool isHit_) { isHit = isHit_; }
    //@}

private:
    //! matrix�̏�����
    MATRIX GoalMat = MGetIdent();

#define GOAL_Y 100.0f //!< �S�[����Y���W
#define GOAL_SIZE_X 1.5f
#define GOAL_SIZE_Y 0.5f
#define GOAL_SIZE_Z 1.5f 

    int modelGoal;      //!< �S�[���̃��f��
    int count;          //!< �S�[���̏o������܂ł̃J�E���g
    int time;           //!< �Q�[���I�[�o�[�܂ł̃J�E���g 
    int messageFontSize;//!< �������x���̕����T�C�Y
    int countFontSize;  //!< �������񐔂̃t�H���g�T�C�Y
    int missedCount;    //!< �S�[��������������
    int flashingCount;  //!< �S�[�����o�����̓_�ŃJ�E���g
    bool isAppearing;   //!< �S�[���̏o���t���O
    bool isHit;         //!< �����蔻��̃t���O

    int textureNum; //!< �S�[���̃e�N�X�`����
    std::vector<std::string> textureName;
};

