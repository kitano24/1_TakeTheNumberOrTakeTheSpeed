//---------------------------------------------------------------------------
//!	@file	precompile.h
//!	@brief	�v���C�R���p�C���w�b�_�[
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! ���C�u�����֐�
//===========================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<array>
#include <math.h>
#include <complex>

//===========================================================================
//! System
//===========================================================================
#include "DxLib.h"
#include "WinMain.h"
#include "GameMain.h"
#include "Input/KeyInput.h"
#include "Input/PadInput.h"
#include "Color.h"
#include "Effekseer.h"
#include "EffekseerForDXLib.h"

//===========================================================================
//! Base
//===========================================================================
#include "Base/Base.h"       //!< �S�N���X�̃x�[�X
#include "Base/EnemyBase.h"  //!< �G�̃x�[�X
#include "Base/PlayerBase.h" //!< �v���C���[�̃x�[�X
#include "Base/Camera.h"     //!< �J�����̃x�[�X

//===========================================================================
//! Manager
//===========================================================================
#include"Enemy/EnemyManager.h" //!< �G�̃}�l�[�W���[

//===========================================================================
//! Game
//===========================================================================
#include "Camera/CameraPlayer.h" //!< �v���C���[�̃J����
#include "Map.h"                 //!< �}�b�v
#include "Player/Player.h"       //!< �v���C���[
#include "Goal.h"                //!< �S�[��
#include "Enemy/Enemy.h"         //!< �G�l�~�[
#include "Score.h"               //!< �X�R�A
#include "Light.h"               //!< ���C�g
#include "SlashingEffect.h"      //!< �G�t�F�N�g

//===========================================================================
//! Scene
//===========================================================================
#include "Scene/SceneRanking.h" //!< �����L���O�V�[��
#include "Scene/SceneTitle.h"   //!< �^�C�g���V�[��
#include "Scene/SceneClear.h"   //!< �N���A�V�[��

//===========================================================================
//! imgui
//===========================================================================
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
