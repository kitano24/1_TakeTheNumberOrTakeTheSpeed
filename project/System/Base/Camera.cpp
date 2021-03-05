//---------------------------------------------------------------------------
//!	@file	Camera.cpp
//!	@brief	カメラ
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
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
//! 更新処理
//---------------------------------------------------------------------------
void Camera::Update()
{
    //-------------------------------------------------------------
    //! ワールド行列を作成
    //-------------------------------------------------------------

    //! Z軸
    //! dxlibは左手の法則なのでDirectXの逆の(lookAt - position)
    VECTOR axisZ = VNorm(VSub(lookAt, pos));

    //! X軸
    VECTOR	axisX = VNorm(VCross(VGet(0.0f, 1.0f, 0.0f), axisZ));

    //! Y軸
    VECTOR	axisY = VCross(axisZ, axisX);

    //! 行列に設定
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
    //! ビュー行列を作成
    //-------------------------------------------------------------
    //! ※ ビュー行列 = カメラのワールド行列の逆行列
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
    //! 投影行列の作成
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
//! 画角設定
//---------------------------------------------------------------------------
void Camera::setPerspective(const float fovY_)
{
    fovY = fovY_;
}

//---------------------------------------------------------------------------
//! カメラのターゲットの設定
//---------------------------------------------------------------------------
void Camera::setPositionAndTarget(const VECTOR& pos_, const VECTOR& target) 
{
    pos = pos_;
    lookAt = target;
}

