//---------------------------------------------------------------------------
//!	@file	SceneRanking.cpp
//!	@brief	ランキングシーン
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
SceneRanking::SceneRanking()
{
	fontSize = CreateFontToHandle(NULL, 100, 3);
	rankingFontSize = CreateFontToHandle(NULL, 150, 3);
	clearRankFontSize = CreateFontToHandle(NULL, 80, 3);
	NumericsInitialize();
}

//---------------------------------------------------------------------------
//! 初期化処理
//---------------------------------------------------------------------------
void SceneRanking::Initialize()
{
	rankingScreen = LoadGraph("data/scene/rankingScreen.png");

	for (int i = 0; i < ranking.size(); i++) {
		ranking[i] = 0;
	}

	//テキストファイルをを開ける
	std::ifstream file("ranking.txt");
	if (file.is_open()) {
		std::string buffer;
		//ファイルから1行とってくる
		for (int i = 0; i < ranking.size(); i++) {
			getline(file, buffer);
			ranking[i] = std::atoi(buffer.c_str());
		}
		file.close();
	}
}

//---------------------------------------------------------------------------
//! 数値の初期化処理
//---------------------------------------------------------------------------
void SceneRanking::NumericsInitialize()
{
	blinkTimer = 0;
	count = 0;
	rankingOpacity = 0;
	firstOpacity = 0;
	secondOpacity = 0;
	thirdOpacity = 0;
	sceneClearOpacity = 0;
	now = 0;
	once = true;
	isTitle = false;
}

//---------------------------------------------------------------------------
//! 更新処理
//---------------------------------------------------------------------------
void SceneRanking::Update()
{
	//! 1回だけ通す
	if (once) {
		now = score_;
		once = false;
	}

	//! ランキングの整理
	for (int i = 0; i < ranking.size(); ++i) {
		//! 順位の見比べ
		if (now < ranking[i]) continue;

		int tmp = ranking[i];
		ranking[i] = now;
		now = tmp;
	}

	Save();
}

//---------------------------------------------------------------------------
//! 透明度の処理
//---------------------------------------------------------------------------
void SceneRanking::DrawUpdate()
{
	int graduallyAdd = 3; //!< 徐々に不透明度の加算

	//! 徐々に透明度を下げる
	rankingOpacity += graduallyAdd + 1;
	if (rankingOpacity == MAX_OPACITY) rankingOpacity = MAX_OPACITY;

	//! RANKINGが描画されたら3位を徐々に描画
	if (rankingOpacity > MAX_OPACITY) {
		thirdOpacity += graduallyAdd;
	}
	//! 3位が描画されたら2位を徐々に描画
	if (thirdOpacity > MAX_OPACITY) {
		secondOpacity += graduallyAdd;
	}
	//! 2位が描画されたら1位を徐々に描画
	if (secondOpacity > MAX_OPACITY) {
		firstOpacity += graduallyAdd;
	}
	//! 数値が描画されてからカウント開始
	if (firstOpacity > MAX_OPACITY) count++;

	if (count == 240) count = 0;

	//! 全てのランキングが描画されるまで、キーを押してもタイトルに戻らない
	if (firstOpacity > MAX_OPACITY && IsKeyOn(KEY_INPUT_SPACE)) {
		//! 決定のSE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		isTitle = true;
	} 
	else if (firstOpacity > MAX_OPACITY && IsPadOn(PAD_B)) {
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		isTitle = true;
	}

	//! 押すとすぐに1位～3位と数値を描画する
	if (IsKeyOn(KEY_INPUT_SPACE) || IsPadOn(PAD_B)) {
		rankingOpacity = MAX_OPACITY;
		thirdOpacity = MAX_OPACITY;
		secondOpacity = MAX_OPACITY;
		firstOpacity = MAX_OPACITY;
	}
}

//---------------------------------------------------------------------------
//! 描画処理
//---------------------------------------------------------------------------
void SceneRanking::Draw()
{
	DrawRanKing();

	//! 1位6の透明度が0になったら点滅して描画
	if (count > 0 && count < 180 && firstOpacity > 255) {
		//! Bボタンで戻るを描画
		DrawStringToHandle(200, 950, "Back in PadB or SPACE", BLACK, fontSize);
	}
}

//---------------------------------------------------------------------------
//! SceneClearで表示するランキング
//---------------------------------------------------------------------------
void SceneRanking::SceneClearRank(SceneClear* sceneClear)
{
	std::string text;
	std::string name;

	if (sceneClear->getIsOpacity()) sceneClearOpacity += 2;

	//! ファイルから読み込んで描画
	for (int i = 0, j = 1; i < ranking.size(), j <= ranking.size(); i++, j++) {

		text = "No.";
		text += std::to_string(j);
		text += ": ";
		text += std::to_string(ranking[i]);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, sceneClearOpacity);
		DrawStringToHandle(750, 550 + (100 * i), text.c_str(), WHITE, clearRankFontSize);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);
	}
	
}

//---------------------------------------------------------------------------
//! ランキングの描画
//---------------------------------------------------------------------------
void SceneRanking::DrawRanKing()
{
	int x = 0; //!< 背景のX座標
	int y = 0; //!< 背景のY座標
	//! 背景の描画
	DrawGraph(x, y, rankingScreen, false);

	int rankTextX = 540; //!< 〓RANKING〓のX座標
	int rankTextY = 70;  //!< 〓RANKING〓のY座標

	//! ランキング
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, rankingOpacity);
	DrawStringToHandle(rankTextX, rankTextY, "〓RANKING〓", WHITE, rankingFontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	int rankX = 570; //!< ランクのX座標
	int rankY = 310; //!< ランクのY座標

	//! 1位
	char firstPlace[256];
	sprintf_s(firstPlace, "%d", ranking[0]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, firstOpacity);
	DrawStringToHandle(rankX, rankY, "1st place", GOLD, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 0), firstPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! 2位
	char secondPlace[256];
	sprintf_s(secondPlace, "%d", ranking[1]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, secondOpacity);
	DrawStringToHandle(rankX, rankY + 220, "2nd place", SILVER, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 1), secondPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! 3位
	char thirdPlace[256];
	sprintf_s(thirdPlace, "%d", ranking[2]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, thirdOpacity);
	DrawStringToHandle(rankX, rankY + 440, "3rd place", COPPER, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 2), thirdPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);
}

//---------------------------------------------------------------------------
//! セーブ処理
//---------------------------------------------------------------------------
void SceneRanking::Save()
{
	//セーブ
	std::ofstream file("ranking.txt");

	file << ranking[0] << std::endl;
	file << ranking[1] << std::endl;
	file << ranking[2] << std::endl;

	file.close();
}

//---------------------------------------------------------------------------
//! @param（score_） Scoreクラスのスコアを設定
//---------------------------------------------------------------------------
void  SceneRanking::setScore(int scroe) {
	score_ = scroe;
}