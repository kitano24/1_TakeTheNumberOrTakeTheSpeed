//---------------------------------------------------------------------------
//!	@file	Light.cpp
//!	@brief	���C�g
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
Light::Light()
{
	//! @retval true ���C�g��L����
	isLightEnable = true;

	direction = VGet(15.0f, -20.0f, 15.0);
	
	difR = 1.0f;
	difG = 1.0f;
	difB = 1.0f;
	difA = 1.0f;
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void Light::Initialize()
{
	isLightEnable = true;
	isImGui = false;
	direction = VGet(15.0f, -20.0f, 15.0);

	difR = 1.0f;
	difG = 1.0f;
	difB = 1.0f;
	difA = 1.0f;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void Light::Update()
{
	ImGui();
}

//---------------------------------------------------------------------------
//! imgui�̏���
//---------------------------------------------------------------------------
void Light::ImGui()
{
	OpenAndCloseImGui();

	if (isImGui) {
		ImGui::Begin("Light");
		if (ImGui::TreeNode("SetLightEnable")) {
			//! �`�F�b�N���O���ƃ��C�g������
			ImGui::Checkbox("isSetLightEnable", &isLightEnable);
			ImGui::TreePop();
		}

		//! ���C�g�̌���
		if (ImGui::TreeNode("Direction")) {
			float* ddir[] = { &direction.x, &direction.y, &direction.z};
			ImGui::DragFloat3("##Direction", *ddir, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		//! �f�B�t���[�Y�J���[
		if (ImGui::TreeNode("DifColor")) {
			ImGui::InputFloat("R", &difR);
			ImGui::InputFloat("G", &difG);
			ImGui::InputFloat("B", &difB);
			ImGui::InputFloat("A", &difA);
			ImGui::TreePop();
		}
		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void Light::Draw()
{
	SetLightEnable(isLightEnable);
	SetLightDirection(direction);
	SetLightDifColor(GetColorF(difR, difG, difB, difA));
}
