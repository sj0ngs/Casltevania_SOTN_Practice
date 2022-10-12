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
	// ���콺 �� üũ
	MouseOnCheck();
}

void CUI::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = GetPos();
	// ī�޶� ������ ������(���� HP ��) ���� ����� ��ȯ
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

	// ���� �Ұ� �귯���� �������´�
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

	// ���콺�� UI�� �����ȿ� �ִ�
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
		m_bMouseOn = true;
	else
		m_bMouseOn = false;
}

