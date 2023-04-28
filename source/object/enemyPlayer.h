#pragma once
#include"../libs/frameWork/object.h"

class EnemyPlayer :public Object {
public:
	EnemyPlayer(Scene* sc);
	~EnemyPlayer()override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:

};