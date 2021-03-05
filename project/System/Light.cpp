//---------------------------------------------------------------------------
//!	@file	Light.cpp
//!	@brief	ライト
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
Light::Light()
{
	//! @retval true ライトを有効化
	isLightEnable = true;

	direction = VGet(15.0f, -20.0f, 15.0);
	
	difR = 1.0f;
	difG = 1.0f;
	difB = 1.0f;
	difA = 1.0f;
}

//---------------------------------------------------------------------------
//! 初期化処理
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
//! 更新処理
//---------------------------------------------------------------------------
void Light::Update()
{
	ImGui();
}

//---------------------------------------------------------------------------
//! imguiの処理
//---------------------------------------------------------------------------
void Light::ImGui()
{
	OpenAndCloseImGui();

	if (isImGui) {
		ImGui::Begin("Light");
		if (ImGui::TreeNode("SetLightEnable")) {
			//! チェックを外すとライトが無効
			ImGui::Checkbox("isSetLightEnable", &isLightEnable);
			ImGui::TreePop();
		}

		//! ライトの向き
		if (ImGui::TreeNode("Direction")) {
			float* ddir[] = { &direction.x, &direction.y, &direction.z};
			ImGui::DragFloat3("##Direction", *ddir, 0.03f, -FLT_MAX, FLT_MAX);
			ImGui::TreePop();
		}

		//! ディフューズカラー
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
//! 描画処理
//---------------------------------------------------------------------------
void Light::Draw()
{
	SetLightEnable(isLightEnable);
	SetLightDirection(direction);
	SetLightDifColor(GetColorF(difR, difG, difB, difA));
}
