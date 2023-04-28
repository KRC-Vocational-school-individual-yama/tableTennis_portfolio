#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"
#include<vector>

/// <summary>
/// �e�[�u����@�ǂȂǂ͈̔�
/// </summary>
class Field :public Object {
public:
	Field(Scene* sc);
	~Field()override;
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	Transform transform;
	VECTOR size;
	int hModel;
	std::vector<int>textureImgs;

	bool wallHit;
	bool tableHit;
};
