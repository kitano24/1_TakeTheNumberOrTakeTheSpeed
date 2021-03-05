//---------------------------------------------------------------------------
//!	@file	Map.cpp
//!	@brief	スカイドーム描画
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
Map::Map()
{
	skyDome = MV1LoadModel("data/skyDome/Dome_TG103.mv1");
	isEnableLine = false; //!< @retval false ラインを描画しない
}

//---------------------------------------------------------------------------
//! デストラクター
//---------------------------------------------------------------------------
Map::~Map()
{
	MV1DeleteModel(skyDome);
}

//---------------------------------------------------------------------------
//! 初期化処理
//---------------------------------------------------------------------------
void Map::Initialize()
{
	isImGui = false;
	isEnableLine = false;
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void Map::Update()
{
	ImGui();
}

//---------------------------------------------------------------------------
//! imguiの処理
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
//! 描画処理
//---------------------------------------------------------------------------
void Map::Draw()
{
	MV1DrawModel(skyDome);

	VECTOR linePos1;
	VECTOR linePos2;

	SetUseZBufferFlag(TRUE);

	//! @retval true ラインを描画
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
