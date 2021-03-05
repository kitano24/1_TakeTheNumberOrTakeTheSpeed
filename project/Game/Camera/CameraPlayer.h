#pragma once
class CameraPlayer : public Camera
{
public:
    //! �R���X�g���N�^
    CameraPlayer();

    //! �f�X�g���N�^
    virtual ~CameraPlayer() = default;

    void Initialize();
    void Move(class Player* player);
    void ImGui();

    //! �X�V
    virtual void Update() override;

    //! �`��
    virtual void Draw() override;

    //-------------------------------------------------------------
    //!	@name	�Q�b�^�[
    //-------------------------------------------------------------

    //@{
    VECTOR getPos();
    VECTOR getRot() { return rot; }
    //@}

private:
   
    float rotSpeed;    //!< ��]�̃X�s�[�h
    float adjustmentY; //!< Y���W�̒���
    bool isImGui;      //!< imgui�̋N���t���O
    VECTOR rot;        //!< �J�����̉�]

#define DISTANCE_ADJUSTMENT 35 //<! �����̒���
};
