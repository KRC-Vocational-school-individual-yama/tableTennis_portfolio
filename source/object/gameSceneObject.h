#pragma once
#include"../libs/frameWork/object.h"

/// <summary>
/// 最初にあったやつ
/// 今はとりあえずのデバッグ用になっている
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
