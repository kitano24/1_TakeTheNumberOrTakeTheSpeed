//---------------------------------------------------------------------------
//! @file   CameraPlayer.cpp
//!	@brief	プレイヤーを見るカメラ
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
CameraPlayer::CameraPlayer()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! 初期化処理
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
//! 更新処理
//---------------------------------------------------------------------------
void CameraPlayer::Update()
{
	//! カメラアップデートを呼ぶ
	Camera::Update();

	ImGui();
}

//---------------------------------------------------------------------------
//! カメラの移動処理
//---------------------------------------------------------------------------
void CameraPlayer::Move(Player* player)
{
	//! @retval true カメラが移動
	if (player->getIsAction()) {
		pos.x += player->getMovToX();
		pos.y += player->getMovToY();
		pos.z += player->getMovToZ();
	}

	//! コントローラー情報を入れる用の変数を用意
	DINPUT_JOYSTATE Input;
	//! コントローラーの情報を取得する(上で宣言した変数を渡してその中に情報を入れる)
	GetJoypadDirectInputState(DX_INPUT_PAD1, &Input);

	//! プレイヤーの周りを回転
	pos.x = (player->getPosX() + (DISTANCE_ADJUSTMENT) * sinf(rot.x));
	pos.z = (player->getPosZ() + (-DISTANCE_ADJUSTMENT) * cosf(rot.x));
	if (CheckHitKey(KEY_INPUT_RIGHT) || Input.Rx > 1) {
		rot.x -= rotSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || Input.Rx < -1) {
		rot.x += rotSpeed;
	}

	//! 画角をセット
	setPerspective(60.0f / 180.0f * DX_PI_F);
	//! ターゲットをセット
	setPositionAndTarget(pos, VGet(player->getPosX(), player->getPosY() + adjustmentY, player->getPosZ()));
}

//---------------------------------------------------------------------------
//! imguiの処理
//---------------------------------------------------------------------------
void CameraPlayer::ImGui()
{
	//! @retval true imguiを開く
	if ((GetMouseInput() & MOUSE_INPUT_LEFT)) {
		isImGui = true;
	}
	//! @retval false imguiを閉じる
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT)) {
		isImGui = false;
	}

	if (isImGui) {
		ImGui::Begin("Camera");
		if (ImGui::TreeNode("Position")) { //!< カメラ座標の変更
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
//! 描画処理（中身なし）
//---------------------------------------------------------------------------
void CameraPlayer::Draw()
{
}


VECTOR CameraPlayer::getPos() { return pos; }