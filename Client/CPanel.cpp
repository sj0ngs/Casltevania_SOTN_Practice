#include "pch.h"
#include "CPanel.h"

#include "CKeyMgr.h"

#include "CTexture.h"

CPanel::CPanel()	:
	m_vLeftRightPadding{},
	m_vTopBottomPadding{},
	m_vInnerPadding{},
	m_vPressPos{}
{
}

CPanel::~CPanel()
{
}

void CPanel::Tick()
{
	if (IsLbtnDown())
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;

		Vec2 vPos = GetPos();
		vPos += vMove;
		SetPos(vPos);

		m_vPressPos = MOUSE_POS;
	}

	CUI::Tick();
}

void CPanel::Render(HDC _DC)
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

void CPanel::MouseLbtnDown()
{
	CUI::MouseLbtnDown();

	m_vPressPos = MOUSE_POS;
}
