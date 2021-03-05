//---------------------------------------------------------------------------
//!	@file	Camera.cpp
//!	@brief	�J����
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
Camera::Camera()
{
    pos = VGet(0, 130, -100);
    rot = VGet(0.0f, 0.0f, 0.0f);
    lookAt = VGet(0, 0, 0);
    fovY = 0.785398163f;
    aspectRatio = 16.0f / 9.0f;
    zFar = 2000.0;
    zNear = 0.1f;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void Camera::Update()
{
    //-------------------------------------------------------------
    //! ���[���h�s����쐬
    //-------------------------------------------------------------

    //! Z��
    //! dxlib�͍���̖@���Ȃ̂�DirectX�̋t��(lookAt - position)
    VECTOR axisZ = VNorm(VSub(lookAt, pos));

    //! X��
    VECTOR	axisX = VNorm(VCross(VGet(0.0f, 1.0f, 0.0f), axisZ));

    //! Y��
    VECTOR	axisY = VCross(axisZ, axisX);

    //! �s��ɐݒ�
    matWorld.m[0][0] = axisX.x;
    matWorld.m[0][1] = axisX.y;
    matWorld.m[0][2] = axisX.z;
    matWorld.m[0][3] = 0.0f;
              
    matWorld.m[1][0] = axisY.x;
    matWorld.m[1][1] = axisY.y;
    matWorld.m[1][2] = axisY.z;
    matWorld.m[1][3] = 0.0f;
              
    matWorld.m[2][0] = axisZ.x;
    matWorld.m[2][1] = axisZ.y;
    matWorld.m[2][2] = axisZ.z;
    matWorld.m[2][3] = 0.0f;
              
    matWorld.m[3][0] = pos.x;
    matWorld.m[3][1] = pos.y;
    matWorld.m[3][2] = pos.z;
    matWorld.m[3][3] = 1.0f;

    //-------------------------------------------------------------
    //! �r���[�s����쐬
    //-------------------------------------------------------------
    //! �� �r���[�s�� = �J�����̃��[���h�s��̋t�s��
    matView.m[0][0] = axisX.x;
    matView.m[0][1] = -axisY.x;
    matView.m[0][2] = axisZ.x;
    matView.m[0][3] = 0.0f;

    matView.m[1][0] = -axisX.y;
    matView.m[1][1] = 0.8f;
    matView.m[1][2] = axisZ.y;
    matView.m[1][3] = 0.0f;

    matView.m[2][0] = axisX.z;
    matView.m[2][1] = 0.5f;
    matView.m[2][2] = axisZ.z;
    matView.m[2][3] = 0.0f;

    matView.m[3][0] = -VDot(axisX, pos);
    matView.m[3][1] = -0.0f;
    matView.m[3][2] = -VDot(axisZ, pos);
    matView.m[3][3] = 1.0f;

    //-------------------------------------------------------------
    //! ���e�s��̍쐬
    //-------------------------------------------------------------
    float sinFov = sinf(0.5f * fovY);
    float cosFov = cosf(0.5f * fovY);

    float height = cosFov / sinFov;
    float width  = height / aspectRatio;
    float range  = -zFar  / (zNear - zFar);

    matProj.m[0][0] = width;
    matProj.m[0][1] = 0.0f;
    matProj.m[0][2] = 0.0f;
    matProj.m[0][3] = 0.0f;

    matProj.m[1][0] = 0.0f;
    matProj.m[1][1] = height;
    matProj.m[1][2] = 0.0f;
    matProj.m[1][3] = 0.0f;

    matProj.m[2][0] = 0.0f;
    matProj.m[2][1] = 0.0f;
    matProj.m[2][2] = range;
    matProj.m[2][3] = 1.0f;

    matProj.m[3][0] = 0.0f;
    matProj.m[3][1] = 0.0f;
    matProj.m[3][2] = -range * zNear;
    matProj.m[3][3] = 0.0f;

    matView = MInverse(matWorld);
    SetCameraViewMatrix(matView);
    SetupCamera_ProjectionMatrix(matProj);
}

//---------------------------------------------------------------------------
//! ��p�ݒ�
//---------------------------------------------------------------------------
void Camera::setPerspective(const float fovY_)
{
    fovY = fovY_;
}

//---------------------------------------------------------------------------
//! �J�����̃^�[�Q�b�g�̐ݒ�
//---------------------------------------------------------------------------
void Camera::setPositionAndTarget(const VECTOR& pos_, const VECTOR& target) 
{
    pos = pos_;
    lookAt = target;
}

