#pragma once
#include"../libs/frameWork/object.h"


class Params :public Object {
public:
	Params(Scene* sc);
	~Params()override;
	void Init()override;
	void Update()override;
	void Draw()override;

	static constexpr int METERS=1000;//�@�s�N�Z���@/�@1���[�g��
	static constexpr int CENTI_METER= METERS/100;//�@�Z���`�@���[�g��
private:

};