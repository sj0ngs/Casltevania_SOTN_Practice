#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2()	:
		x(0.f),
		y(0.f)
	{
	}

	Vec2(float _x, float _y)	:
		x(_x),
		y(_y)
	{
	}

	Vec2(LONG _x, LONG _y) :

		x((float)_x),
		y((float)_y)
	{
	}

	Vec2(POINT _pt) :
		x((float)_pt.x),
		y((float)_pt.y)
	{
	}

	~Vec2()
	{
	}

public:
	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	void operator += (float _f)
	{
		x += _f;
		y += _f;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator -= (float _f)
	{
		x -= _f;
		y -= _f;
	}

	Vec2 operator / (Vec2 _vOther)
	{
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (Vec2 _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}

	Vec2 operator / (float _f)
	{
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}


	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	void operator *= (Vec2 _vOther)
	{
		x *= _vOther.x;
		y *= _vOther.y;
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

	bool operator == (Vec2 _Other)
	{
		return x == _Other.x && y == _Other.y;
	}

	bool operator != (Vec2 _Other)
	{
		return x != _Other.x && y != _Other.y;
	}

public:
	void Normalize()	// ������ ����ȭ
	{
		float fDist = sqrt(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	bool IsZero()
	{
		return 0.f == x && 0.f == y;
	}
};

// ���� ����ü
struct tLine
{
	Vec2 v1;	// ������ �� 1
	Vec2 v2;	// ������ �� 2
	Vec2 vGradient;		// ������ ���� ���� ǥ����
	float fGradient;	// ������ ����
	float fYIntercept;	// y ����

	bool bIsX;
	bool bIsY;

public:
	tLine()	:
		v1{},
		v2{},
		vGradient{},
		fGradient(0.f),
		fYIntercept(0.f),
		bIsX(false),
		bIsY(false)
	{
	}

	tLine(Vec2 _v1, Vec2 _v2)	:
		v1(_v1),
		v2(_v2),
		vGradient{},
		fGradient(0.f),
		fYIntercept(0.f),
		bIsX(false),
		bIsY(false)
	{
		// x = a ������ ��
		if (v1.x == v2.x && v1.y != v2.y)
		{
			vGradient = Vec2(0.f, 1.f);
			bIsX = true;
			fYIntercept = v1.x;
		}
		// y = b ������ ��
		else if (v1.x != v2.x && v1.y == v2.y)
		{
			vGradient = Vec2(1.f, 0.f);
			bIsY = true;
			fYIntercept = v1.y;
		}
		else if (v1 != v2)
		{
			Vec2 Gradient = v1 - v2;
			Gradient.Normalize();
			vGradient = Gradient;
			fGradient = vGradient.y / vGradient.x;
			fYIntercept = -(fGradient * v1.x) + v1.y;
		}
	}

public:
	Vec2 MeetPoint(tLine _Other)
	{	
		Vec2 vResult = {};

		// x = a �����ľ˶�
		if (bIsX)
		{
			if (_Other.bIsY)
			{
				vResult.x = fYIntercept;
				vResult.y = _Other.fYIntercept;
				return vResult;
			}

			vResult.x = fYIntercept;
			vResult.y = _Other.fGradient * fYIntercept + _Other.fYIntercept;
			return vResult;
		}
		// y = b �������϶�
		if (bIsY)
		{
			if (_Other.bIsX)
			{
				vResult.x = _Other.fYIntercept;
				vResult.y = fYIntercept;
				return vResult;
			}

			vResult.x = (fYIntercept - _Other.fYIntercept) / _Other.fGradient;
			vResult.y = fYIntercept;
			return vResult;
		}

		vResult.x = (-fYIntercept + _Other.fYIntercept) / (fGradient - _Other.fGradient);
		vResult.y = (fGradient * _Other.fYIntercept - _Other.fGradient * fYIntercept) / (fGradient - _Other.fGradient);
		return vResult;
	}

	float GetPoint(float _x)
	{
		return _x * fGradient + fYIntercept;
	}
};

struct tEvent
{
	EEVENT_TYPE eType;
	DWORD_PTR wParam;
	DWORD_PTR lParam;
};

struct tAnimFrm
{
	Vec2 vLeftTop;	// �̹��� ������ �������� �»�� ��ġ
	Vec2 vSize;		// ������ ������
	Vec2 vOffset;	// �߰� �̵�
	float fDuration; // �ش� ������ ���� �ð�
};

struct tPlayerInfo
{
	int m_iHP;
	UINT m_iMaxHP;

	int m_iMP;
	UINT m_iMaxMP;

	UINT m_iHeart;

	UINT m_iStr;	// ���ݷ� ����
	UINT m_iCon;	// ���� ����
	UINT m_iInt;	// ���� ���ݷ� ����

	float m_fSpeed;
};

struct tMonsterInfo
{
	int m_iHP;
	UINT m_iMaxHP;

	UINT m_iAtk;
	UINT m_iDef;

	float m_fPatrolSpeed;
	float m_fTraceSpeed;
	float m_fDetectRange;	// Ž�� ����
	float m_fAttackRange;	// ���� ����
	float m_fDodgeRange;	// �ڷ� ������ ����
	float m_fAttackTime;
};

struct tSpawnPointInfo
{
	ESPAWNABLE_OBJECT m_eOption;	// ������ų ������Ʈ
	int m_iDir;	// �ٶ󺸴� ����(1 : ������ / -1 : ����)
};

struct tWeaponInfo
{
	UINT m_iStr;
	UINT m_iCon;
	UINT m_iInt;

	float m_fAtkSpeed;
};