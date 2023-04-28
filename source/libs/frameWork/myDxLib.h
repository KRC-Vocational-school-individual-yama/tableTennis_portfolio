#pragma once

#include<DxLib.h>
#include<cassert>
//#include<string>
//#include<vector>
//#include<unordered_map>
//#include<algorithm>
#include"../../main/config.h"
#include"../common/colorhsv.h"
#include"../common/easeing.h"

namespace DxLib {
	struct Vec2 {
		int x = 0, y = 0;

		static Vec2 zero() { return Vec2{ 0,0 }; }
		operator VECTOR () {
			return VGet(static_cast<float>(x), static_cast<float>(y), 0);
		}

		Vec2 operator +(const Vec2& a) { return Vec2{ this->x + a.x,this->y + a.y }; }
		Vec2 operator -(const Vec2& a) { return Vec2{ this->x - a.x,this->y - a.y }; }
		Vec2 operator *(const Vec2& a) { return Vec2{ this->x * a.x,this->y * a.y }; }
		Vec2 operator /(const Vec2& a) { return Vec2{ this->x / a.x,this->y / a.y }; }
		Vec2 operator %(const Vec2& a) { return Vec2{ this->x % a.x,this->y % a.y }; }
		const Vec2& operator +=(const Vec2& a) {
			this->x += a.x;
			this->y += a.y;
			return (*this);
		}
		const Vec2& operator -=(const Vec2& a) {
			this->x -= a.x;
			this->y -= a.y;
			return (*this);
		}
		const Vec2& operator *=(const Vec2& a) {
			this->x *= a.x;
			this->y *= a.y;
			return (*this);
		}
		const Vec2& operator /=(const Vec2& a) {
			this->x /= a.x;
			this->y /= a.y;
			return (*this);
		}
		const Vec2& operator %=(const Vec2& a) {
			this->x %= a.x;
			this->y %= a.y;
			return (*this);
		}
		const bool operator ==(const Vec2& a) { return ((this->x == a.x) && (this->y == a.y)); }

		Vec2 operator -(const VECTOR& a) { return (*this) - Vec2{ (int)a.x,(int)a.y }; }

	};

	struct Rect {
		Rect(float x, float y, float sx, float sy)
			:posX(x)
			, posY(y)
			, sizeX(sx)
			, sizeY(sy)
		{}

		float posX;
		float posY;
		float sizeX;
		float sizeY;
	};

	//四角当たり判定
	inline bool SquareCollision(Rect a, Rect b) {
		if (a.posY >= b.posY + b.sizeY)
			return false;//up
		if (a.posY + a.sizeY <= b.posY)
			return false;//down

		if (a.posX >= b.posX + b.sizeX)
			return false;//left
		if (a.posX + a.sizeX <= b.posX)
			return false;//right


		return true;
	}

	//left top : x,y 
	//right bottom : xSize,ySize
	//true：当たっている
	inline bool SquareCollision(RECT a, RECT b) {
		if (a.top >= b.top + b.bottom)return false;
		if (a.top + a.bottom <= b.top)return false;
		if (a.left >= b.left + b.right)return false;
		if (a.left + a.right <= b.left)return false;

		//どこにも触れていなければfalseの逆説
		return true;

	}

	inline bool SquareCollision(const VECTOR& posa, const VECTOR& sizea, const VECTOR& posb, const VECTOR& sizeb) {
		Rect a = Rect(posa.x, posa.y, sizea.x, sizea.y);
		Rect b = Rect(posb.x, posb.y, sizeb.x, sizeb.y);

		return SquareCollision(a, b);
	}

	//deg（度）から rad（ラジアン）へ変換
	inline float DegToRad(float deg) {return DX_PI_F /180.f * deg;	}
	inline double DegToRad(double deg) { return DX_PI / 180. * deg; }
	inline float DegToRad(int deg) {return DegToRad(static_cast<float>(deg));}
	//rad（ラジアン）から deg（度）へ変換
	inline float RadToDeg(float rad) { return rad * 180.f / DX_PI_F; }
	inline float RadToDeg(int rad) { return RadToDeg(static_cast<float>(rad)); }


	inline int DrawGraphVector(const VECTOR& pos, int GrHandle, int TransFlag) {
		return DrawGraphF(pos.x, pos.y, GrHandle, TransFlag);
	}

	inline int DrawExtendGraphVector(const VECTOR& pos, const VECTOR& size, int GrHandle, int TransFlag) {
		return DrawExtendGraphF(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GrHandle, TransFlag);
	}

	inline int DrawBoxVector(const VECTOR& pos, const VECTOR& size, unsigned int Color, int FillFlag) {
		return DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, Color, FillFlag);
	}
	inline int DrawBoxCenter(float   x1, float   y1, float   x2, float   y2, unsigned int Color, int FillFlag) {
		return DrawBoxAA(x1,y1,x2,y2,Color,FillFlag);
	}
	inline int DrawBoxCenterVector(const VECTOR& pos, const VECTOR& size, unsigned int Color, int FillFlag) {
		return DrawBoxCenter(pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2, Color, FillFlag);
	}
	inline int MV1DrawModelMatrix(const MATRIX& Matrix, const int& MHandle) {
		MV1SetMatrix(MHandle,Matrix);
		return MV1DrawModel(MHandle);
	}

	inline int DrawRotaGraph3FVector(const VECTOR& pos, const VECTOR& size, float rotate, int GrHandle, int TransFlag) {

		int graphX = 0, graphY = 0;
		GetGraphSize(GrHandle, &graphX, &graphY);

		float Fsize_x = size.x, Fsize_y = size.y;
		float size_x = Fsize_x / graphX;
		float size_y = Fsize_y / graphY;
		return DrawRotaGraph3F(pos.x + size.x / 2.f, pos.y + size.y / 2.f, graphX / 2.f, graphY / 2.f, size_x, size_y, rotate, GrHandle, TransFlag);
	}

	//立方体描画 start = 始点　end = 終点 color = 色(デフォルト白)
	inline void DrawBox3D(const VECTOR& start, const VECTOR& end, unsigned int color = 0xffffff) {
		DrawLine3D(start, VGet(end.x, start.y, start.z), color);
		DrawLine3D(start, VGet(start.x, end.y, start.z), color);
		DrawLine3D(start, VGet(start.x, start.y, end.z), color);

		DrawLine3D(VGet(start.x, end.y, end.z), VGet(start.x, end.y, start.z), color);
		DrawLine3D(VGet(start.x, end.y, end.z), VGet(start.x, start.y, end.z), color);
		DrawLine3D(VGet(start.x, end.y, end.z), VGet(end.x, end.y, end.z), color);

		DrawLine3D(VGet(end.x, end.y, start.z), VGet(start.x, end.y, start.z), color);
		DrawLine3D(VGet(end.x, end.y, start.z), VGet(end.x, start.y, start.z), color);
		DrawLine3D(VGet(end.x, end.y, start.z), VGet(end.x, end.y, end.z), color);

		DrawLine3D(VGet(end.x, start.y, end.z), VGet(start.x, start.y, end.z), color);
		DrawLine3D(VGet(end.x, start.y, end.z), VGet(end.x, end.y, end.z), color);
		DrawLine3D(VGet(end.x, start.y, end.z), VGet(end.x, start.y, start.z), color);
	}

	// 座標 法線 ディフューズカラー スペキュラカラー テクスチャ座標
	inline VERTEX3D GetVertex3D(const VECTOR& pos,const VECTOR& norm
		,const COLOR_U8& dif
		,const COLOR_U8& spc
		,float u, float v
		,float su=0,float sv=0) {
		VERTEX3D anser;
		anser.pos	=pos;
		anser.norm	=norm;
		anser.spc	=spc;
		anser.dif	=dif;
		anser.u		=u	;
		anser.v		=v	;
		anser.su	=su	;
		anser.sv	=sv	;
		return anser;
	}
	inline VERTEX3D GetVertex3D(const VECTOR& pos
		,const COLOR_U8& dif
		,float u, float v
	) {
		VERTEX3D anser;
		anser.pos	=pos;
		anser.norm	=VGet(0,0,1);
		anser.dif	=dif;
		anser.spc	=GetColorU8(0,0,0,0);
		anser.u		=u	;
		anser.v		=v	;
		anser.su	=0;
		anser.sv	=0;
		return anser;
	}
	inline VECTOR VGet(const Vec2& value) {
		return VGet((float)value.x, (float)value.y, 0);
	}
	inline const VECTOR operator +(const VECTOR& a, const VECTOR& b) {
		return VAdd(a, b);
	}
	inline const VECTOR operator +=(VECTOR& a, const VECTOR& b) {
		return a= VAdd(a, b);
	}
	inline const VECTOR operator -(const VECTOR& a, const VECTOR& b) {
		return VSub(a, b);
	}
	inline VECTOR operator -=( VECTOR& a, const VECTOR& b) {
		return a = a - b;
	}
	inline const VECTOR operator *(const VECTOR& a, const VECTOR& b) {
		return { a.x * b.x,a.y * b.y,a.z * b.z };
	}
	inline VECTOR& operator *=(VECTOR& a, const VECTOR& b) {
		return a = a * b;
	}
	inline const VECTOR operator /(const VECTOR& a, const VECTOR& b) {
		return {a.x/b.x,a.y/b.y,a.z/b.z};
	}
	inline VECTOR& operator /=(VECTOR& a, const VECTOR& b) {
		return a = a / b;
	}
	inline VECTOR& operator /=(VECTOR& a, const int& b) {
		return a /= VGet((float)b, (float)b, (float)b);
	}
	inline const MATRIX operator *(const MATRIX& a, const MATRIX& b) {
		return MMult(a, b);
	}
	inline const VECTOR operator *(const VECTOR& a, const MATRIX& b) {
		return VTransform(a, b);
	}

}