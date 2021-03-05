//---------------------------------------------------------------------------
//!	@file	SceneClear.cpp
//!	@brief	�N���A�V�[��
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
SceneClear::SceneClear()
{
	Initialize();
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
SceneClear::~SceneClear()
{

}

//---------------------------------------------------------------------------
//! ����������
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
//! �X�V����
//---------------------------------------------------------------------------
void SceneClear::Update()
{
	//! �����̃X�R�A���\�������܂ŃL�[�������Ă��^�C�g���ɖ߂�Ȃ�
	if (dispScore >= score && IsKeyOn(KEY_INPUT_SPACE)) {
		//! @retval true �^�C�g���֖߂�
		isTitle = true; 
	}
	else if (dispScore >= score && IsPadOn(PAD_B)) {
		isTitle = true;
	}

	if (dispScore < score) {
		dispScore += 100;
		//! �_���̉��Z���̌��ʉ�
		PlaySoundFile("data/sound/score.wav", DX_PLAYTYPE_BACK);
	}

	//! �����̃X�R�A�������ɕ`��
	if (IsKeyOn(KEY_INPUT_SPACE) || IsPadOn(PAD_B)) {
		dispScore = score;
	}

	if (dispScore >= score) {
		dispScore = score;
		isOpacity = true;
		//! �X�R�A���\�����ꂽ��~�߂�
		StopSound();
	}

	count++;
	if (count == 120) count = 0;
}

//---------------------------------------------------------------------------
//! �`�揈��
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

	//! B�{�^���Ŗ߂�
	if (count > 0 && count < 60 && isOpacity) {
		DrawStringToHandle(200, 900, "Push PadB or SPACE", WHITE, fontSize);
	}
}

//---------------------------------------------------------------------------
//! @param�iscore_�j Score�N���X�̃X�R�A��ݒ�
//---------------------------------------------------------------------------
void  SceneClear::setScore(int scroe_) 
{
	score = scroe_;
}