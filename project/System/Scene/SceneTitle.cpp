//---------------------------------------------------------------------------
//!	@file	SceneTitle.cpp
//!	@brief	タイトルシーン
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
SceneTitle::SceneTitle()
{
	fontSize = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_NORMAL);;
	Initialize();
}

//---------------------------------------------------------------------------
//! デストラクター
//---------------------------------------------------------------------------
SceneTitle::~SceneTitle()
{
}

//---------------------------------------------------------------------------
//! 初期化処理
//---------------------------------------------------------------------------
void SceneTitle::Initialize()
{
	titletScreen = LoadGraph("data/scene/titletScreen.png");
	x1 = 540;
	y1 = 570;
	x2 = 1380;
	y2 = 690;
	isMainGame = false;
	isRanking = false;
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void SceneTitle::Update()
{
	Move();

	//! ゲームスタートの位置
	if (y1 == 570 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 570 && IsPadOn(PAD_B)) {
		//! 決定のSE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		//! @retval true ゲームスタート
		isMainGame = true;
	}
	else {
		isMainGame = false;
	}

	//! ランキングの位置
	if (y1 == 770 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 770 && IsPadOn(PAD_B)) {
		//! 決定のSE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		//! @retval true ランキングシーンへ移動
		isRanking = true;
	}
	else {
		isRanking = false;
	}
}

//---------------------------------------------------------------------------
//! 印の移動処理
//---------------------------------------------------------------------------
void SceneTitle::Move()
{
	//! 印がランキングの位置へ移動
	if (y1 == 570 && IsKeyOn(KEY_INPUT_DOWN) || IsPadOn(PAD_DOWN)) {
		y1 = 770;
		y2 = 890;
		//! 選択しているときのSE
		PlaySoundFile("data/sound/option.wav", DX_PLAYTYPE_BACK);
	}

	//! 印がゲームスタートの位置へ移動
	if (y1 == 770 && IsKeyOn(KEY_INPUT_UP) || IsPadOn(PAD_UP)) {
		y1 = 570;
		y2 = 690;
		//! 選択しているときのSE
		PlaySoundFile("data/sound/option.wav", DX_PLAYTYPE_BACK);
	}
}

//---------------------------------------------------------------------------
//! 描画処理
//---------------------------------------------------------------------------
void SceneTitle::Draw()
{
	DrawGraph(0, 0, titletScreen, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(x1, y1, x2, y2, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! ゲームスタートを選択中
	if (y1 == 570) {
		DrawStringToHandle(750, 590, "GAME START", YELLOW, fontSize);
	}
	else {
		//! 選択されていなければ文字を黒くする
		DrawStringToHandle(750, 590, "GAME START", BLACK, fontSize);
	}

	//! ランキングを選択中
	if (y1 == 770) {
		DrawStringToHandle(820, 790, "RANKING", YELLOW, fontSize);
	}
	else {
		//! 選択されていなければ文字を黒くする
		DrawStringToHandle(820, 790, "RANKING", BLACK, fontSize);
	}
}
