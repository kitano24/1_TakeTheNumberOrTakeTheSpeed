//---------------------------------------------------------------------------
//!	@file	SceneTitle.cpp
//!	@brief	タイトルシーン
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
SceneTitle::SceneTitle()
{
	fontSize = CreateFontToHandle(NULL, 100, 3, DX_FONTTYPE_NORMAL);;
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
	y1 = 580;
	x2 = 1380;
	y2 = 700;
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
	if (y1 == 580 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 580 && IsPadOn(PAD_B)) {
		//! 決定のSE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		//! @retval true ゲームスタート
		isMainGame = true;
	}
	else {
		isMainGame = false;
	}

	//! ランキングの位置
	if (y1 == 780 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 780 && IsPadOn(PAD_B)) {
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
	if (y1 == 580 && IsKeyOn(KEY_INPUT_DOWN) || IsPadOn(PAD_DOWN)) {
		y1 = 780;
		y2 = 900;
		//! 選択しているときのSE
		PlaySoundFile("data/sound/option.wav", DX_PLAYTYPE_BACK);
	}

	//! 印がゲームスタートの位置へ移動
	if (y1 == 780 && IsKeyOn(KEY_INPUT_UP) || IsPadOn(PAD_UP)) {
		y1 = 580;
		y2 = 700;
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
	if (y1 == 580) {
		DrawStringToHandle(710, 590, "GAME START", YELLOW, fontSize);
	}
	else {
		//! 選択されていなければ文字を黒くする
		DrawStringToHandle(710, 590, "GAME START", BLACK, fontSize);
	}

	//! ランキングを選択中
	if (y1 == 780) {
		DrawStringToHandle(780, 790, "RANKING", YELLOW, fontSize);
	}
	else {
		//! 選択されていなければ文字を黒くする
		DrawStringToHandle(780, 790, "RANKING", BLACK, fontSize);
	}
}
