#include "pch.h"
#include "CMPBar.h"

#include "CObjMgr.h"

#include "CPlayer.h"

#include "CTexture.h"

CMPBar::CMPBar()	:
	m_fRatio(1.f)
{
}

CMPBar::~CMPBar()
{
}

void CMPBar::Tick()
{
	CPlayer* pPlayer = (CPlayer*)CObjMgr::GetInst()->FindObj(L"Player");
	UINT MPMax = pPlayer->GetPlayerInfo().m_iMaxMP;
	int MP = pPlayer->GetPlayerInfo().m_iMP;

	m_fRatio = (float)MP / (float)MPMax;

	CUI::Tick();
}

void CMPBar::Render(HDC _DC)
{
	if (nullptr == GetIdleTex())
		return;

	Vec2 vPos = GetFinalPos();

	TransparentBlt(_DC,
		(int)vPos.x, (int)vPos.y,
		(int)(GetIdleTex()->GetWidth() * m_fRatio),
		GetIdleTex()->GetHeight(),
		GetIdleTex()->GetDC(),
		0, 0,
		(int)(GetIdleTex()->GetWidth() * m_fRatio),
		GetIdleTex()->GetHeight(),
		RGB(255, 0, 255));
}
