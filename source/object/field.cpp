#include "field.h"
#include"params.h"
#include"../libs/frameWork/scene.h"
#include"ball.h"

namespace {
	/*体育館大きさについて
	
		天井の高さ　7m,10m,15m
		
		小学校　　　 25m*35m
		中学校　　　 33m*15m
		高校　　　　 35m*23m
		大学,一般　　37m*24m
	*/
	/*卓球台大きさについて
		274cm*152.5cm * 76cm
		縦　幅　高さ
		
		ネット高さ
		15.25cm
	*/

}

Field::Field(Scene* sc)
	:Object(sc)
	,transform()
	,size()
	,hModel(-1)
	,textureImgs()
	,wallHit(false)
	,tableHit(false)
{}

Field::~Field(){
	MV1DeleteModel(hModel);
}

void Field::Init(){
	transform.position = VGet(0, 0, 0);
	size = VGet(37, 15, 24);
	size.x *= (float)Params::METERS;
	size.y *= (float)Params::METERS;
	size.z *= (float)Params::METERS;

	hModel= MV1LoadModel("data/model/table tennis/Table tennis.mv1");
	assert(hModel > 0);
	float size = 20;
	MV1SetScale(hModel, VGet(size,size,size));
	MV1SetRotationMatrix(hModel, MGetRotY(DX_PI_F/180*90));
	//MV1SetTextureGraphHandle(hModel,0,textureImgs,TRUE);
}

void Field::Update(){

	//ボール当たり判定
	Ball* ball= GetScene()->Invoke<Ball>();
	if (ball) {
	//カベと当たり判定
		VECTOR wallPos = VGet(-Params::METERS * 2, 0, 1525.f);
		VECTOR wallSize = VGet(Params::METERS * 2, Params::METERS * 3, 200);
		if (ball->CollisionWall(wallPos, wallSize, VGet(0,0,-1))) {
			wallHit = true;
		}
	//テーブルとの当たり判定
		VECTOR tableSize = VGet(Params::METERS * 2, Params::METERS * 1.5f, Params::METERS * 5);
		VECTOR tablePos = VGet(-tableSize.x+200, 0, -tableSize.z / 2);
		if (ball->CollisionTable(tablePos, tableSize, VGet(0, -1, 0))) {
			tableHit = true;
		}
	}
	

}

void Field::Draw(){
	transform.MakeMatrix();
	//VERTEX3D ver=GetVertex3D(VGet(0,0,0),GetColorU8(0,0,0,0),0,0 );

	//体育館描画
	{
		float cameraNear = GetCameraNear();
		float cameraFar = GetCameraFar();
		SetCameraNearFar(cameraNear, 100000);
		VECTOR disp = VGet(1, 1, 1) * transform.matrix;
		DrawBox3D(disp, disp + size, 0x8b4513);
		SetCameraNearFar(cameraNear, cameraFar);
	}

	//卓球台描画
	VECTOR dispPos = VGet(0,0,0);
	VECTOR dispSize = VGet(2.74f,0.76f,1.525f)*VGet(Params::METERS, Params::METERS, Params::METERS);
	DrawBox3D(dispPos,dispPos+ dispSize, 0x006400);
	for(int i=0;i<10;i++)
	DrawBox3D(dispPos+VGet(i,i,i), dispPos + dispSize+VGet(i,i,i), 0x006400);

	MV1DrawModel(hModel);

#ifdef _DEBUG
	//カベ
	VECTOR wallPos = VGet(200,0, 1525.f);
	VECTOR wallSize = VGet(-Params::METERS * 2,Params::METERS*3,200);
	unsigned int wallColor = 0xffffff;
	if (wallHit) {
		wallColor = 0xe50000;
		wallHit = false;
	}
	DrawBox3D(wallPos,wallPos+wallSize,wallColor);

	//テーブル
	VECTOR tableSize= VGet(Params::METERS*2,Params::METERS*1.5f,Params::METERS*5);
	VECTOR tablePos = VGet(-tableSize.x + 200, 0, -tableSize.z / 2);
	unsigned int tableColor = 0xffffff;
	if (tableHit) {
		tableColor = 0xe50000;
		tableHit = false;
	}
	DrawBox3D(tablePos,tablePos+ tableSize, tableColor);

#endif
}

