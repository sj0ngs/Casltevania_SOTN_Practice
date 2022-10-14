#include "pch.h"
#include "CLineCollider.h"

#include "CEngine.h"

#include "CObj.h"

CLineCollider::CLineCollider(CObj* _pOwner)	:
	CCollider(_pOwner),
	m_vPos1{},
	m_vPos2{}
{
	SetColliderType(ECOLLIDER_TYPE::LINE);
}

CLineCollider::~CLineCollider()
{
}

void CLineCollider::Render(HDC _DC)
{
	// 충돌체를 그린다
	HPEN hPen = nullptr;

	if (0 < GetOverlapCount())
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::RED);
	else
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC 의 기존 팬과 브러쉬를 새로 가져온것들로 대체한다
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetFinalPos());
	Vec2 vLength = GetOwner()->GetScale() / 2.f;

	m_vPos1 = vPos + vLength;
	m_vPos2 = vPos - vLength;

	MoveToEx(_DC, (int)m_vPos1.x, (int)m_vPos1.y, NULL);

	LineTo(_DC, (int)m_vPos2.x, (int)m_vPos2.y);

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}