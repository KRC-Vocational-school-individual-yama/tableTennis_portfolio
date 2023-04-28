#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"
#include"../libs/common/keyManager.h"

/// <summary>
/// �ʂ�łl�@���P�b�g
/// </summary>
class Player :public Object {
public:
	Player(Scene* sc);
	~Player()override;
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Transform transform;
	KeyManager* keys;
	float radius;
	float height;
	float moveSpeed;

	float racketRad;

	VECTOR colliderPos;
	VECTOR colliderSize;
	bool racketHit;
};

