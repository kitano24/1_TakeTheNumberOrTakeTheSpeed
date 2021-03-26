//---------------------------------------------------------------------------
//!	@file	GameMain.cpp
//!	@brief	GameMain
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
void GameMain::Initialize()
{	
	//! 最初のシーンをタイトルにする
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
    //!	@name	初期化
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
//! 更新処理
//---------------------------------------------------------------------------
void GameMain::Update()
{
	switch (scene)
	{
     //=============================================================
     //! タイトルシーン
	 //=============================================================
	case Scene::TITLE:
		sceneTitle->Update();

		//! @retval true ゲームスタート
		if (sceneTitle->getIsMainGame()) {
			scene = Scene::GAME;
		}

		//! @retval true ランキング
		if (sceneTitle->getIsRanking()) {
			scene = Scene::RANKING;
		}

		break;

     //=============================================================
     //! メインゲームシーン
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

		//! @retval true ゲームクリア
		if (goal->getIsHit()) {
			scene = Scene::CLEAR;
		}

		break;

	//=============================================================
	//! ランキングシーン
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
	//! クリアシーン
	//=============================================================
	case Scene::CLEAR:
		sceneClear->Update();
		//! @details　クリアシーンは絶対通るので、ランキングのアップデートをここで呼ぶ
		sceneRanking->Update();
		//! @retval true タイトルに戻り、数値が変わったオブジェクトを初期化
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
//! 描画処理
//---------------------------------------------------------------------------
void GameMain::Draw()
{
	switch (scene)
	{
	//=============================================================
	//! タイトルシーン
	//=============================================================
	case Scene::TITLE:
		sceneTitle->Draw();
		break;

	//=============================================================
	//! メインゲームシーン
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
	//! ランキングシーン
	//=============================================================
	case Scene::RANKING:
		sceneRanking->Draw();
		break;

	//=============================================================
	//! クリアシーン
	//=============================================================
	case Scene::CLEAR:
		sceneClear->Draw();
		sceneRanking->SceneClearRank(sceneClear.get());
		break;
	}
}

//---------------------------------------------------------------------------
//! 当たり判定
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
//! 敵とプレイヤーの攻撃の当たり判定
//---------------------------------------------------------------------------
void GameMain::PlayerAttackHitEnemy(EnemyBase* enemyBase)
{
	//! エネミーとプレイヤーの当たり判定の半径
	float enemyR = 5.0f, playerR = player->getHitSize();

	int enemyScore = 1000;

	//! @details　球の中心点の座標からの距離と2つの球の半径で比べる
	//! @details　平方根の計算は処理が重いので2乗のまま扱う
	if (VSquareSize(VSub(player->getPos(), enemyBase->getPos()))
		<= (playerR + enemyR) * (playerR + enemyR) && !enemyBase->getIsAttackHit()) {

		//! 当たっている状態で攻撃ボタンを押したら
		if (IsKeyOn(KEY_INPUT_R) || IsPadOn(PAD_X)) {
			//! @retval true 攻撃が当たった 
			enemyBase->setIsAttackHit(true);
		
			//! エフェクトの位置を倒された敵の位置にする
			slashingEffect->setEffectPos(enemyBase->getPos());

			//! スコアを+1000する
			score->setEnemyScore(enemyScore);
			//! カウントを+1する
			enemyManager->addEnemyCount();
		}
	}
}

//---------------------------------------------------------------------------
//! プレイヤーとゴールの当たり判定
//---------------------------------------------------------------------------
void GameMain::PlayerHitGoal()
{
	float goalR = goal->getHitSize(), playerR = player->getHitSize();

	if (VSquareSize(VSub(player->getPos(), goal->getPos()))
		<= (playerR + goalR) * (playerR + goalR) && goal->getIsAppearing()) {
		goal->setIsHit(true);
	}
}

