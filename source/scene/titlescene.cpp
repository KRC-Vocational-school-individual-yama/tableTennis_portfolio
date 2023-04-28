#include "titlescene.h"

#include<DxLib.h>
#include"../libs/frameWork/scenemanager.h"
#include"../object/titleobject.h"
#include"../object/params.h"

namespace { using namespace SceneManager; }

TitleScene::TitleScene(){
	//SetBackgroundColor(0xff,0xff,0x84);
	//SetBackgroundColor(0xe5, 0xff, 0xff);

	Create<TitleObject>();

	//コモンシーンにパラメーター管理を作る
	Scene* common = GetCommonScene();
	if( ! common->Invoke<Params>())
		common->Create<Params>();

	SetMouseDispFlag(TRUE);
}
TitleScene::~TitleScene(){
}