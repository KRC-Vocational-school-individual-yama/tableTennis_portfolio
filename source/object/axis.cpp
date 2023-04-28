#include "axis.h"

Axis::Axis(Scene* sc)
	:Object(sc)
{
}

Axis::~Axis()
{
}

void Axis::Init()
{
}

void Axis::Update()
{
}

void Axis::Draw(){
#ifdef _DEBUG

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255/3);

	//画面に張り付くタイプ
	float lenght = 15;
	VECTOR disp = ConvScreenPosToWorldPos(VGet(100, SCREEN_HEIGHT - 100, 0.5f));
	DrawLine3D(disp, VAdd(disp, VGet(lenght, 0, 0)), 0xff5555);
	DrawLine3D(disp, VAdd(disp, VGet(0, lenght, 0)), 0x55ff55);
	DrawLine3D(disp, VAdd(disp, VGet(0, 0, lenght)), 0x5555ff);
	disp = VGet(0,0,0);
	lenght = 5000;
	DrawLine3D(disp, VAdd(disp, VGet(lenght, 0, 0)), 0xff5555);
	DrawLine3D(disp, VAdd(disp, VGet(0, lenght, 0)), 0x55ff55);
	DrawLine3D(disp, VAdd(disp, VGet(0, 0, lenght)), 0x5555ff);


	//その場にいるタイプ
	for (int i = 0; i < 100; i++) {
		//x
		int xColor = 0xff90ff;//赤
		DrawLine3D(VGet(i*500,0,-1000),VGet(i*500,0,1000),xColor);
		DrawLine3D(VGet(i*500,-1000,0),VGet(i*500,1000,0),xColor);
		DrawLine3D(VGet(i*-500,0,-1000),VGet(i*-500,0,1000),xColor);
		DrawLine3D(VGet(i*-500,-1000,0),VGet(i*-500,1000,0),xColor);


		//y
		int yColor = 0xffff90;//黄色
		DrawLine3D(VGet(-1000,i*500,0),VGet(1000,i*500,0),yColor);
		DrawLine3D(VGet(-1000,i*-500,0),VGet(1000,i*-500,0),yColor);
		
		//z
		int zColor = 0x90ffff;//青
		DrawLine3D(VGet(-1000,0,i*500),VGet(1000,0,i*500),zColor);
		DrawLine3D(VGet(0,-1000,i*500),VGet(0,1000,i*500),zColor);
		DrawLine3D(VGet(-1000,0,i*-500),VGet(1000,0,i*-500),zColor);
		DrawLine3D(VGet(0,-1000,i*-500),VGet(0,1000,i*-500),zColor);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#endif
}
