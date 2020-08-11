#include "AlgebraLib.h"
#include <algorithm>
#include <cmath>

namespace Mat4D
{
	CVector4D::CVector4D() :
		val{}
	{
	}

	CVector4D::CVector4D(const CVector4D & cpy) :
		val{ cpy.x, cpy.y, cpy.z, cpy.w }
	{
	}

	CVector4D::CVector4D(float x_, float y_, float z_, float w_) :
		x(x_),
		y(y_),
		z(z_),
		w(w_)
	{
	}

	CVector4D& CVector4D::operator+=(const CVector4D & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	CVector4D& CVector4D::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	CVector4D& CVector4D::operator-=(const CVector4D & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	CVector4D& CVector4D::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	float CVector4D::Dot(const CVector4D& b) const
	{
		return x * b.x + y * b.y + z * b.z + w * b.w;
	}

	float CVector4D::Magnitude() const
	{
		return sqrtf(this->Dot(*this));
	}

	CVector4D CVector4D::Cross(const CVector4D & b) const
	{
		return CVector4D(
			y * b.z - z * b.y,
			z * b.x - x * b.z,
			x * b.y - y * b.x, 0);
	}

	CVector4D CVector4D::Normalize() const
	{
		float magnitude = Magnitude();
		return magnitude != 0 ? *this / magnitude : CVector4D();
	}

	CVector4D operator*(CVector4D lhs, const CMatrix4D & rhs)
	{
		CVector4D r;
		r.x = lhs.x * rhs.m00;
		r.x += lhs.y * rhs.m10;
		r.x += lhs.z * rhs.m20;
		r.x += lhs.w * rhs.m30;

		r.y = lhs.x * rhs.m01;
		r.y += lhs.y * rhs.m11;
		r.y += lhs.z * rhs.m21;
		r.y += lhs.w * rhs.m31;

		r.z = lhs.x * rhs.m02;
		r.z += lhs.y * rhs.m12;
		r.z += lhs.z * rhs.m22;
		r.z += lhs.w * rhs.m32;

		r.w = lhs.x * rhs.m03;
		r.w += lhs.y * rhs.m13;
		r.w += lhs.z * rhs.m23;
		r.w += lhs.w * rhs.m33;

		return r;
	}

	CVector4D operator+(CVector4D lhs, const CVector4D & rhs)
	{
		lhs += rhs;
		return lhs;
	}

	CVector4D operator-(CVector4D lhs, const CVector4D & rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	CVector4D operator*(CVector4D vec, float scalar)
	{
		vec *= scalar;
		return vec;
	}

	CVector4D operator*(float scalar, const CVector4D & vec)
	{
		return vec * scalar;
	}

	CVector4D operator/(CVector4D vec, float scalar)
	{
		return vec /= scalar;
	}

	CVector4D operator*(CMatrix4D lhs, const CVector4D & rhs)
	{
		return CVector4D(
			lhs.r0.Dot(rhs),
			lhs.r1.Dot(rhs),
			lhs.r2.Dot(rhs),
			lhs.r3.Dot(rhs)
		);
	}

	CMatrix4D operator*(CMatrix4D a, const CMatrix4D & b)
	{
		return
		{
			a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0],	a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1],	a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2],	a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3],
			a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0],	a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1],	a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2],	a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3],
			a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0],	a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1],	a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2],	a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3],
			a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0],	a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1],	a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2],	a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3]
		};
		/*for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		for (int k = 0; k < 4; k++)
		R.m[i][j] += lhs.m[i][k] * rhs.m[k][j];*/
	}

	CMatrix4D::CMatrix4D() :
		v{}
	{
	}

	CMatrix4D::CMatrix4D(float * a)
	{
		*this = a;
	}

	CMatrix4D::CMatrix4D(const CMatrix4D & cpy) :
		v
	{
		cpy.m00, cpy.m01, cpy.m02, cpy.m03,
		cpy.m10, cpy.m11, cpy.m12, cpy.m13,
		cpy.m20, cpy.m21, cpy.m22, cpy.m23,
		cpy.m30, cpy.m31, cpy.m32, cpy.m33
	}
	{

	}

	CMatrix4D::CMatrix4D(const CVector4D & row1, const CVector4D & row2, const CVector4D & row3, const CVector4D & row4)
	{
		r0 = row1;
		r1 = row2;
		r2 = row3;
		r3 = row4;
	}

	CMatrix4D::CMatrix4D
	(
		float i00, float i01, float i02, float i03,
		float i10, float i11, float i12, float i13,
		float i20, float i21, float i22, float i23,
		float i30, float i31, float i32, float i33
	) :
		v
	{
		i00, i01, i02, i03,
		i10, i11, i12, i13,
		i20, i21, i22, i23,
		i30, i31, i32, i33
	}
	{
	}

	CMatrix4D& CMatrix4D::operator*=(const CMatrix4D & rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	CMatrix4D& CMatrix4D::operator=(float * a)
	{
		v[0] = a[0];	v[1] = a[1];	v[2] = a[2];  v[3] = a[3];
		v[4] = a[4];	v[5] = a[5];	v[6] = a[6];  v[7] = a[7];
		v[8] = a[8];	v[9] = a[9];	v[10] = a[10]; v[11] = a[11];
		v[12] = a[12];	v[13] = a[13];	v[14] = a[14]; v[15] = a[15];
		return *this;
	}

	void CMatrix4D::Identity()
	{
		Zero();
		m00 = 1.f;
		m11 = 1.f;
		m22 = 1.f;
		m33 = 1.f;
	}

	void CMatrix4D::Zero()
	{
		v[0] = 0; v[1] = 0; v[2] = 0; v[3] = 0;
		v[4] = 0; v[5] = 0; v[6] = 0; v[7] = 0;
		v[8] = 0; v[9] = 0; v[10] = 0; v[11] = 0;
		v[12] = 0; v[13] = 0; v[14] = 0; v[15] = 0;
	}

	CMatrix4D Scale(float sx, float sy, float sz)
	{
		return CMatrix4D
		(
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D TranslateLH(float tx, float ty, float tz)
	{
		return CMatrix4D
		(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			tx, ty, tz, 1
		);
	}

	CMatrix4D RotateXLH(float theta)
	{
		return CMatrix4D(
			1, 0, 0, 0,
			0, cosf(theta), sin(theta), 0,
			0, -sinf(theta), cosf(theta), 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D RotateYLH(float theta)
	{
		return CMatrix4D(
			cosf(theta), 0, -sinf(theta), 0,
			0, 1, 0, 0,
			sinf(theta), 0, cos(theta), 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D RotateZLH(float theta)
	{
		return CMatrix4D(
			cosf(theta), sinf(theta), 0, 0,
			-sinf(theta), cosf(theta), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D LookAtLH(const CVector4D & eye, const CVector4D & at, const CVector4D up)
	{
		CVector4D zaxis = (at - eye).Normalize();
		CVector4D xaxis = (up.Cross(zaxis)).Normalize();
		CVector4D yaxis = zaxis.Cross(xaxis);

		return{ xaxis.x ,   yaxis.x , zaxis.x , 0,
			xaxis.y ,   yaxis.y , zaxis.y , 0,
			xaxis.z ,	yaxis.z , zaxis.z ,	0,
			-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye),  1 };
	}

	CMatrix4D PerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	{
		float sen = std::sinf(fovy * 0.5f);
		float yScale = sen != 0.0f ? std::cosf((fovy * 0.5f)) / sen : 0.f;

		float xScale = yScale / aspect;

		return{ xScale,  0,			0,						0,
			0,		 yScale,    0,						0,
			0,       0,			zf / (zf - zn),			1,
			0,		 0,			-zn*zf / (zf - zn),     0 };

	}


	//Right handed system

	CMatrix4D TranslateRH(float tx, float ty, float tz)
	{
		return CMatrix4D
		(
			1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1
		);
	}

	CMatrix4D RotateXRH(float theta)
	{
		return CMatrix4D(
			1, 0, 0, 0,
			0, cosf(theta), -sin(theta), 0,
			0, sinf(theta), cosf(theta), 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D RotateYRH(float theta)
	{
		return CMatrix4D(
			cosf(theta), 0, sinf(theta), 0,
			0, 1, 0, 0,
			-sinf(theta), 0, cos(theta), 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D RotateZRH(float theta)
	{
		return CMatrix4D(
			cosf(theta), -sinf(theta), 0, 0,
			sinf(theta), cosf(theta), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	CMatrix4D LookAtRH(const CVector4D & eye, const CVector4D & at, const CVector4D up)
	{
		CVector4D zaxis = (eye - at).Normalize();
		CVector4D xaxis = (up.Cross(zaxis)).Normalize();
		CVector4D yaxis = zaxis.Cross(xaxis);

		return{ xaxis.x ,   yaxis.x , zaxis.x , 0,
				xaxis.y ,   yaxis.y , zaxis.y , 0,
				xaxis.z ,	yaxis.z , zaxis.z ,	0,
				-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye),  1 };
	}

	CMatrix4D PerspectiveFovRH(float fovy, float aspect, float zn, float zf)
	{
		float sen = std::sinf(fovy * 0.5f);
		float yScale = sen != 0.0f ? std::cosf((fovy * 0.5f)) / sen : 0.f;

		float xScale = yScale / aspect;

		return{
			xScale,		0,			0,						0,
			0,			yScale,		0,						0,
			0,			0,			zf / (zn - zf),			-1,
			0,			0,			zn*zf / (zn - zf),      0 };
	}

}