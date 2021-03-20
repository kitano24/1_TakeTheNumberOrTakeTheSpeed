//---------------------------------------------------------------------------
//!	@file	SceneRanking.cpp
//!	@brief	�����L���O�V�[��
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
SceneRanking::SceneRanking()
{
	fontSize = CreateFontToHandle(NULL, 100, 3);
	rankingFontSize = CreateFontToHandle(NULL, 150, 3);
	clearRankFontSize = CreateFontToHandle(NULL, 80, 3);
	NumericsInitialize();
}

//---------------------------------------------------------------------------
//! ����������
//---------------------------------------------------------------------------
void SceneRanking::Initialize()
{
	rankingScreen = LoadGraph("data/scene/rankingScreen.png");

	for (int i = 0; i < ranking.size(); i++) {
		ranking[i] = 0;
	}

	//�e�L�X�g�t�@�C�������J����
	std::ifstream file("ranking.txt");
	if (file.is_open()) {
		std::string buffer;
		//�t�@�C������1�s�Ƃ��Ă���
		for (int i = 0; i < ranking.size(); i++) {
			getline(file, buffer);
			ranking[i] = std::atoi(buffer.c_str());
		}
		file.close();
	}
}

//---------------------------------------------------------------------------
//! ���l�̏���������
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
//! �X�V����
//---------------------------------------------------------------------------
void SceneRanking::Update()
{
	//! 1�񂾂��ʂ�
	if (once) {
		now = score_;
		once = false;
	}

	//! �����L���O�̐���
	for (int i = 0; i < ranking.size(); ++i) {
		//! ���ʂ̌����
		if (now < ranking[i]) continue;

		int tmp = ranking[i];
		ranking[i] = now;
		now = tmp;
	}

	Save();
}

//---------------------------------------------------------------------------
//! �����x�̏���
//---------------------------------------------------------------------------
void SceneRanking::DrawUpdate()
{
	int graduallyAdd = 3; //!< ���X�ɕs�����x�̉��Z

	//! ���X�ɓ����x��������
	rankingOpacity += graduallyAdd + 1;
	if (rankingOpacity == MAX_OPACITY) rankingOpacity = MAX_OPACITY;

	//! RANKING���`�悳�ꂽ��3�ʂ����X�ɕ`��
	if (rankingOpacity > MAX_OPACITY) {
		thirdOpacity += graduallyAdd;
	}
	//! 3�ʂ��`�悳�ꂽ��2�ʂ����X�ɕ`��
	if (thirdOpacity > MAX_OPACITY) {
		secondOpacity += graduallyAdd;
	}
	//! 2�ʂ��`�悳�ꂽ��1�ʂ����X�ɕ`��
	if (secondOpacity > MAX_OPACITY) {
		firstOpacity += graduallyAdd;
	}
	//! ���l���`�悳��Ă���J�E���g�J�n
	if (firstOpacity > MAX_OPACITY) count++;

	if (count == 240) count = 0;

	//! �S�Ẵ����L���O���`�悳���܂ŁA�L�[�������Ă��^�C�g���ɖ߂�Ȃ�
	if (firstOpacity > MAX_OPACITY && IsKeyOn(KEY_INPUT_SPACE)) {
		//! �����SE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		isTitle = true;
	} 
	else if (firstOpacity > MAX_OPACITY && IsPadOn(PAD_B)) {
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		isTitle = true;
	}

	//! �����Ƃ�����1�ʁ`3�ʂƐ��l��`�悷��
	if (IsKeyOn(KEY_INPUT_SPACE) || IsPadOn(PAD_B)) {
		rankingOpacity = MAX_OPACITY;
		thirdOpacity = MAX_OPACITY;
		secondOpacity = MAX_OPACITY;
		firstOpacity = MAX_OPACITY;
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void SceneRanking::Draw()
{
	DrawRanKing();

	//! 1��6�̓����x��0�ɂȂ�����_�ł��ĕ`��
	if (count > 0 && count < 180 && firstOpacity > 255) {
		//! B�{�^���Ŗ߂��`��
		DrawStringToHandle(200, 950, "Back in PadB or SPACE", BLACK, fontSize);
	}
}

//---------------------------------------------------------------------------
//! SceneClear�ŕ\�����郉���L���O
//---------------------------------------------------------------------------
void SceneRanking::SceneClearRank(SceneClear* sceneClear)
{
	std::string text;
	std::string name;

	if (sceneClear->getIsOpacity()) sceneClearOpacity += 2;

	//! �t�@�C������ǂݍ���ŕ`��
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
//! �����L���O�̕`��
//---------------------------------------------------------------------------
void SceneRanking::DrawRanKing()
{
	int x = 0; //!< �w�i��X���W
	int y = 0; //!< �w�i��Y���W
	//! �w�i�̕`��
	DrawGraph(x, y, rankingScreen, false);

	int rankTextX = 540; //!< ��RANKING����X���W
	int rankTextY = 70;  //!< ��RANKING����Y���W

	//! �����L���O
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, rankingOpacity);
	DrawStringToHandle(rankTextX, rankTextY, "��RANKING��", WHITE, rankingFontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	int rankX = 570; //!< �����N��X���W
	int rankY = 310; //!< �����N��Y���W

	//! 1��
	char firstPlace[256];
	sprintf_s(firstPlace, "%d", ranking[0]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, firstOpacity);
	DrawStringToHandle(rankX, rankY, "1st place", GOLD, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 0), firstPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! 2��
	char secondPlace[256];
	sprintf_s(secondPlace, "%d", ranking[1]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, secondOpacity);
	DrawStringToHandle(rankX, rankY + 220, "2nd place", SILVER, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 1), secondPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! 3��
	char thirdPlace[256];
	sprintf_s(thirdPlace, "%d", ranking[2]);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, thirdOpacity);
	DrawStringToHandle(rankX, rankY + 440, "3rd place", COPPER, fontSize);
	DrawStringToHandle(WINDOW_W / 2 + 115, 315 + (220 * 2), thirdPlace, BLACK, fontSize);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);
}

//---------------------------------------------------------------------------
//! �Z�[�u����
//---------------------------------------------------------------------------
void SceneRanking::Save()
{
	//�Z�[�u
	std::ofstream file("ranking.txt");

	file << ranking[0] << std::endl;
	file << ranking[1] << std::endl;
	file << ranking[2] << std::endl;

	file.close();
}

//---------------------------------------------------------------------------
//! @param�iscore_�j Score�N���X�̃X�R�A��ݒ�
//---------------------------------------------------------------------------
void  SceneRanking::setScore(int scroe) {
	score_ = scroe;
}