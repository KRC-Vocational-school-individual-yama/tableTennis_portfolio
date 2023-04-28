#pragma once
#include"../libs/frameWork/object.h"
#include"../libs/common/transForm.h"

/// <summary>
/// 卓球の玉
/// </summary>
class Ball :public Object {
public:
	Ball(Scene* sc);
	~Ball()override;
	void Init()override;
	void Update()override;
	void Draw()override;

	//カベとの当たり判定
	bool CollisionWall(const VECTOR& pos, const VECTOR& size, const VECTOR& dirNorm);
	//卓球台 テーブルのみ当たり判定
	bool CollisionTable(const VECTOR& pos, const VECTOR& size, const VECTOR& dirNorm);
	//ラケット との当たり判定
	bool CollisionRacket(const VECTOR& pos, const VECTOR& size);

	//前ならtrue
	bool CollisionFront(const VECTOR& pos,const VECTOR& dirNorm);
	//垂直な立方体の当たり判定
	bool CollisionCube(const VECTOR& pos, const VECTOR& size);
	//ToDo:気が向いたら作る
	//方向がある立方体の当たり判定//bool CollisionCubeDirection(const VECTOR& pos, const VECTOR& size, const VECTOR& norm);
private:
	Transform transform;
	VECTOR rotateVelocity;
	float radius;
	int hModel;

	//velocity 減衰
	void Attenuation(float value);
};
