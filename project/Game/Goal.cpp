//---------------------------------------------------------------------------
//!	@file	Goal.cpp
//!	@brief	ゴールの処理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
Goal::Goal()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! デストラクター
//---------------------------------------------------------------------------
Goal::~Goal()
{
	MV1DeleteModel(modelGoal);
}

//---------------------------------------------------------------------------
//! 初期化処理
//---------------------------------------------------------------------------
void Goal::Initialize()
{
	modelGoal = MV1LoadModel("data/goal/ゴールゲート.mv1");

	//! ゴールの初期座標
	pos = VGet(0.0f, GOAL_Y, 0.0f);

	//! ゴールの初期座標
	GoalMat.m[3][0] = pos.x;
	GoalMat.m[3][1] = pos.y;
	GoalMat.m[3][2] = pos.z;

	//! ゴールのサイズ
	GoalMat.m[0][0] = GOAL_SIZE_X;
	GoalMat.m[1][1] = GOAL_SIZE_Y;
	GoalMat.m[2][2] = GOAL_SIZE_Z;

	//! ゴールのテクスチャ貼り付け
	int GrHandle1 = LoadGraph("data/goal/goalTexture.png");
	textureNum = MV1GetTextureNum(modelGoal);
	for (int i = 0; i < textureNum; i++) {
		textureName.push_back(MV1GetTextureName(modelGoal, i));
		MV1SetTextureGraphHandle(modelGoal, i, GrHandle1, TRUE);
	}

	//! フォントサイズを指定
	fontSize = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_NORMAL);
	messageFontSize = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_NORMAL);
	countFontSize = CreateFontToHandle(NULL, 70, 3, DX_FONTTYPE_NORMAL);

	time = 0;
	count = 0;
	missedCount = 0;
	flashingCount = 0;
	isAppearing = false; //!< @retval false ゴールは出現させない
	isEnableDebug = false;
	isHit = false;
	isImGui = false;

	//! 3Dモデルを移動する行列のセット
	MV1SetMatrix(modelGoal, GoalMat);
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void Goal::Update()
{
	count++;

	if (count <= 6000) flashingCount++;

	if (count > 6000) flashingCount += 5;

	//! 20秒になったらゴールが出現
	//! 出現してから20秒間は初期座標
	if (count > 1200) {
		isAppearing = true; //!< @retval true ゴールが出現
	}

	//! @details　ゴールが出現してから20秒が経過したら20秒ごとにゴールがランダム出現
	if (isAppearing  && count % 1200 == 0) {
		//! ゴールが移動するときに流れるSE
		PlaySoundFile("data/sound/warp.wav", DX_PLAYTYPE_BACK);
		pos.x = (float)GetRand(1100) - 550;
		pos.z = (float)GetRand(1100) - 550;

		GoalMat.m[3][0] = pos.x;
		GoalMat.m[3][1] = pos.y;
		GoalMat.m[3][2] = pos.z;

		missedCount += 1;

		MV1SetMatrix(modelGoal, GoalMat);
	}

	//! 60フレームごとに1増やす
	if (count % 60 == 0) {
		time++;
	}
	if (flashingCount == 120) flashingCount = 0;

	ImGui();
}

//---------------------------------------------------------------------------
//! imguiの処理
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
			//! チェックを入れるとゴール
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
//! 描画処理
//---------------------------------------------------------------------------
void Goal::Draw()
{
	//! 画面の中心に「ゴールが出現」と描画
	if (isAppearing && count < 2400) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
		DrawBox(0, 380, 1920, 500, BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(730, 400, "ゴールが出現", RED, fontSize);
	}

	//! @details　ゴールが出現して20秒を超えると左端に「ゴールが移動中」と描画
	if (isAppearing && count > 2400) {
		if (flashingCount > 0 && flashingCount < 60) {
			DrawStringToHandle(10, 100, "ゴールが移動中", RED, fontSize);
		}
	}

	//! @retval true ゴールが出現
	if (isAppearing) {
		DrawStringToHandle(10, 250, "ゴールを見逃した回数", RED, messageFontSize);
		
		//! 見逃した回数を描画
		char missedCount_[256];
		sprintf_s(missedCount_, "%d", missedCount);
		DrawFormatStringToHandle(440, 240, BLACK, countFontSize, missedCount_);
	
		//! ゴールのモデル
		MV1DrawModel(modelGoal);
	}

	//! @retval true デバックを有効化
	if (isEnableDebug) {
		//! ゴールの当たり判定の大きさ
		DrawSphere3D(pos, hitSize, 10, RED, RED, false);

		char text[256];
		sprintf_s(text, "%d", time);
		printfDx("count%d\n", count);
		printfDx("GoalX%f\n", pos.x);
		printfDx("GoalZ%f\n", pos.z);
	}
}
