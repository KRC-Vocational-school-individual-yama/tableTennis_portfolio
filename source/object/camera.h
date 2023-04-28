#pragma once
#include"../libs/frameWork/object.h"

class Camera :public Object {
public:
	Camera(Scene* sc);
	~Camera()override;
	void Init()override;
	void Update()override;
	void Draw()override;

	VECTOR GetPos() { return position; }
	void SetPos(const VECTOR& pos) { position = pos; }
	void SetTar(const VECTOR& tar) { target = tar; }
private:
	VECTOR position;
	VECTOR target;
};