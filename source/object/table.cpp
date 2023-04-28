#include "table.h"
#include"params.h"

namespace {
	char pass[] = "data/model/table tennis/Table tennis.mv1";
	char passCube[] = "data/model/cube/cube.mv1";
}

Table::Table(Scene* sc)
	:Object(sc)
	,hModel(-1)
	,hCube(-1)
	,transform()
{}

Table::~Table(){
	MV1DeleteModel(hModel);
	MV1DeleteModel(hCube);

}

void Table::Init(){
	hModel = MV1LoadModel(pass);
	assert(hModel > 0);
	hCube = MV1LoadModel(passCube);
	assert(hCube > 0);

	float size = 20;
	MV1SetScale(hModel, VGet(size, size, size));
	MV1SetRotationMatrix(hModel, MGetRotY(DX_PI_F / 180 * 90));


	//MV1SetPosition(hCube,VGet(-800, 2000.f,0));
	MV1SetScale(hCube, VGet(7,7,7));


}

void Table::Update(){

}

void Table::Draw(){
	transform.MakeMatrix();

	MV1DrawModel(hCube);

	////‘ì‹…‘ä•`‰æ
	MV1DrawModel(hModel);


}
