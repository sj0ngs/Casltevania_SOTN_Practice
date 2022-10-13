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

	// 플랫폼 스테이터스 벡터 때문에 복사 생성자 따로 만들어 줘야함
public:
	CLONE(CPlatform);

public:
	CPlatform();
	~CPlatform();

public:
	virtual void BeginOverlap(CCollider* _pOther)	override;
	virtual void OnOverlap(CCollider* _pOther)	override;
	virtual void EndOverlap(CCollider* _pOther)	override;

private:
	void SetPoint();
	bool UpCheck(CPlayer* _pPlayer);
	bool DownCheck(CPlayer* _pPlayer);
	void LeftCheck(CPlayer* _pPlayer);
	void RightCheck(CPlayer* _pPlayer);
};

