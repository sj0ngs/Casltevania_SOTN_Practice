#include "pch.h"
#include "CUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"


CUI::CUI()	:
	m_bLbtnDown(false),
	m_bMouseOn(false),
	m_bCmrAfctd(false)
{
}

CUI::~CUI()
{
}

void CUI::Tick()
{
	// 마우스 온 체크
	MouseOnCheck();
}

void CUI::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC 의 기존 팬과 브러쉬를 새로 가져온것들로 대체한다
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = GetPos();
	// 카메라에 영향을 받으면(몬스터 HP 등) 랜더 포즈로 변환
	if (m_bCmrAfctd)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	Vec2 vScale = GetScale();

	Rectangle(_DC, 
		(int)vPos.x, 
		(int)vPos.y, 
		(int)(vPos.x + vScale.x),
		(int)(vPos.y + vScale.y));

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}

void CUI::MouseOnCheck()
{
	Vec2 vPos = GetPos();
	if (m_bCmrAfctd)
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;

	// 마우스가 UI의 영역안에 있다
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
		m_bMouseOn = true;
	else
		m_bMouseOn = false;
}

