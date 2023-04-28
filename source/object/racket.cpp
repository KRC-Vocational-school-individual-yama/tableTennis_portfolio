#include "racket.h"
#include"../libs/frameWork/scene.h"
#include"camera.h"

namespace {
	char pass[] = "data/model/Racket/racket_.mv1";
}

Racket::Racket(Scene* sc)
	:Object(sc)
	,hModel(-1)
	,mouse3D()
{}

Racket::~Racket(){
	MV1DeleteModel(hModel);
}

void Racket::Init(){
	hModel = MV1LoadModel(pass);
	assert(hModel > 0);

	//大きさ
	float size = 20;
	MV1SetScale(hModel, VGet(size, size, size));
	MV1SetRotationMatrix(hModel, MGetRotY(DX_PI_F / 180 * 90));

	//場所
	VECTOR position = VGet(-800.f, 1500.f, -1800.f);
	MV1SetPosition(hModel,position);


}

void Racket::Update(){
	//マウス座標を取得
	Vec2 mouse = {};
	GetMousePoint(&mouse.x,&mouse.y);
	mouse3D= ConvScreenPosToWorldPos(VGet(mouse.x,mouse.y,1.f));

	//カメラ座標を獲てマウス座標を加工
	Camera* cam = GetScene()->Invoke<Camera>();
	if (cam) {
		VECTOR camPos= cam->GetPos();
		mouse3D += camPos;
		VECTOR norm= VNorm(mouse3D);
		VECTOR reSize= VScale(norm, 200);
		mouse3D= camPos + reSize;
	}

	//mouse3D -= VGet(0,0,12000);
	//mouse3D.y = 2000.f;

	printfDx("x= %f\n",mouse3D.x);
	printfDx("y= %f\n",mouse3D.y);
	printfDx("z= %f\n",mouse3D.z);

}

void Racket::Draw(){
	MV1DrawModel(hModel);
	VECTOR halfSize = VGet(10,10,1);
	DrawCube3D(mouse3D-halfSize,mouse3D+halfSize,0xffffff,0xffffff,true);
	DrawSphere3D(mouse3D, 20, 21, 0xffffff, 0xffffff, true);
}
