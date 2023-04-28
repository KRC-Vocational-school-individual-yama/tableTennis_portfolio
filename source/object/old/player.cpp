#include "player.h"
#include"params.h"
#include"../libs/frameWork/scene.h"
#include"camera.h"
#include"ball.h"

Player::Player(Scene* sc)
	:Object(sc)
	,transform()
	,keys(nullptr)
	,radius()
	,height()
	,moveSpeed()
	,racketRad(0)
{}

Player::~Player(){
	delete keys;
}

void Player::Init(){
	keys = new KeyManager;
	transform.position = VGet(-800.f,0,-3000.f);
	height = Params::METERS* 1.8f;
	radius = 85.f / DX_TWO_PI_F ;//���� ���ϒj�� �~��/��*2 =���a
	radius *= Params::CENTI_METER;
	moveSpeed = Params::METERS * 0.5f;
	//racketRad = DegToRad(0);
	
	SetMouseDispFlag(FALSE);
	SetMousePoint(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
}

void Player::Update(){

	//���P�b�g�̏���
	
		Vec2 mouse = {};
		//static Vec2 oldMouse = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};//�����Ń}�E�X�̈ʒu���w�肷��ƃ��P�b�g�̏����ʒu�ɂȂ�
		static Vec2 oldMouse = {};//�����Ń}�E�X�̈ʒu���w�肷��ƃ��P�b�g�̏����ʒu�ɂȂ�
		GetMousePoint(&mouse.x, &mouse.y);
		static const int Mouse_Aim_Speed = 10;

		float oneFrameMove = mouse.x - oldMouse.x;
		if((int)oneFrameMove != 0){

			float send = DegToRad(oneFrameMove / Mouse_Aim_Speed);
			send += racketRad;

			if (DegToRad(-90) <= send && send <= DegToRad(90)) {
				racketRad = send;
			}
			oldMouse = mouse;

			//�J�[�\���ʒu�����ɖ߂�
			oldMouse = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
			SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}

	

	//�ړ�����
	{
		Vec2 moveVec = { 0,0 };
		if (keys->DownKeep(KEY_INPUT_W))
			moveVec.y += 1;
		if (keys->DownKeep(KEY_INPUT_S))
			moveVec.y += -1;
		if (keys->DownKeep(KEY_INPUT_A))
			moveVec.x += -1;
		if (keys->DownKeep(KEY_INPUT_D))
			moveVec.x += 1;

		if (0 != moveVec.x || 0 != moveVec.y) {
			float dir = atan2(moveVec.x, moveVec.y);
			transform.position += VGet(0, 0, moveSpeed) * MGetRotY(dir);

		}
	}

	//�J�����X�V
	{
		Camera* camera = GetScene()->Invoke<Camera>();
		if (camera) {

			VECTOR sendPos = transform.position + VGet(0, height, 0) + VGet(0, Params::METERS, Params::METERS * -3.f);
			VECTOR sendTar = transform.position + VGet(0, height, 0) + VGet(0, Params::METERS * 0, 0);
			camera->SetPos(sendPos);
			camera->SetTar(sendTar);
		}
	}

	//�{�[���ƃ��P�b�g�̓����蔻��

	if ((int)oneFrameMove != 0) {
		Ball* ball = GetScene()->Invoke<Ball>();
		if (ball) {
			VECTOR playerPos = transform.position;
			VECTOR playerSize = VGet(radius, height, radius);

			playerSize = VGet(Params::METERS * 2.f, height * 1.5f, Params::METERS/2.f);
			if (DegToRad(-0) >= racketRad) {
				playerPos = playerPos - playerSize;
				playerPos.y += playerSize.y;
			}

			if (ball->CollisionRacket(playerPos, playerSize)) {

				racketHit = true;
			}
			colliderPos = playerPos;
			colliderSize = playerSize;
		}
	}

}

void Player::Draw(){
	transform.MakeMatrix();
	VECTOR disp = VGet(1, 1, 1) * transform.matrix;

	//�l�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/1.5f);
	DrawCapsule3D(disp,disp+VGet(0,height,0), radius, 32, 0xffffff, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//���P�b�g�`��
	VECTOR racketPos = disp+VGet(0,height/1.2f,0);
	MATRIX rotY = MGetRotY(racketRad );
	VECTOR dispRacket = racketPos + VGet(1,1,Params::METERS) * rotY;
	DrawLine3D(racketPos, dispRacket,0xe50000);
	for(int i=0;i<100;i++)
		DrawLine3D(racketPos+VGet(-i,i,i), dispRacket+VGet(-i,i,i), 0xe50000);

#ifdef _DEBUG
	//���P�b�g�����蔻��
	int color = 0xffffff;
	if (racketHit) {
		color = 0xe50000;
		racketHit = false;
	}
	DrawBox3D(colliderPos, colliderPos+colliderSize,color);
#endif
}
