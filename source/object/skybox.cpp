#include "skybox.h"

#include"../libs/frameWork/scene.h"
#include"camera.h"
#include"camera/freeCamera.h"

Skybox::Skybox(Scene* sc)
	:Object(sc)
	,hModel{-1}
{}

Skybox::~Skybox(){
	MV1DeleteModel(hModel);
}

void Skybox::Init(){
	hModel = MV1LoadModel("data/model/yukawa_original/Sky_Sunny.mv1");
	assert(hModel > 0);

}

void Skybox::Update(){
	auto camera=GetScene()->Invoke<Camera>();
	if (camera) {
		VECTOR pos = camera->GetPos();
		MV1SetPosition(hModel, pos);
	}
	auto freeCamera=GetScene()->Invoke<FreeCamera>();
	if (freeCamera) {
		VECTOR pos = freeCamera->GetPos();
		MV1SetPosition(hModel, pos);
	}
}

void Skybox::Draw(){

	//float nowNear=GetCameraNear();
	//float nowFar= GetCameraFar();
	//SetCameraNearFar(1000,1000);
	MV1DrawModel(hModel);

	//SetCameraNearFar(nowNear,nowFar);
}
