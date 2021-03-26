//---------------------------------------------------------------------------
//!	@file	SceneTitle.cpp
//!	@brief	�^�C�g���V�[��
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
SceneTitle::SceneTitle()
{
	fontSize = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_NORMAL);;
	Initialize();
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
SceneTitle::~SceneTitle()
{
}

//---------------------------------------------------------------------------
//! ����������
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
//! �X�V����
//---------------------------------------------------------------------------
void SceneTitle::Update()
{
	Move();

	//! �Q�[���X�^�[�g�̈ʒu
	if (y1 == 570 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 570 && IsPadOn(PAD_B)) {
		//! �����SE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		//! @retval true �Q�[���X�^�[�g
		isMainGame = true;
	}
	else {
		isMainGame = false;
	}

	//! �����L���O�̈ʒu
	if (y1 == 770 && IsKeyOn(KEY_INPUT_SPACE) || y1 == 770 && IsPadOn(PAD_B)) {
		//! �����SE
		PlaySoundFile("data/sound/decision.wav", DX_PLAYTYPE_BACK);
		//! @retval true �����L���O�V�[���ֈړ�
		isRanking = true;
	}
	else {
		isRanking = false;
	}
}

//---------------------------------------------------------------------------
//! ��̈ړ�����
//---------------------------------------------------------------------------
void SceneTitle::Move()
{
	//! �󂪃����L���O�̈ʒu�ֈړ�
	if (y1 == 570 && IsKeyOn(KEY_INPUT_DOWN) || IsPadOn(PAD_DOWN)) {
		y1 = 770;
		y2 = 890;
		//! �I�����Ă���Ƃ���SE
		PlaySoundFile("data/sound/option.wav", DX_PLAYTYPE_BACK);
	}

	//! �󂪃Q�[���X�^�[�g�̈ʒu�ֈړ�
	if (y1 == 770 && IsKeyOn(KEY_INPUT_UP) || IsPadOn(PAD_UP)) {
		y1 = 570;
		y2 = 690;
		//! �I�����Ă���Ƃ���SE
		PlaySoundFile("data/sound/option.wav", DX_PLAYTYPE_BACK);
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void SceneTitle::Draw()
{
	DrawGraph(0, 0, titletScreen, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(x1, y1, x2, y2, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_OPACITY);

	//! �Q�[���X�^�[�g��I��
	if (y1 == 570) {
		DrawStringToHandle(750, 590, "GAME START", YELLOW, fontSize);
	}
	else {
		//! �I������Ă��Ȃ���Ε�������������
		DrawStringToHandle(750, 590, "GAME START", BLACK, fontSize);
	}

	//! �����L���O��I��
	if (y1 == 770) {
		DrawStringToHandle(820, 790, "RANKING", YELLOW, fontSize);
	}
	else {
		//! �I������Ă��Ȃ���Ε�������������
		DrawStringToHandle(820, 790, "RANKING", BLACK, fontSize);
	}
}
