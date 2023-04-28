#include "gamescene.h"

#include<DxLib.h>
#include"../libs/frameWork/scenemanager.h"
#include"../object/gameSceneObject.h"
#include"../object/skybox.h"
#include"../object/camera.h"
#include"../object/camera/freeCamera.h"
#include"../object/axis.h"

#include"../object/table.h"
#include"../object/ball.h"
#include"../object/racket.h"
#include"../object/enemyPlayer.h"


GameScene::GameScene(){
	//SetBackgroundColor(0xe5,0xff,0xff);

	Create<Skybox>("skyBox");
	Create<Camera>("camera");

	Create<Table>("table");		//
	Create<EnemyPlayer>("enemyPlayer");//相手
	Create<Ball>("Ball");		//
	Create<Racket>("Racket");	//ラケット(自分
	/*
	背景（青空
	背景（体育館
	カメラ

	ラケット（マウス
	ボール
	相手（壁

	*/

#ifdef _DEBUG
	Create<Axis>("axis");
	Create<GameSceneObject>("gameSceneObject");
#endif
}

GameScene::~GameScene(){
}

//ToDo:後で消す
//------------------------------------------------------------------

namespace { 
	bool keystop = true;

	void BackScene() {
		bool backKey = CheckHitKey(KEY_INPUT_ESCAPE);
		bool keyDown = backKey && !keystop;
		keystop = backKey;

		if (keyDown) {
			SceneManager::SceneChange("Title");
		}

	}
}
void GameScene::Update(){
	Scene::Update();

	BackScene(); 
}
void GameScene::Draw() {
	Scene::Draw();

	
#ifdef _DEBUG 
	DrawFormatString(100,100,0x0,"GameScene\nEscapeで戻る");
#endif

}