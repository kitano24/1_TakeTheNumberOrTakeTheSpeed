//---------------------------------------------------------------------------
//!	@file	Player.h
//!	@brief	プレイヤーの処理
//---------------------------------------------------------------------------
#pragma once
class Player : public PlayerBase
{
public:
	Player();
	~Player();

	virtual void Initialize() override;//!< 初期化
	virtual void Draw() override;      //!< 描画
	virtual void Move() override;      //!< 移動処理
	virtual void Animation() override; //!< アニメーション
	virtual void Update() override;    //!< 更新処理
	void Texture();      //!< テクスチャー
	void WorldMat();     //!< ワールド行列
	void Rot();          //!< 回転
	void ImGui();        //!< imguiの処理

public:
	//-------------------------------------------------------------
	//!	@name	ゲッター
	//-------------------------------------------------------------

	//@{
	//! 座標
	VECTOR getPos() const { return pos; }
	float getPosX() const { return pos.x; }
	float getPosY() const { return pos.y; }
	float getPosZ() const { return pos.z; }

	//! 移動量
	float getMovToX() const { return moveTo.x; }
	float getMovToY() const { return moveTo.y; }
	float getMovToZ() const { return moveTo.z; }

	//! 動いているか
	bool getIsAction() const { return isAction; }

	//! 当たり判定のサイズ
	float getHitSize() const { return hitSize; }
	//@}


	//-------------------------------------------------------------
	//!	@name	セッター
	//-------------------------------------------------------------

	//@{ 
	void setCameraPos(const VECTOR& pos);
	void setCameraRot(const VECTOR& rot);
	//@}

private:

	//! キャラクターのアニメーション
	enum class CharaAnim {
		Run,
		Waiting,
		Attack,
	};
	CharaAnim charaAnim;

	//! アニメーションの番号
	enum  AnimNum {
		RUN = 0,
		WAITING = 1,
		ATTACK = 2,
	};

	MATRIX playerMat = MGetIdent();	//!< playermatの初期化
	MATRIX matWorld;                //!< プレイヤーのワールド行列

	VECTOR moveTo;        //!< プレイヤーの移動量
	VECTOR direction;     //!< プレイヤーの向いている方向
	VECTOR cameraPos;     //!< カメラの位置
	VECTOR cameraRot;     //!< カメラの回転

	int   modelHotaru;   //!< 主人公のモデル
	int   attachAnim;    //!< アニメーションのアタッチ
	float totalTime;     //!< アニメーションの総時間
	float playTime;      //!< アニメーションのスピード
	float attackTime;    //!< 攻撃アニメーションのスピード
	float moveSpeed;     //!< 移動スピード
	float playerSize;    //!< プレイヤーのサイズ
	float angleX;        //!< プレイヤーの傾きX
	float angleZ;        //!< プレイヤーの傾きZ
	bool  isAction;      //!< プレイヤーが動いていたら
	bool  isAttack;      //!< 攻撃ボタンが押されたら

	int textureNum; //!< プレイヤーのテクスチャ数
	std::vector<std::string> textureName;
};