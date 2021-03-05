//---------------------------------------------------------------------------
//! @file   CameraPlayer.cpp
//!	@brief	�v���C���[������J����
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
CameraPlayer::CameraPlayer()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void CameraPlayer::Initialize()
{
	rot = VGet(0.0f, 0.0f, 0.0f);
	pos = VGet(0, 120, -100);
	isImGui = false;
	rotSpeed = 0.05f;
	adjustmentY = 10;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void CameraPlayer::Update()
{
	//! �J�����A�b�v�f�[�g���Ă�
	Camera::Update();

	ImGui();
}

//---------------------------------------------------------------------------
//! �J�����̈ړ�����
//---------------------------------------------------------------------------
void CameraPlayer::Move(Player* player)
{
	//! @retval true �J�������ړ�
	if (player->getIsAction()) {
		pos.x += player->getMovToX();
		pos.y += player->getMovToY();
		pos.z += player->getMovToZ();
	}

	//! �R���g���[���[��������p�̕ϐ���p��
	DINPUT_JOYSTATE Input;
	//! �R���g���[���[�̏����擾����(��Ő錾�����ϐ���n���Ă��̒��ɏ�������)
	GetJoypadDirectInputState(DX_INPUT_PAD1, &Input);

	//! �v���C���[�̎������]
	pos.x = (player->getPosX() + (DISTANCE_ADJUSTMENT) * sinf(rot.x));
	pos.z = (player->getPosZ() + (-DISTANCE_ADJUSTMENT) * cosf(rot.x));
	if (CheckHitKey(KEY_INPUT_RIGHT) || Input.Rx > 1) {
		rot.x -= rotSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || Input.Rx < -1) {
		rot.x += rotSpeed;
	}

	//! ��p���Z�b�g
	setPerspective(60.0f / 180.0f * DX_PI_F);
	//! �^�[�Q�b�g���Z�b�g
	setPositionAndTarget(pos, VGet(player->getPosX(), player->getPosY() + adjustmentY, player->getPosZ()));
}

//---------------------------------------------------------------------------
//! imgui�̏���
//---------------------------------------------------------------------------
void CameraPlayer::ImGui()
{
	//! @retval true imgui���J��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT)) {
		isImGui = true;
	}
	//! @retval false imgui�����
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT)) {
		isImGui = false;
	}

	if (isImGui) {
		ImGui::Begin("Camera");
		if (ImGui::TreeNode("Position")) { //!< �J�������W�̕ύX
			float* pPos[] = { &pos.x, &pos.y, &pos.z };
			ImGui::DragFloat3("##position", *pPos, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Rot")) {
			float* rRot[] = { &rot.x, &rot.y, &rot.z };
			ImGui::DragFloat3("##position", *rRot, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("RotSpeed")) {
			ImGui::DragFloat("##moveSpeed", &rotSpeed, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("adjustmentY")) {
			ImGui::DragFloat("##moveSpeed", &adjustmentY, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! �`�揈���i���g�Ȃ��j
//---------------------------------------------------------------------------
void CameraPlayer::Draw()
{
}


VECTOR CameraPlayer::getPos() { return pos; }