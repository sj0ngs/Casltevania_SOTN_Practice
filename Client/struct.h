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
	void Normalize()	// 벡터의 정규화
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

// 직선 구조체
struct tLine
{
	Vec2 v1;	// 지나는 점 1
	Vec2 v2;	// 지나는 점 2
	Vec2 vGradient;		// 직선의 기울기 벡터 표현식
	float fGradient;	// 직선의 기울기
	float fYIntercept;	// y 절편

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
		// x = a 직선일 때
		if (v1.x == v2.x && v1.y != v2.y)
		{
			vGradient = Vec2(0.f, 1.f);
			bIsX = true;
			fYIntercept = v1.x;
		}
		// y = b 직선일 때
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

		// x = a 방정식알때
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
		// y = b 방정식일때
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
	Vec2 vLeftTop;	// 이미지 내에서 프레임의 좌상단 위치
	Vec2 vSize;		// 프레임 사이즈
	Vec2 vOffset;	// 추가 이동
	float fDuration; // 해당 프레임 노출 시간
};

struct tPlayerInfo
{
	int m_iHP;
	UINT m_iMaxHP;

	int m_iMP;
	UINT m_iMaxMP;

	UINT m_iHeart;

	UINT m_iStr;	// 공격력 스탯
	UINT m_iCon;	// 방어력 스탯
	UINT m_iInt;	// 마법 공격력 스탯

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
	float m_fDetectRange;	// 탐색 범위
	float m_fAttackRange;	// 공격 범위
	float m_fDodgeRange;	// 뒤로 빠지는 범위
	float m_fAttackTime;
	float m_fAttackCoolTime; // 공격 쿨 타임
};

struct tSpawnPointInfo
{
	ESPAWNABLE_OBJECT m_eOption;	// 스폰시킬 오브젝트
	int m_iDir;	// 바라보는 방향(1 : 오른쪽 / -1 : 왼쪽)
};

struct tWeaponInfo
{
	UINT m_iStr;
	UINT m_iCon;
	UINT m_iInt;

	float m_fAtkSpeed;
};