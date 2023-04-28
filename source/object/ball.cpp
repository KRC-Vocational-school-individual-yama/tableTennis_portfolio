#include "ball.h"

namespace {
	static const float Gravity = 4.1f;

}

Ball::Ball(Scene* sc)
	:Object(sc)
	,transform()
	,velocity()
	,rotateVelocity()
{}

Ball::~Ball(){

}

void Ball::Init(){

}

void Ball::Update(){

	//�d��
	velocity.y -= Gravity;
	//��C��R
	Attenuation(0.5f);

	//
	transform.position += velocity;

	
}

void Ball::Draw(){

}
bool Ball::CollisionCube(const VECTOR& pos, const VECTOR& size) {
	bool yFront = CollisionFront(pos, VGet(0, -1, 0));//���
	bool yBack = CollisionFront(pos + size, VGet(0, 1, 0));//����
	bool xFront = CollisionFront(pos, VGet(-1, 0, 0));//�E��
	bool xBack = CollisionFront(pos + size, VGet(1, 0, 0));//����
	bool zFront = CollisionFront(pos, VGet(0, 0, -1));//�O��
	bool zBack = CollisionFront(pos + size, VGet(0, 0, 1));//���

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

bool Ball::CollisionFront(const VECTOR& pos, const VECTOR& dirNorm) {
	VECTOR dot1 = dirNorm;
	VECTOR dot2 = pos - transform.position;
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

