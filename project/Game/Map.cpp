//---------------------------------------------------------------------------
//!	@file	Map.cpp
//!	@brief	�X�J�C�h�[���`��
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
Map::Map()
{
	skyDome = MV1LoadModel("data/skyDome/Dome_TG103.mv1");
	isEnableLine = false; //!< @retval false ���C����`�悵�Ȃ�
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
Map::~Map()
{
	MV1DeleteModel(skyDome);
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void Map::Initialize()
{
	isImGui = false;
	isEnableLine = false;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void Map::Update()
{
	ImGui();
}

//---------------------------------------------------------------------------
//! imgui�̏���
//---------------------------------------------------------------------------
void Map::ImGui()
{
	OpenAndCloseImGui();

	if (isImGui) {
		ImGui::Begin("Map");
		if (ImGui::TreeNode("Line")) { 
			ImGui::Checkbox("isEnableLine", &isEnableLine);
			ImGui::TreePop();
		}
		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void Map::Draw()
{
	MV1DrawModel(skyDome);

	VECTOR linePos1;
	VECTOR linePos2;

	SetUseZBufferFlag(TRUE);

	//! @retval true ���C����`��
	if (isEnableLine) {
		linePos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		linePos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (int i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(linePos1, linePos2, WHITE);
			linePos1.x += LINE_AREA_SIZE / LINE_NUM;
			linePos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		linePos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		linePos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (int i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(linePos1, linePos2, WHITE);
			linePos1.z += LINE_AREA_SIZE / LINE_NUM;
			linePos2.z += LINE_AREA_SIZE / LINE_NUM;
		}
	}
}
