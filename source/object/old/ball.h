#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"

/// <summary>
/// �싅�̋�
/// </summary>
class Ball :public Object {
public:
	Ball(Scene* sc);
	~Ball()override;
	void Init()override;
	void Update()override;
	void Draw()override;

	//�J�x�Ƃ̓����蔻��
	bool CollisionWall(const VECTOR& pos, const VECTOR& size, const VECTOR& dirNorm);
	//�싅�� �e�[�u���̂ݓ����蔻��
	bool CollisionTable(const VECTOR& pos, const VECTOR& size, const VECTOR& dirNorm);
	//���P�b�g �Ƃ̓����蔻��
	bool CollisionRacket(const VECTOR& pos, const VECTOR& size);

	//�O�Ȃ�true
	bool CollisionFront(const VECTOR& pos,const VECTOR& dirNorm);
	//�����ȗ����̂̓����蔻��
	bool CollisionCube(const VECTOR& pos, const VECTOR& size);
	//ToDo:�C������������
	//���������闧���̂̓����蔻��//bool CollisionCubeDirection(const VECTOR& pos, const VECTOR& size, const VECTOR& norm);
private:
	Transform transform;
	VECTOR rotateVelocity;
	float radius;
	int hModel;

	//velocity ����
	void Attenuation(float value);
};
