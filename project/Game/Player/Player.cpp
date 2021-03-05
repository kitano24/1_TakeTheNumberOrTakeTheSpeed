//---------------------------------------------------------------------------
//!	@file	Player.cpp
//!	@brief	�v���C���[�̏���
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
Player::Player()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
Player::~Player()
{
	MV1DeleteModel(modelHotaru);
	MV1DetachAnim(modelHotaru, attachAnim);
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void Player::Initialize()
{
	playTime = 0.0f;
	playerSize = 1.0f;
	attackTime = 0.0f;
	moveSpeed = 1.0f;

	playerMat.m[3][0] = pos.x;
	playerMat.m[3][1] = pos.y;
	playerMat.m[3][2] = pos.z;

	isAttack = false;

	angleX = 0.0f;
	angleZ = 0.0f;

	//! 3D���f�����ړ�����s��̃Z�b�g
	MV1SetMatrix(modelHotaru, playerMat);

	//! �v���C���[�̏������W
	pos = VGet(0.0f, 100.0f, -160.0f);

	//! �v���C���[�̌����Ă������(����)
	direction = VGet(0.0f, 0.0f, 1.0f);

	//! @retval false �ҋ@���[�V�������Z�b�g
	isAction = false;

	//! @retval false �f�o�b�N�𖳌���
	isEnableDebug = false;

	isImGui = false;

	modelHotaru = MV1LoadModel("data/player/hotaru/hotaru.mv1");

	//! �e�N�X�`���\��t��
	Texture();

	//! �ҋ@�̃A�j���[�V�������A�^�b�`
	attachAnim = MV1AttachAnim(modelHotaru, WAITING, -1, FALSE);

	//! �A�j���[�V�����̑����Ԃ��擾
	totalTime = MV1GetAttachAnimTotalTime(modelHotaru, attachAnim);

	hitPos = VGet(pos.x, pos.y, pos.z);

	cameraPos = VGet(0, 0, 0);
	cameraRot = VGet(0, 0, 0);
}

//---------------------------------------------------------------------------
//! �L�����N�^�[�ƌ��̃e�N�X�`���\��t��
//---------------------------------------------------------------------------
void Player::Texture()
{
	//! �L�����̃e�N�X�`��
	int GrHandle1 = LoadGraph("data/player/hotaru/playerTexture/hair.png");
	int GrHandle2 = LoadGraph("data/player/hotaru/playerTexture/face.png");
	int GrHandle4 = LoadGraph("data/player/hotaru/playerTexture/mc3.png");
	int GrHandle6 = LoadGraph("data/player/hotaru/playerTexture/attire.png");

	//! ���̃e�N�X�`��
	int GrHandle8  = LoadGraph("data/player/hotaru/swordTexture/bltg.png");

	textureNum = MV1GetTextureNum(modelHotaru);

	for (int i = 0; i < textureNum; i++) {
		textureName.push_back(MV1GetTextureName(modelHotaru, i));
	}

	//! �L�����̃e�N�X�`��
	MV1SetTextureGraphHandle(modelHotaru, 1, GrHandle1, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 2, GrHandle2, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 4, GrHandle4, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 6, GrHandle6, TRUE);

	//! ���̃e�N�X�`��
	MV1SetTextureGraphHandle(modelHotaru, 8, GrHandle8, TRUE);
}

//---------------------------------------------------------------------------
//! ���f���̈ړ�����
//---------------------------------------------------------------------------
void Player::Move()
{
	moveTo = VGet(0.0f, 0.0f, 0.0f);

	//! @retval false �U���{�^����������Ă��Ȃ���Έړ��ł���
	if (!isAttack) {

		//-------------------------------------------------------------
        //!	@name	�L�[�{�[�h
        //-------------------------------------------------------------
		//! �J�����������Ă�������icameraRot.x == 0.0f�j�ɐi��
		if (CheckHitKey(KEY_INPUT_W))
		{
			Rot();
		}
		if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_A))
		{
			//! �J�����̌����Ă���͂��̒l�����������Ɍ�����
			cameraRot.x += (135 * (DX_PI_F / 180));
			Rot();
		}
		else if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_D))
		{
			//! �J�����̌����Ă���͂��̒l�����������Ɍ�����
			cameraRot.x += ((180 + 45) * (DX_PI_F / 180));
			Rot();
		}
    	//! �J�����������Ă�������icameraRot.x�@== 0.0f�j�ɐi��
		else if (CheckHitKey(KEY_INPUT_S))
		{
			//! �J�����̌����Ă���͂��̒l�����������Ɍ�����
			cameraRot.x += (180 * (DX_PI_F / 180));
			Rot();
		}
		//! ���E�ړ�
		else if (CheckHitKey(KEY_INPUT_A)) {
			//! �J�����̌����Ă���͂��̒l���������E�Ɍ�����
			cameraRot.x += (90 * (DX_PI_F / 180));
			Rot();
		}
		else if (CheckHitKey(KEY_INPUT_D)) {
			//! �J�����̌����Ă���͂��̒l�����������Ɍ�����
			cameraRot.x += (270 * (DX_PI_F / 180));
			Rot();
		}

		//-------------------------------------------------------------
        //!	@name	�Q�[���p�b�h
        //-------------------------------------------------------------
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP)
		{
			Rot();
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)
		{
			cameraRot.x += (135 * (DX_PI_F / 180));
			Rot();
		}
		else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
		{
			cameraRot.x += ((180 + 45) * (DX_PI_F / 180));
			Rot();
		}
		else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN)
		{
			cameraRot.x += (180 * (DX_PI_F / 180));
			Rot();
		}
		else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) {
			cameraRot.x += (90 * (DX_PI_F / 180));
			Rot();
		}
		else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) {
			cameraRot.x += (270 * (DX_PI_F / 180));
			Rot();
		}
	}

	//! �ړ����E�l
	const float skyDomeLimit = 600.0f;
	//! �v���C���[��߂�
	const float prayerReturn = skyDomeLimit;
	//! �X�J�C�h�[������o�Ȃ��悤�ɂ���
	if (pos.z > skyDomeLimit) {
		pos.z = prayerReturn;
	}
	if (pos.z < -skyDomeLimit) {
		pos.z = -prayerReturn;
	}
	if (pos.x > skyDomeLimit) {
		pos.x = prayerReturn;
	}
	if (pos.x < -skyDomeLimit) {
		pos.x = -prayerReturn;
	}

	isAction = false;

	if (VSquareSize(moveTo) != 0.0f) {
		isAction = true;
		moveTo = VNorm(moveTo);
		direction = moveTo;
		/*! @details�@DX���C�u�����̊֐� VNorm() �Ƀo�O�����������߁A�m�[�}���C�Y�� 
		 ���������邩�A�ϐ� moveTo ���֐� Move �ŏ��������邱�Ƃŉ���
		 */
		//! �m�[�}���C�Y������
		//float l = sqrtf(moveTo.x * moveTo.x + moveTo.y * moveTo.y + moveTo.z * moveTo.z);
		//moveTo.x /= l;
		//moveTo.y /= l;
		//moveTo.z /= l;
	}

	pos = VAdd(pos, moveTo);

	//! ���[���h�s��𐶐�
	WorldMat();
}

//---------------------------------------------------------------------------
//! �J�����̌����Ă�������Ɉړ�
//---------------------------------------------------------------------------
void Player::Rot()
{
	moveTo.x += moveSpeed * sinf(-cameraRot.x);
	moveTo.z += moveSpeed * cosf(cameraRot.x);
}

//---------------------------------------------------------------------------
//! ��l���̃A�j���[�V����
//---------------------------------------------------------------------------
void Player::Animation()
{
	//! �A�j���[�V�������f�^�b�`
	MV1DetachAnim(modelHotaru, attachAnim);

	switch (charaAnim)
	{
	case CharaAnim::Waiting: //!< �ҋ@
		attachAnim = MV1AttachAnim(modelHotaru, WAITING, -1, FALSE);
		break;

	case CharaAnim::Run:     //!< ����
		attachAnim = MV1AttachAnim(modelHotaru, RUN, -1, FALSE);
		break;

	case CharaAnim::Attack:  //!< �U��
		attachAnim = MV1AttachAnim(modelHotaru, ATTACK, -1, FALSE);
		//! �A�^�b�`���Ă���A�j���[�V�����i�U���j�̍Đ����Ԃ�ݒ肷��
		MV1SetAttachAnimTime(modelHotaru, attachAnim, attackTime);
		break;
	}

	//! �ҋ@�A�j���[�V�����̃��[�v����
	playTime += 1.0f;
	if (playTime > totalTime - 1.5f) {
		playTime = 0.0f;
	}

	//! �A�^�b�`���Ă���A�j���[�V�����i�ҋ@�Ƒ���j�̍Đ����Ԃ�ݒ肷��
	MV1SetAttachAnimTime(modelHotaru, attachAnim, playTime);

	//! �g�[�^���^�C�����Ď擾
	totalTime = MV1GetAttachAnimTotalTime(modelHotaru, attachAnim);
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void Player::Update()
{
	//! @retval true ����A�j���[�V�������A�^�b�`
	if (isAction) {
		charaAnim = CharaAnim::Run;
	}
	//! @retval false �ҋ@�A�j���[�V�������A�^�b�`
	else {
		charaAnim = CharaAnim::Waiting;
	}

	//! R�L�[�A��������PAD��X�������ꂽ��U��
	if (IsKeyOn(KEY_INPUT_R) || IsPadOn(PAD_X)) {
		isAttack = true;
		//! �a���������Đ�
		PlaySoundFile("data/sound/attack.mp3", DX_PLAYTYPE_BACK);
	}

	//! @retval true �U�����[�V�������Đ�
	if (isAttack)
	{
		//! �A�j���[�V�������U���ɕύX
		charaAnim = CharaAnim::Attack;
		//! �U�����[�V�����̍Đ����x
		attackTime += 1.0f;
		//! �U���A�j���[�V�����Đ�����
		if (attackTime > totalTime - 5.0f) {
			isAttack = false;
			attackTime = 0;
		}
	}

	//! �A�j���[�V�������Z�b�g
	Animation();

	//! �v���C���[�̈ړ����Z�b�g
	Move();

	//! imgui���Z�b�g
	ImGui();

	//! �����蔻��X�V
	hitPos = VGet(pos.x, pos.y + 10, pos.z);
}

//---------------------------------------------------------------------------
//! ���[���h�s��
//---------------------------------------------------------------------------
void Player::WorldMat()
{
	//! �P�ʍs����쐬����
	CreateIdentityMatrix(&matWorld);

	// ���[���h�s��̐���
	// �s��̓����͉��L�̒ʂ�
	// |  axisX.x  axisX.y  axisX.z  0.0f |
	// |  axisY.x  axisY.y  axisY.z  0.0f |
	// |  axisZ.x  axisZ.y  axisZ.z  0.0f |
	// |  x        y        z        1.0f |

	//! Y��
	VECTOR	axisY = VGet(angleX, playerSize, angleZ);
	//! Z��
	VECTOR	axisZ = VScale(direction, -1.0f);
	//! X��
	VECTOR	axisX = VCross(axisY, axisZ);

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

	//! ���f���̍��W�ϊ��p�s����Z�b�g
	MV1SetMatrix(modelHotaru, matWorld);
}

//---------------------------------------------------------------------------
//! imgui�̏���
//---------------------------------------------------------------------------
void Player::ImGui()
{
	OpenAndCloseImGui();

	//! �v���C���[�̏���imgui�ŕύX
	if (isImGui) {
		ImGui::Begin("Player");
		if (ImGui::TreeNode("Position")) { //!< �v���C���[���W�̕ύX
			float* pPos[] = { &pos.x, &pos.y, &pos.z };
			ImGui::DragFloat3("##position", *pPos, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("direction")) {
			float* dDir[] = { &direction.x, &direction.y, &direction.z };
			ImGui::DragFloat3("##direction", *dDir, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("angleX")) {
			ImGui::DragFloat("##moveSpeed", &angleX, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("angleZ")) {
			ImGui::DragFloat("##moveSpeed", &angleZ, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Move")) {
			ImGui::DragFloat("##moveSpeed", &moveSpeed, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("PlayerSize")) {
			ImGui::DragFloat("##PlayerSize", &playerSize, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("HitSize")) {
			ImGui::DragFloat("##HitSize", &hitSize, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Debug")) { //!< �v���C���[�̃f�o�b�O���l��ON,OFF
			ImGui::Checkbox("isEnableDebug", &isEnableDebug);
			ImGui::TreePop();
		}
		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void Player::Draw()
{
	//! �J�v�Z�����`�������_���̈�_�̍��W
	VECTOR posUp = pos;
	posUp.y = pos.y + 14.0f;

	MV1DrawModel(modelHotaru);

	//! @retval true �f�o�b�N��L����	
	if (isEnableDebug) {
		DrawCapsule3D(pos, posUp, 3, 10, RED, RED, FALSE);
		DrawSphere3D(hitPos, hitSize, 20, RED, RED, FALSE);
		printfDx("���Đ�����%.1f\n", totalTime);
		printfDx("�Đ�����%.1f\n", playTime);
		printfDx("PlayerX%f\n", pos.x);
		printfDx("PlayerY%f\n", pos.y);
		printfDx("PlayerZ%f\n", pos.z);
		printfDx("�e�N�X�`����%d\n", textureNum);
	}
}

//---------------------------------------------------------------------------
//! @param�ipos�j �J�����̈ʒu��ݒ�
//---------------------------------------------------------------------------
void Player::setCameraPos(const VECTOR& pos) {
	cameraPos = pos;
}

//---------------------------------------------------------------------------
//! @param�irot�j �J�����̉�]��ݒ�
//---------------------------------------------------------------------------
void Player::setCameraRot(const VECTOR& rot) {
	cameraRot = rot;
}
