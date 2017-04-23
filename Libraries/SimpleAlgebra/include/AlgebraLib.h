#ifndef _SIMPLE_ALGEBRA_H_
#define _SIMPLE_ALGEBRA_H_

#ifdef USING_LEFT_HANDEND_SYSTEM
#define Mat4RotateX			Mat4D::RotateXLH
#define Mat4RotateY			Mat4D::RotateYLH
#define Mat4RotateZ			Mat4D::RotateZLH
#define Mat4Translate		Mat4D::TranslateLH
#define Mat4LookAt			Mat4D::LookAtLH
#define Mat4PerspectiveFov	Mat4D::PerspectiveFovLH
#else
#define Mat4RotateX			Mat4D::RotateXRH
#define Mat4RotateY			Mat4D::RotateYRH
#define Mat4RotateZ			Mat4D::RotateZRH
#define Mat4Translate		Mat4D::TranslateLH
#define Mat4LookAt			Mat4D::LookAtRH
#define Mat4PerspectiveFov  Mat4D::PerspectiveFovRH
#endif // USING_LEFT_HANDEND_SYSTEM

namespace Mat4D
{


	class CMatrix4D;

	class CVector4D
	{
	public:
		union
		{
			struct 
			{
				float x, y, z, w;
			};
			struct  
			{
				float r, g, b, a;
			};
			float val[4];
		};
		CVector4D();
		CVector4D(const CVector4D& cpy);
		CVector4D(float x_, float y_, float z_, float w_);
		CVector4D& operator+=(const CVector4D& rhs);
		CVector4D& operator*=(float scalar);
		CVector4D& operator-=(const CVector4D& rhs);
		CVector4D& operator/=(float scalar);
		float		Dot(const CVector4D& b)	const;
		float		Magnitude() const;
		CVector4D	Cross(const CVector4D& b) const;
		CVector4D	Normalize() const;
	};

	CVector4D operator+(CVector4D lhs, const CVector4D& rhs);
	CVector4D operator-(CVector4D lhs, const CVector4D& rhs);
	CVector4D operator*(CVector4D vec, float scalar);
	CVector4D operator*(float scalar, const CVector4D& vec);
	CVector4D operator/(CVector4D vec, float scalar);


	class CMatrix4D
	{
	public:
		union 
		{
			struct 
			{
				float	m00, m01, m02, m03,
						m10, m11, m12, m13,
						m20, m21, m22, m23,
						m30, m31, m32, m33;
			};
			struct
			{
				CVector4D r0, r1, r2, r3;
			};
			float m[4][4];
			float v[16] = { 0 };
		};
		CMatrix4D();
		CMatrix4D(float* a);
		CMatrix4D(const CMatrix4D& cpy);
		CMatrix4D	(
					const CVector4D& row1,
					const CVector4D& row2,
					const CVector4D& row3,
					const CVector4D& row4
					);
		CMatrix4D	(
					float i00, float i01, float i02, float i03,
					float i10, float i11, float i12, float i13,
					float i20, float i21, float i22, float i23,
					float i30, float i31, float i32, float i33
					);
		CMatrix4D& operator*=(const CMatrix4D& rhs);
		CMatrix4D& operator=(float* a);
		void	Identity();
		void	Zero();
	};

	CVector4D operator*(CMatrix4D lhs, const CVector4D & rhs);
	CVector4D operator*(CVector4D lhs, const CMatrix4D & rhs);
	CMatrix4D operator*(CMatrix4D lhs, const CMatrix4D& rhs);

	//TODO: Meter a la como metodos de la clase
	CMatrix4D Scale(float sx, float sy, float sz);

	CMatrix4D TranslateLH(float tx, float ty, float tz);
	CMatrix4D RotateXLH(float theta);
	CMatrix4D RotateYLH(float theta);
	CMatrix4D RotateZLH(float theta);
	CMatrix4D LookAtLH(const CVector4D& eye, const CVector4D& at, const CVector4D up);
	CMatrix4D PerspectiveFovLH(float fovy, float aspect, float zn, float zf);

	CMatrix4D TranslateRH(float tx, float ty, float tz);
	CMatrix4D RotateXRH(float theta);
	CMatrix4D RotateYRH(float theta);
	CMatrix4D RotateZRH(float theta);
	CMatrix4D LookAtRH(const CVector4D& eye, const CVector4D& at, const CVector4D up);
	CMatrix4D PerspectiveFovRH(float fovy, float aspect, float zn, float zf);

}

#endif //_SIMPLE_ALGEBRA_H_