#include "pch.h"
#include "CHUD.h"

#include "CResMgr.h"

#include "CTexture.h"

CHUD::CHUD()
{
}

CHUD::~CHUD()
{
}

void CHUD::Tick()
{
	CUI::Tick();
}

void CHUD::Render(HDC _DC)
{
	if (nullptr == GetIdleTex())
		return;

	Vec2 vPos = GetFinalPos();

	TransparentBlt(_DC,
		(int)vPos.x, (int)vPos.y,
		GetIdleTex()->GetWidth(),
		GetIdleTex()->GetHeight(),
		GetIdleTex()->GetDC(),
		0, 0,
		GetIdleTex()->GetWidth(),
		GetIdleTex()->GetHeight(),
		RGB(255, 0, 255));

	Render_ChildUI(_DC);
}
