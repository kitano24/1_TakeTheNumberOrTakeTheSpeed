//---------------------------------------------------------------------------
//!	@file	Player.cpp
//!	@brief	プレイヤーの処理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
Player::Player()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! デストラクター
//---------------------------------------------------------------------------
Player::~Player()
{
	MV1DeleteModel(modelHotaru);
	MV1DetachAnim(modelHotaru, attachAnim);
}

//---------------------------------------------------------------------------
//! 初期化処理
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

	//! 3Dモデルを移動する行列のセット
	MV1SetMatrix(modelHotaru, playerMat);

	//! プレイヤーの初期座標
	pos = VGet(0.0f, 100.0f, -160.0f);

	//! プレイヤーの向いている方向(正面)
	direction = VGet(0.0f, 0.0f, 1.0f);

	//! @retval false 待機モーションをセット
	isAction = false;

	//! @retval false デバックを無効化
	isEnableDebug = false;

	isImGui = false;

	modelHotaru = MV1LoadModel("data/player/hotaru/hotaru.mv1");

	//! テクスチャ貼り付け
	Texture();

	//! 待機のアニメーションをアタッチ
	attachAnim = MV1AttachAnim(modelHotaru, WAITING, -1, FALSE);

	//! アニメーションの総時間を取得
	totalTime = MV1GetAttachAnimTotalTime(modelHotaru, attachAnim);

	hitPos = VGet(pos.x, pos.y, pos.z);

	cameraPos = VGet(0, 0, 0);
	cameraRot = VGet(0, 0, 0);
}

//---------------------------------------------------------------------------
//! キャラクターと剣のテクスチャ貼り付け
//---------------------------------------------------------------------------
void Player::Texture()
{
	//! キャラのテクスチャ
	int GrHandle1 = LoadGraph("data/player/hotaru/playerTexture/hair.png");
	int GrHandle2 = LoadGraph("data/player/hotaru/playerTexture/face.png");
	int GrHandle4 = LoadGraph("data/player/hotaru/playerTexture/mc3.png");
	int GrHandle6 = LoadGraph("data/player/hotaru/playerTexture/attire.png");

	//! 剣のテクスチャ
	int GrHandle8  = LoadGraph("data/player/hotaru/swordTexture/bltg.png");

	textureNum = MV1GetTextureNum(modelHotaru);

	for (int i = 0; i < textureNum; i++) {
		textureName.push_back(MV1GetTextureName(modelHotaru, i));
	}

	//! キャラのテクスチャ
	MV1SetTextureGraphHandle(modelHotaru, 1, GrHandle1, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 2, GrHandle2, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 4, GrHandle4, TRUE);
	MV1SetTextureGraphHandle(modelHotaru, 6, GrHandle6, TRUE);

	//! 剣のテクスチャ
	MV1SetTextureGraphHandle(modelHotaru, 8, GrHandle8, TRUE);
}

//---------------------------------------------------------------------------
//! モデルの移動処理
//---------------------------------------------------------------------------
void Player::Move()
{
	moveTo = VGet(0.0f, 0.0f, 0.0f);

	//! @retval false 攻撃ボタンが押されていなければ移動できる
	if (!isAttack) {

		//-------------------------------------------------------------
        //!	@name	キーボード
        //-------------------------------------------------------------
		//! カメラが向いている方向（cameraRot.x == 0.0f）に進む
		if (CheckHitKey(KEY_INPUT_W))
		{
			Rot();
		}
		if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_A))
		{
			//! カメラの向いているはずの値だけをを後ろに向ける
			cameraRot.x += (135 * (DX_PI_F / 180));
			Rot();
		}
		else if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_D))
		{
			//! カメラの向いているはずの値だけをを後ろに向ける
			cameraRot.x += ((180 + 45) * (DX_PI_F / 180));
			Rot();
		}
    	//! カメラが向いている方向（cameraRot.x　== 0.0f）に進む
		else if (CheckHitKey(KEY_INPUT_S))
		{
			//! カメラの向いているはずの値だけをを後ろに向ける
			cameraRot.x += (180 * (DX_PI_F / 180));
			Rot();
		}
		//! 左右移動
		else if (CheckHitKey(KEY_INPUT_A)) {
			//! カメラの向いているはずの値だけをを右に向ける
			cameraRot.x += (90 * (DX_PI_F / 180));
			Rot();
		}
		else if (CheckHitKey(KEY_INPUT_D)) {
			//! カメラの向いているはずの値だけをを左に向ける
			cameraRot.x += (270 * (DX_PI_F / 180));
			Rot();
		}

		//-------------------------------------------------------------
        //!	@name	ゲームパッド
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

	//! 移動限界値
	const float skyDomeLimit = 600.0f;
	//! プレイヤーを戻す
	const float prayerReturn = skyDomeLimit;
	//! スカイドームから出ないようにする
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
		/*! @details　DXライブラリの関数 VNorm() にバグがあったため、ノーマライズを 
		 直書きするか、変数 moveTo を関数 Move で初期化することで解決
		 */
		//! ノーマライズ直書き
		//float l = sqrtf(moveTo.x * moveTo.x + moveTo.y * moveTo.y + moveTo.z * moveTo.z);
		//moveTo.x /= l;
		//moveTo.y /= l;
		//moveTo.z /= l;
	}

	pos = VAdd(pos, moveTo);

	//! ワールド行列を生成
	WorldMat();
}

//---------------------------------------------------------------------------
//! カメラの向いている方向に移動
//---------------------------------------------------------------------------
void Player::Rot()
{
	moveTo.x += moveSpeed * sinf(-cameraRot.x);
	moveTo.z += moveSpeed * cosf(cameraRot.x);
}

//---------------------------------------------------------------------------
//! 主人公のアニメーション
//---------------------------------------------------------------------------
void Player::Animation()
{
	//! アニメーションをデタッチ
	MV1DetachAnim(modelHotaru, attachAnim);

	switch (charaAnim)
	{
	case CharaAnim::Waiting: //!< 待機
		attachAnim = MV1AttachAnim(modelHotaru, WAITING, -1, FALSE);
		break;

	case CharaAnim::Run:     //!< 走る
		attachAnim = MV1AttachAnim(modelHotaru, RUN, -1, FALSE);
		break;

	case CharaAnim::Attack:  //!< 攻撃
		attachAnim = MV1AttachAnim(modelHotaru, ATTACK, -1, FALSE);
		//! アタッチしているアニメーション（攻撃）の再生時間を設定する
		MV1SetAttachAnimTime(modelHotaru, attachAnim, attackTime);
		break;
	}

	//! 待機アニメーションのループ処理
	playTime += 1.0f;
	if (playTime > totalTime - 1.5f) {
		playTime = 0.0f;
	}

	//! アタッチしているアニメーション（待機と走る）の再生時間を設定する
	MV1SetAttachAnimTime(modelHotaru, attachAnim, playTime);

	//! トータルタイムを再取得
	totalTime = MV1GetAttachAnimTotalTime(modelHotaru, attachAnim);
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void Player::Update()
{
	//! @retval true 走るアニメーションをアタッチ
	if (isAction) {
		charaAnim = CharaAnim::Run;
	}
	//! @retval false 待機アニメーションをアタッチ
	else {
		charaAnim = CharaAnim::Waiting;
	}

	//! Rキー、もしくはPADのXが押されたら攻撃
	if (IsKeyOn(KEY_INPUT_R) || IsPadOn(PAD_X)) {
		isAttack = true;
		//! 斬撃音声を再生
		PlaySoundFile("data/sound/attack.mp3", DX_PLAYTYPE_BACK);
	}

	//! @retval true 攻撃モーションを再生
	if (isAttack)
	{
		//! アニメーションを攻撃に変更
		charaAnim = CharaAnim::Attack;
		//! 攻撃モーションの再生速度
		attackTime += 1.0f;
		//! 攻撃アニメーション再生時間
		if (attackTime > totalTime - 5.0f) {
			isAttack = false;
			attackTime = 0;
		}
	}

	//! アニメーションをセット
	Animation();

	//! プレイヤーの移動をセット
	Move();

	//! imguiをセット
	ImGui();

	//! 当たり判定更新
	hitPos = VGet(pos.x, pos.y + 10, pos.z);
}

//---------------------------------------------------------------------------
//! ワールド行列
//---------------------------------------------------------------------------
void Player::WorldMat()
{
	//! 単位行列を作成する
	CreateIdentityMatrix(&matWorld);

	// ワールド行列の生成
	// 行列の内部は下記の通り
	// |  axisX.x  axisX.y  axisX.z  0.0f |
	// |  axisY.x  axisY.y  axisY.z  0.0f |
	// |  axisZ.x  axisZ.y  axisZ.z  0.0f |
	// |  x        y        z        1.0f |

	//! Y軸
	VECTOR	axisY = VGet(angleX, playerSize, angleZ);
	//! Z軸
	VECTOR	axisZ = VScale(direction, -1.0f);
	//! X軸
	VECTOR	axisX = VCross(axisY, axisZ);

	//! 行列に設定
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

	//! モデルの座標変換用行列をセット
	MV1SetMatrix(modelHotaru, matWorld);
}

//---------------------------------------------------------------------------
//! imguiの処理
//---------------------------------------------------------------------------
void Player::ImGui()
{
	OpenAndCloseImGui();

	//! プレイヤーの情報をimguiで変更
	if (isImGui) {
		ImGui::Begin("Player");
		if (ImGui::TreeNode("Position")) { //!< プレイヤー座標の変更
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

		if (ImGui::TreeNode("Debug")) { //!< プレイヤーのデバッグ数値のON,OFF
			ImGui::Checkbox("isEnableDebug", &isEnableDebug);
			ImGui::TreePop();
		}
		ImGui::End();
	}
}

//---------------------------------------------------------------------------
//! 描画処理
//---------------------------------------------------------------------------
void Player::Draw()
{
	//! カプセルを形成する二点中の一点の座標
	VECTOR posUp = pos;
	posUp.y = pos.y + 14.0f;

	MV1DrawModel(modelHotaru);

	//! @retval true デバックを有効化	
	if (isEnableDebug) {
		DrawCapsule3D(pos, posUp, 3, 10, RED, RED, FALSE);
		DrawSphere3D(hitPos, hitSize, 20, RED, RED, FALSE);
		printfDx("総再生時間%.1f\n", totalTime);
		printfDx("再生時間%.1f\n", playTime);
		printfDx("PlayerX%f\n", pos.x);
		printfDx("PlayerY%f\n", pos.y);
		printfDx("PlayerZ%f\n", pos.z);
		printfDx("テクスチャ数%d\n", textureNum);
	}
}

//---------------------------------------------------------------------------
//! @param（pos） カメラの位置を設定
//---------------------------------------------------------------------------
void Player::setCameraPos(const VECTOR& pos) {
	cameraPos = pos;
}

//---------------------------------------------------------------------------
//! @param（rot） カメラの回転を設定
//---------------------------------------------------------------------------
void Player::setCameraRot(const VECTOR& rot) {
	cameraRot = rot;
}
