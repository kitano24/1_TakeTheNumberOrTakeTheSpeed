//---------------------------------------------------------------------------
//!	@file	EnemyManager.cpp
//!	@brief	�G�l�~�[�S�̂̊Ǘ�
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^�[
//---------------------------------------------------------------------------
EnemyManager::EnemyManager()
{
	//! push_back�Ŕz����쐬
	for (int i = 0; i < enemyMax; i++) {
		enemys.push_back(new Enemy());
	}

	fontSize = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_NORMAL);
	countFontSize = CreateFontToHandle(NULL, 70, 3, DX_FONTTYPE_NORMAL);
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^�[
//---------------------------------------------------------------------------
EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemyMax; i++) {
		if (enemys[i] == nullptr) continue;
		delete enemys[i];
		enemys[i] = nullptr;

	}
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
void EnemyManager::Initialize()
{
	for (int i = 0; i < enemyMax; i++) {
		if (enemys[i] != nullptr) {
			enemys[i]->Initialize();
		}
	}

	enemyCount = 0;
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void EnemyManager::Update()
{
	for (int i = 0; i < enemyMax; i++) {
		if (enemys[i] != nullptr) {
			enemys[i]->Update();
		}
	}
}

//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void EnemyManager::Draw()
{
	for (int i = 0; i < enemyMax; i++) {
		if (enemys[i] != nullptr) {
			enemys[i]->Draw();
		}
	}

	int enemyCountX = 300;
	int enemyCountY = 320;

	DrawStringToHandle(10, 330, "�G��|������", RED, fontSize);
	char enemyCount_[256];
	sprintf_s(enemyCount_, "%d", enemyCount);
	DrawFormatStringToHandle(enemyCountX, enemyCountY, BLACK, countFontSize, enemyCount_);
}
