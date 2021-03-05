//---------------------------------------------------------------------------
//!	@file	Goal.cpp
//!	@brief	�S�[���̏���
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
Goal::Goal()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
Goal::~Goal()
{
	MV1DeleteModel(modelGoal);
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void Goal::Initialize()
{
	modelGoal = MV1LoadModel("data/goal/�S�[���Q�[�g.mv1");

	//! �S�[���̏������W
	pos = VGet(0.0f, GOAL_Y, 0.0f);

	//! �S�[���̏������W
	GoalMat.m[3][0] = pos.x;
	GoalMat.m[3][1] = pos.y;
	GoalMat.m[3][2] = pos.z;

	//! �S�[���̃T�C�Y
	GoalMat.m[0][0] = GOAL_SIZE_X;
	GoalMat.m[1][1] = GOAL_SIZE_Y;
	GoalMat.m[2][2] = GOAL_SIZE_Z;

	//! �S�[���̃e�N�X�`���\��t��
	int GrHandle1 = LoadGraph("data/goal/goalTexture.png");
	textureNum = MV1GetTextureNum(modelGoal);
	for (int i = 0; i < textureNum; i++) {
		textureName.push_back(MV1GetTextureName(modelGoal, i));
		MV1SetTextureGraphHandle(modelGoal, i, GrHandle1, TRUE);
	}

	//! �t�H���g�T�C�Y���w��
	fontSize = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_NORMAL);
	messageFontSize = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_NORMAL);
	countFontSize = CreateFontToHandle(NULL, 70, 3, DX_FONTTYPE_NORMAL);

	time = 0;
	count = 0;
	missedCount = 0;
	flashingCount = 0;
	isAppearing = false; //!< @retval false �S�[���͏o�������Ȃ�
	isEnableDebug = false;
	isHit = false;
	isImGui = false;

	//! 3D���f�����ړ�����s��̃Z�b�g
	MV1SetMatrix(modelGoal, GoalMat);
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void Goal::Update()
{
	count++;

	if (count <= 6000) flashingCount++;

	if (count > 6000) flashingCount += 5;

	//! 20�b�ɂȂ�����S�[�����o��
	//! �o�����Ă���20�b�Ԃ͏������W
	if (count > 1200) {
		isAppearing = true; //!< @retval true �S�[�����o��
	}

	//! @details�@�S�[�����o�����Ă���20�b���o�߂�����20�b���ƂɃS�[���������_���o��
	if (isAppearing  && count % 1200 == 0) {
		//! �S�[�����ړ�����Ƃ��ɗ����SE
		PlaySoundFile("data/sound/warp.wav", DX_PLAYTYPE_BACK);
		pos.x = (float)GetRand(1100) - 550;
		pos.z = (float)GetRand(1100) - 550;

		GoalMat.m[3][0] = pos.x;
		GoalMat.m[3][1] = pos.y;
		GoalMat.m[3][2] = pos.z;

		missedCount += 1;

		MV1SetMatrix(modelGoal, GoalMat);
	}

	//! 60�t���[�����Ƃ�1���₷
	if (count % 60 == 0) {
		time++;
	}
	if (flashingCount == 120) flashingCount = 0;

	ImGui();
}

//---------------------------------------------------------------------------
//! imgui�̏���
//---------------------------------------------------------------------------
void Goal::ImGui()
{
	OpenAndCloseImGui();

	if (isImGui) {
		ImGui::Begin("Goal");
		if (ImGui::TreeNode("Position")) {
			float* pPos[] = { &pos.x, &pos.y, &pos.z };
			ImGui::DragFloat3("##position", *pPos, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("HitSize")) {
			ImGui::DragFloat("##HitSize", &hitSize, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Goal")) {
			//! �`�F�b�N������ƃS�[��
			ImGui::Checkbox("isGoal", &isHit);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Debug")) {
			ImGui::Checkbox("isEnableDebug", &isEnableDebug);
			ImGui::TreePop();
		}
		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void Goal::Draw()
{
	//! ��ʂ̒��S�Ɂu�S�[�����o���v�ƕ`��
	if (isAppearing && count < 2400) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
		DrawBox(0, 380, 1920, 500, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(730, 400, "�S�[�����o��", RED, fontSize);
	}

	//! @details�@�S�[�����o������20�b�𒴂���ƍ��[�Ɂu�S�[�����ړ����v�ƕ`��
	if (isAppearing && count > 2400) {
		if (flashingCount > 0 && flashingCount < 60) {
			DrawStringToHandle(10, 100, "�S�[�����ړ���", RED, fontSize);
		}
	}

	//! @retval true �S�[�����o��
	if (isAppearing) {
		DrawStringToHandle(10, 250, "�S�[��������������", RED, messageFontSize);
		
		//! ���������񐔂�`��
		char missedCount_[256];
		sprintf_s(missedCount_, "%d", missedCount);
		DrawFormatStringToHandle(440, 240, BLACK, countFontSize, missedCount_);
	
		//! �S�[���̃��f��
		MV1DrawModel(modelGoal);
	}

	//! @retval true �f�o�b�N��L����
	if (isEnableDebug) {
		//! �S�[���̓����蔻��̑傫��
		DrawSphere3D(pos, hitSize, 10, RED, RED, false);

		char text[256];
		sprintf_s(text, "%d", time);
		printfDx("count%d\n", count);
		printfDx("GoalX%f\n", pos.x);
		printfDx("GoalZ%f\n", pos.z);
	}
}
