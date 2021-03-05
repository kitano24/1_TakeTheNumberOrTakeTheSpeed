//---------------------------------------------------------------------------
//!	@file	Camera.h
//!	@brief	カメラ
//---------------------------------------------------------------------------
#pragma once
class Camera : public Base
{
public:
	Camera();
	~Camera() = default;

	virtual void Update();
	virtual void Draw() = 0;

	void setPerspective(const float fovY_);
	void setPositionAndTarget(const VECTOR& pos_, const VECTOR& target);

private:

	MATRIX matWorld;     //!< カメラのワールド行列
	MATRIX matView;      //!< ビュー行列
	MATRIX matProj;      //!< 投影行列
	VECTOR lookAt;       //!< 注視点
	VECTOR rot;          //!< 回転

	float fovY;			  //!< 画角
	float aspectRatio;    //!< アスペクト比
	float zNear;          //!< 近クリップ面
	float zFar;           //!< 遠クリップ面
};

