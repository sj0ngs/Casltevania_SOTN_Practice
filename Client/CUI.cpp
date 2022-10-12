#include "pch.h"
#include "CUI.h"

#include "CEngine.h"

CUI::CUI()
{
}

CUI::~CUI()
{
}

void CUI::Tick()
{
}

void CUI::Render()
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(_DC, 
		(int)vPos.x, 
		(int)vPos.y, 
		(int)(vPos.x + vScale),
		(int)(vPos.y + vScale));

	// ���� �Ұ� �귯���� �������´�
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}

