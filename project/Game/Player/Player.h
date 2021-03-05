//---------------------------------------------------------------------------
//!	@file	Player.h
//!	@brief	�v���C���[�̏���
//---------------------------------------------------------------------------
#pragma once
class Player : public PlayerBase
{
public:
	Player();
	~Player();

	virtual void Initialize() override;//!< ������
	virtual void Draw() override;      //!< �`��
	virtual void Move() override;      //!< �ړ�����
	virtual void Animation() override; //!< �A�j���[�V����
	virtual void Update() override;    //!< �X�V����
	void Texture();      //!< �e�N�X�`���[
	void WorldMat();     //!< ���[���h�s��
	void Rot();          //!< ��]
	void ImGui();        //!< imgui�̏���

public:
	//-------------------------------------------------------------
	//!	@name	�Q�b�^�[
	//-------------------------------------------------------------

	//@{
	//! ���W
	VECTOR getPos() const { return pos; }
	float getPosX() const { return pos.x; }
	float getPosY() const { return pos.y; }
	float getPosZ() const { return pos.z; }

	//! �ړ���
	float getMovToX() const { return moveTo.x; }
	float getMovToY() const { return moveTo.y; }
	float getMovToZ() const { return moveTo.z; }

	//! �����Ă��邩
	bool getIsAction() const { return isAction; }

	//! �����蔻��̃T�C�Y
	float getHitSize() const { return hitSize; }
	//@}


	//-------------------------------------------------------------
	//!	@name	�Z�b�^�[
	//-------------------------------------------------------------

	//@{ 
	void setCameraPos(const VECTOR& pos);
	void setCameraRot(const VECTOR& rot);
	//@}

private:

	//! �L�����N�^�[�̃A�j���[�V����
	enum class CharaAnim {
		Run,
		Waiting,
		Attack,
	};
	CharaAnim charaAnim;

	//! �A�j���[�V�����̔ԍ�
	enum  AnimNum {
		RUN = 0,
		WAITING = 1,
		ATTACK = 2,
	};

	MATRIX playerMat = MGetIdent();	//!< playermat�̏�����
	MATRIX matWorld;                //!< �v���C���[�̃��[���h�s��

	VECTOR moveTo;        //!< �v���C���[�̈ړ���
	VECTOR direction;     //!< �v���C���[�̌����Ă������
	VECTOR cameraPos;     //!< �J�����̈ʒu
	VECTOR cameraRot;     //!< �J�����̉�]

	int   modelHotaru;   //!< ��l���̃��f��
	int   attachAnim;    //!< �A�j���[�V�����̃A�^�b�`
	float totalTime;     //!< �A�j���[�V�����̑�����
	float playTime;      //!< �A�j���[�V�����̃X�s�[�h
	float attackTime;    //!< �U���A�j���[�V�����̃X�s�[�h
	float moveSpeed;     //!< �ړ��X�s�[�h
	float playerSize;    //!< �v���C���[�̃T�C�Y
	float angleX;        //!< �v���C���[�̌X��X
	float angleZ;        //!< �v���C���[�̌X��Z
	bool  isAction;      //!< �v���C���[�������Ă�����
	bool  isAttack;      //!< �U���{�^���������ꂽ��

	int textureNum; //!< �v���C���[�̃e�N�X�`����
	std::vector<std::string> textureName;
};