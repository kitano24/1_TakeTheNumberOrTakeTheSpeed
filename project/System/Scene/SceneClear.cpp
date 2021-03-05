//---------------------------------------------------------------------------
//!	@file	SceneClear.cpp
//!	@brief	クリアシーン
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
SceneClear::SceneClear()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! デストラクター
//---------------------------------------------------------------------------
SceneClear::~SceneClear()
{

}

//---------------------------------------------------------------------------
//! 初期化処理
//---------------------------------------------------------------------------
void SceneClear::Initialize()
{
	clearScreen = LoadGraph("data/scene/ClearScreen.png");
	isTitle = false;
	isOpacity = false;
	score = 0;
	dispScore = 0;
	count = 0;
	fontSize = CreateFontToHandle(NULL, 100, 3, DX_FONTTYPE_NORMAL);
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void SceneClear::Update()
{
	//! 自分のスコアが表示されるまでキーを押してもタイトルに戻らない
	if (dispScore >= score && IsKeyOn(KEY_INPUT_SPACE)) {
		//! @retval true タイトルへ戻る
		isTitle = true; 
	}
	else if (dispScore >= score && IsPadOn(PAD_B)) {
		isTitle = true;
	}

	if (dispScore < score) {
		dispScore += 100;
		//! 点数の加算時の効果音
		PlaySoundFile("data/sound/score.wav", DX_PLAYTYPE_BACK);
	}

	//! 自分のスコアをすぐに描画
	if (IsKeyOn(KEY_INPUT_SPACE) || IsPadOn(PAD_B)) {
		dispScore = score;
	}

	if (dispScore >= score) {
		dispScore = score;
		isOpacity = true;
		//! スコアが表示されたら止める
		StopSound();
	}

	count++;
	if (count == 120) count = 0;
}

//---------------------------------------------------------------------------
//! 描画処理
//---------------------------------------------------------------------------
void SceneClear::Draw()
{
	int x = 0;
	int y = 0;
	DrawGraph(x, y, clearScreen, false);

	DrawStringToHandle(550, 400, "Your score ", WHITE, fontSize);
	char text[256];
	sprintf_s(text, "%d", dispScore);
	DrawStringToHandle(1090, 400, text, SKYBLUE, fontSize);

	//! Bボタンで戻る
	if (count > 0 && count < 60 && isOpacity) {
		DrawStringToHandle(200, 900, "Push PadB or SPACE", WHITE, fontSize);
	}
}

//---------------------------------------------------------------------------
//! @param（score_） Scoreクラスのスコアを設定
//---------------------------------------------------------------------------
void  SceneClear::setScore(int scroe_) 
{
	score = scroe_;
}