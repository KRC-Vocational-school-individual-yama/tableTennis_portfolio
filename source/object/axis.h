#pragma once
#include"../libs/frameWork/object.h"

/// <summary>
/// ���W��
/// </summary>
class Axis :public Object {
public:
	Axis(Scene* sc);
	~Axis()override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:
};
