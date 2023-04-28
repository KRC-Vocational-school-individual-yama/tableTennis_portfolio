#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"

class Table :public Object {
public:
	Table(Scene* sc);
	~Table()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	int hModel;
	int hCube;
	Transform transform;

};