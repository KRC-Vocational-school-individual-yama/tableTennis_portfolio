#include "ball.h"
#include"params.h"

#include"../libs/common/keyManager.h"
namespace {
	KeyManager* keys=nullptr;
	static const float Gravity = 9.81f/3;
	static const float AirResistance = 0.97f / 3;
}

Ball::Ball(Scene* sc)
	:Object(sc)
	,transform()
	,rotateVelocity()
	,radius()
	,hModel(-1)
{}

Ball::~Ball(){
	MV1DeleteModel(hModel);
	delete keys;
}

void Ball::Init(){
	keys = new KeyManager;
	hModel = MV1LoadModel("data/model/roundCube.mv1");
	//hModel = MV1LoadModel("data/model/lightBulb.mv1");
	assert(hModel > 0);
	transform.position = VGet(0,Params::METERS*1.5,-Params::METERS);
	transform.rotation = VGet(0, DegToRad(45), 0);
	radius = 100;// 42.f;
	rotateVelocity = VGet(0,90,0);
	transform.velocity = VGet(0,0,200);

	transform.position = VGet(-Params::METERS/2, Params::METERS * 2, 0);
}

void Ball::Update(){

	//velocity��position�ɓK��
	transform.position += transform.velocity;
	transform.rotation += rotateVelocity;

	//velocity���� ��C��R�̂���
	float attenuation = AirResistance;//������
	Attenuation(attenuation);
	
	//�������蔻��
	{
		VECTOR posFloor		= VGet(transform.position.x, 0, transform.position.z);
		VECTOR sizeFloor	= VGet(10, 1000, 10);
		bool floorCollider	= CollisionCube(posFloor - sizeFloor, sizeFloor);
		if (floorCollider) {
			transform.velocity.y *= -1;
			transform.position.y = 0;

			Attenuation(0.99f);//���ڐG�̌���
		}
	}

	


	//�d��
	transform.velocity -= VGet(0 , Gravity, 0);

#ifdef _DEBUG //�f�o�b�O�p
	//�����������̂ňړ�����
	{
		int debugMoveSpeed = 10;
		if (keys->DownKeep(KEY_INPUT_UP)	){transform.position.z += debugMoveSpeed;}
		if (keys->DownKeep(KEY_INPUT_DOWN)	){transform.position.z -= debugMoveSpeed;}
		if (keys->DownKeep(KEY_INPUT_RIGHT)	){transform.position.x += debugMoveSpeed;}
		if (keys->DownKeep(KEY_INPUT_LEFT)	){transform.position.x -= debugMoveSpeed;}
	}
	//�������]�@�f�o�b�O�p
	if (keys->Down(KEY_INPUT_R)) {
		transform.velocity = transform.velocity * MGetRotY(DegToRad(180));
	}

	//�f�o�b�O�p
	//transform.position.y= transform.position.y <= 0 ? 0:transform.position.y;
#endif
}

void Ball::Draw() {
	transform.MakeMatrix();
	VECTOR disp = VGet(1, 1, 1) * transform.matrix;

	//DrawSphere3D(disp,radius,32,0xffffff,0xffffff,TRUE);

	MV1DrawModelMatrix(transform.matrix, hModel);


#ifdef _DEBUG //�f�o�b�O�p ����

	//�{�[���i���ցj�����蔻��
	DrawBox3D(transform.position,transform.position+ VGet(radius,radius,radius),0xffe5ff);

	//���i�{�[���ցj�����蔻��@
	VECTOR posFloor	 = VGet(transform.position.x, 0, transform.position.z);
	VECTOR sizeFloor = VGet(10, 1000, 10);
	DrawBox3D(posFloor - sizeFloor, posFloor );


#endif
}

bool Ball::CollisionWall(const VECTOR& pos, const VECTOR& size, const VECTOR& norm){
	if (CollisionCube(pos, size)) {
		transform.velocity = transform.velocity * MGetRotY(DegToRad(180.f));
		return true;
	}
	return false;
}

bool Ball::CollisionTable(const VECTOR& pos, const VECTOR& size, const VECTOR& dirNorm){
	if (CollisionCube(pos, size)) {
		transform.velocity.y *= -1;
		transform.position.y = pos.y + size.y+radius;


		return true;
	}
	return false;
}

bool Ball::CollisionRacket(const VECTOR& pos, const VECTOR& size){
	if (CollisionCube(pos, size)) {
		transform.velocity += VGet(1, 1, 200/4);// *MGetRotY(0);
		transform.velocity += VGet(1,1,200)*MGetRotX(DegToRad( -3));

		return true;
	}
	return false;
}

bool Ball::CollisionCube(const VECTOR& pos, const VECTOR& size){
	bool yFront = CollisionFront(pos		, VGet( 0,-1, 0));//���
	bool yBack	= CollisionFront(pos + size	, VGet( 0, 1, 0));//����
	bool xFront = CollisionFront(pos		, VGet(-1, 0, 0));//�E��
	bool xBack	= CollisionFront(pos + size	, VGet( 1, 0, 0));//����
	bool zFront = CollisionFront(pos		, VGet( 0, 0,-1));//�O��
	bool zBack	= CollisionFront(pos + size	, VGet( 0, 0, 1));//���

	bool boxCollider{
		zFront
		&& zBack
		&& xFront
		&& xBack
		&& yFront
		&& yBack
	};
	if (boxCollider)
		return true;
	return false;
}

bool Ball::CollisionFront(const VECTOR& pos, const VECTOR& dirNorm){
	VECTOR dot1= dirNorm;
	VECTOR dot2= pos - transform.position;
	float ans = VDot(dot1, dot2);//����
	//cos�𒊏o
	ans /= VSize(dot1);
	ans /= VSize(dot2);

	if (ans >= 0)
		return true;
	return false;
}

void Ball::Attenuation(float value) {
	transform.velocity *= VGet(value, value, value);
	rotateVelocity *= VGet(value, value, value);
}
