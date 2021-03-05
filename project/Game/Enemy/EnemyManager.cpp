//---------------------------------------------------------------------------
//!	@file	EnemyManager.cpp
//!	@brief	エネミー全体の管理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクター
//---------------------------------------------------------------------------
EnemyManager::EnemyManager()
{
	//! push_backで配列を作成
	for (int i = 0; i < enemyMax; i++) {
		enemys.push_back(new Enemy());
	}

	fontSize = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_NORMAL);
	countFontSize = CreateFontToHandle(NULL, 70, 3, DX_FONTTYPE_NORMAL);
}

//---------------------------------------------------------------------------
//! デストラクター
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
//! 初期化
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
//! 更新処理
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
//! 描画処理
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

	DrawStringToHandle(10, 330, "敵を倒した数", RED, fontSize);
	char enemyCount_[256];
	sprintf_s(enemyCount_, "%d", enemyCount);
	DrawFormatStringToHandle(enemyCountX, enemyCountY, BLACK, countFontSize, enemyCount_);
}
