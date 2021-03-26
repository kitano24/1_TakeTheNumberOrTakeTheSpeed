//---------------------------------------------------------------------------
//!	@file	GameMain.cpp
//!	@brief	GameMain
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
void GameMain::Initialize()
{	
	//! �ŏ��̃V�[�����^�C�g���ɂ���
	scene = Scene::TITLE;

	//-------------------------------------------------------------
    //!	@name	new
    //-------------------------------------------------------------
	map = std::make_unique<class Map>();
	player = std::make_unique<class Player>();
	cameraPlayer = std::make_unique<class CameraPlayer>();
	goal = std::make_unique<class Goal>();
	score = std::make_unique<class Score>();
	sceneTitle = std::make_unique<class SceneTitle>();
	sceneRanking = std::make_unique<class SceneRanking>();;
	sceneClear = std::make_unique<class SceneClear>();
	light = std::make_unique<class Light>();
	enemyManager = std::make_unique<class EnemyManager>();
	slashingEffect = std::make_unique<class SlashingEffect>();

	//-------------------------------------------------------------
    //!	@name	������
    //-------------------------------------------------------------
	player->Initialize();
	cameraPlayer->Initialize();
	goal->Initialize();
	sceneRanking->Initialize();
	sceneRanking->NumericsInitialize();
	sceneTitle->Initialize();
	sceneClear->Initialize();
	if (enemyManager != nullptr) {
		enemyManager->Initialize();
	}
}

//---------------------------------------------------------------------------
//! �X�V����
//---------------------------------------------------------------------------
void GameMain::Update()
{
	switch (scene)
	{
     //=============================================================
     //! �^�C�g���V�[��
	 //=============================================================
	case Scene::TITLE:
		sceneTitle->Update();

		//! @retval true �Q�[���X�^�[�g
		if (sceneTitle->getIsMainGame()) {
			scene = Scene::GAME;
		}

		//! @retval true �����L���O
		if (sceneTitle->getIsRanking()) {
			scene = Scene::RANKING;
		}

		break;

     //=============================================================
     //! ���C���Q�[���V�[��
     //=============================================================
	case Scene::GAME:
		player->Update();
		goal->Update();
		cameraPlayer->Update();
		cameraPlayer->Move(player.get());
		player->setCameraPos(cameraPlayer->getPos());
		player->setCameraRot(cameraPlayer->getRot());
		PlayerHitGoal();
		map->Update();
		slashingEffect->Update();
		if (enemyManager != nullptr) {
			enemyManager->Update();
		}
		
		score->Update();
		light->Update();

		Hit();

		//! @retval true �Q�[���N���A
		if (goal->getIsHit()) {
			scene = Scene::CLEAR;
		}

		break;

	//=============================================================
	//! �����L���O�V�[��
	//=============================================================
	case Scene::RANKING:
		sceneRanking->DrawUpdate();
		if (sceneRanking->getIsTitle()) {
			sceneRanking->Initialize();
			sceneRanking->NumericsInitialize();
			scene = Scene::TITLE;
		}
		break;

	//=============================================================
	//! �N���A�V�[��
	//=============================================================
	case Scene::CLEAR:
		sceneClear->Update();
		//! @details�@�N���A�V�[���͐�Βʂ�̂ŁA�����L���O�̃A�b�v�f�[�g�������ŌĂ�
		sceneRanking->Update();
		//! @retval true �^�C�g���ɖ߂�A���l���ς�����I�u�W�F�N�g��������
		if (sceneClear->getIsisTitle()) {
			goal->Initialize();
			cameraPlayer->Initialize();
			player->Initialize();
			map->Initialize();
			enemyManager->Initialize();
			sceneRanking->NumericsInitialize();
			sceneClear->Initialize();
			score->Initialize();
			light->Initialize();
			scene = Scene::TITLE;
		}
		break;
	}

	sceneClear->setScore(score->getScore());
	sceneRanking->setScore(score->getScore());
}
 
//---------------------------------------------------------------------------
//! �`�揈��
//---------------------------------------------------------------------------
void GameMain::Draw()
{
	switch (scene)
	{
	//=============================================================
	//! �^�C�g���V�[��
	//=============================================================
	case Scene::TITLE:
		sceneTitle->Draw();
		break;

	//=============================================================
	//! ���C���Q�[���V�[��
	//=============================================================
	case Scene::GAME:
		map->Draw();
		player->Draw();
		cameraPlayer->Draw();
		light->Draw();
		slashingEffect->Draw();
		if (enemyManager != nullptr) {
			enemyManager->Draw();
		}
		goal->Draw();

		break;

	//=============================================================
	//! �����L���O�V�[��
	//=============================================================
	case Scene::RANKING:
		sceneRanking->Draw();
		break;

	//=============================================================
	//! �N���A�V�[��
	//=============================================================
	case Scene::CLEAR:
		sceneClear->Draw();
		sceneRanking->SceneClearRank(sceneClear.get());
		break;
	}
}

//---------------------------------------------------------------------------
//! �����蔻��
//---------------------------------------------------------------------------
void GameMain::Hit()
{
	if (enemyManager != nullptr) {
		for (int i = 0; i < enemyManager->getEnemyMax(); i++) {
			if (player != nullptr) {
				PlayerAttackHitEnemy(enemyManager->getEnemy(i));
			}
		}
	}
}

//---------------------------------------------------------------------------
//! �G�ƃv���C���[�̍U���̓����蔻��
//---------------------------------------------------------------------------
void GameMain::PlayerAttackHitEnemy(EnemyBase* enemyBase)
{
	//! �G�l�~�[�ƃv���C���[�̓����蔻��̔��a
	float enemyR = 5.0f, playerR = player->getHitSize();

	int enemyScore = 1000;

	//! @details�@���̒��S�_�̍��W����̋�����2�̋��̔��a�Ŕ�ׂ�
	//! @details�@�������̌v�Z�͏������d���̂�2��̂܂܈���
	if (VSquareSize(VSub(player->getPos(), enemyBase->getPos()))
		<= (playerR + enemyR) * (playerR + enemyR) && !enemyBase->getIsAttackHit()) {

		//! �������Ă����ԂōU���{�^������������
		if (IsKeyOn(KEY_INPUT_R) || IsPadOn(PAD_X)) {
			//! @retval true �U������������ 
			enemyBase->setIsAttackHit(true);
		
			//! �G�t�F�N�g�̈ʒu��|���ꂽ�G�̈ʒu�ɂ���
			slashingEffect->setEffectPos(enemyBase->getPos());

			//! �X�R�A��+1000����
			score->setEnemyScore(enemyScore);
			//! �J�E���g��+1����
			enemyManager->addEnemyCount();
		}
	}
}

//---------------------------------------------------------------------------
//! �v���C���[�ƃS�[���̓����蔻��
//---------------------------------------------------------------------------
void GameMain::PlayerHitGoal()
{
	float goalR = goal->getHitSize(), playerR = player->getHitSize();

	if (VSquareSize(VSub(player->getPos(), goal->getPos()))
		<= (playerR + goalR) * (playerR + goalR) && goal->getIsAppearing()) {
		goal->setIsHit(true);
	}
}

