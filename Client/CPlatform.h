#pragma once
#include "CObj.h"

enum class EPLATFORM_STATUS
{
	NONE,
	UP,
	LEFT,
	RIGHT,
	DOWN
};

enum class EPLATFORM_TYPE
{
	FLOOR,
	PLATFORM
};

class CPlayer;

class CPlatform	:
	public CObj
{
private:
	tLine m_UpLine;
	tLine m_DownLine;
	tLine m_LeftLine;
	tLine m_RightLine;

	Vec2 m_vLeftTop;
	Vec2 m_vRightTop;
	Vec2 m_vLeftDown;
	Vec2 m_vRightDown;

	map<UINT, EPLATFORM_STATUS> m_mapPlatformStatus;

	EPLATFORM_TYPE m_eType;

public:
	void SetType(EPLATFORM_TYPE _eType) { m_eType = _eType; }

public:
	CLONE(CPlatform);

public:
	CPlatform();
	CPlatform(const CPlatform& _Origin);
	~CPlatform();

public:
	virtual void Render(HDC _DC) override;

public:
	virtual void BeginOverlap(CCollider* _pOther)	override;
	virtual void OnOverlap(CCollider* _pOther)	override;
	virtual void EndOverlap(CCollider* _pOther)	override;

private:
	void SetPoint();
	bool UpCheck(CObj* _pObj);
	bool DownCheck(CObj* _pObj);
	void LeftCheck(CObj* _pObj);
	void RightCheck(CObj* _pObj);

public:
	virtual void Save(FILE* _pFile) override;
	virtual void Load(FILE* _pFile) override;
};
