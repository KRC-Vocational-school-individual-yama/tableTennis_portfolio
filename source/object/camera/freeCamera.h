#pragma once
#include"../../libs/frameWork/object.h"

/// <summary>
/// 自由カメラ
/// </summary>
class FreeCamera :public Object {
public:
	FreeCamera(Scene* sc);
	~FreeCamera()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	//カメラ座標
	const VECTOR& GetPos() { return position+velocity; }
	void SetPos(VECTOR pos) { position = pos; }
	void SetTar(VECTOR tar) { target = tar; }
	//カメラ方向ベクトル
	VECTOR GetDir();
	//const VECTOR& GetRot() { return rotation; }
private:
	void DispMove();
	void UpDownMove();
	void Movement();


	VECTOR position;
	VECTOR target;
	VECTOR tarPos;
	VECTOR velocity;
	VECTOR rotation;
	Vec2 mouse;
	Vec2 oldMouse;

};