#pragma once
#include"../libs/frameWork/object.h"

class Racket :public Object {
public:
	Racket(Scene*sc);
	~Racket()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	int hModel;
	VECTOR mouse3D;
};