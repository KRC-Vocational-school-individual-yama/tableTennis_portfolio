#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"

class Ball :public Object {
public:
	Ball(Scene* sc);
	~Ball()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	bool CollisionCube(const VECTOR& pos, const VECTOR& size);
	bool CollisionFront(const VECTOR& pos, const VECTOR& dirNorm);

	void Ball::Attenuation(float value);
private:
	Transform transform;
	VECTOR velocity;
	VECTOR rotateVelocity;
};