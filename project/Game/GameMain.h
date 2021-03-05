//---------------------------------------------------------------------------
//!	@file	GameMain.h
//!	@brief	GameMain
//---------------------------------------------------------------------------

#pragma once

enum class Scene {
	TITLE,
	GAME,
	CLEAR,
	RANKING,
};

class GameMain 
{
	public:
	void Initialize();
	void Update();
	void Draw();

	void Hit();
	void PlayerAttackHitEnemy(class EnemyBase* enemyBase);
	void PlayerHitGoal();

private:
	Scene scene;

	std::unique_ptr<class Player> player;
	std::unique_ptr<class CameraPlayer> cameraPlayer;
	std::unique_ptr<class EnemyManager> enemyManager;
	std::unique_ptr<class Map> map;
	std::unique_ptr<class Goal> goal;
	std::unique_ptr<class Score> score;
	std::unique_ptr<class SceneTitle>sceneTitle;
	std::unique_ptr<class SceneClear> sceneClear;
	std::unique_ptr<class Light>light;
	std::unique_ptr<class SceneRanking>sceneRanking;
	std::unique_ptr<class SlashingEffect>slashingEffect;
};

