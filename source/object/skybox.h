#pragma once
#include"../libs/frameWork/object.h"

/// <summary>
/// ��V��
/// </summary>
class Skybox :public Object {
public:
	Skybox(Scene* sc);
	~Skybox()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	int hModel;
};
