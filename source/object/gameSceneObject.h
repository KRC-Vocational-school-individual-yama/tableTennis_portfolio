#pragma once
#include"../libs/frameWork/object.h"

/// <summary>
/// �ŏ��ɂ��������
/// ���͂Ƃ肠�����̃f�o�b�O�p�ɂȂ��Ă���
/// </summary>
class GameSceneObject :public Object {
public:
	GameSceneObject(Scene* sc);
	~GameSceneObject()	override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:

};
