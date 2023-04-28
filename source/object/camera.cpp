#include "camera.h"
#include"params.h"

Camera::Camera(Scene* sc)
	:Object(sc)
	,position()
	,target()
{}

Camera::~Camera(){

}

void Camera::Init(){
	VECTOR position = VGet(-800.f, 2800.f, -4500.f);
	VECTOR target = VGet(-800, 1800.f, -1500.f);

	SetPos(position);
	SetTar(target);
}

void Camera::Update(){
	

}

void Camera::Draw(){

	SetCameraPositionAndTarget_UpVecY(position, target);

}
