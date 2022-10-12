#include "pch.h"
#include "CCollider.h"

#include "CEngine.h"

#include "CObj.h"

CCollider::CCollider(CObj* _pOwner)	:
	CComponent(_pOwner),
	m_vOffsetPos{},
	m_vFinalPos{},
	m_vScale{},
	m_iOverlapCount(0)
{
}

CCollider::CCollider(const CCollider& _Other)	:
	CComponent(nullptr),
	m_vOffsetPos(_Other.m_vOffsetPos),
	m_vScale(_Other.m_vScale),
	m_iOverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::Tick()
{
	// 중첩횟수가 음수인 경우 프로그램 중단
	assert(!(m_iOverlapCount < 0));
}

void CCollider::Final_Tick()
{
	// 충돌체의 최종 위치값을 결정한다
	m_vFinalPos = GetOwner()->GetPos() + GetOffsetPos();
}

void CCollider::Render(HDC _DC)
{
	// 충돌체를 그린다
	HPEN hPen = nullptr;

	if (0 < m_iOverlapCount)
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::RED);
	else
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC 의 기존 팬과 브러쉬를 새로 가져온것들로 대체한다
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetFinalPos());
	Vec2 vScale = GetScale();

	Rectangle(_DC, (int)(vPos.x - vScale.x / 2),
					(int)(vPos.y - vScale.y / 2),
					(int)(vPos.x + vScale.x / 2),
					(int)(vPos.y + vScale.y / 2));

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);

	// 만들어 사용한 팬을 제거한다
	//DeleteObject(hGreenPen);
}

void CCollider::BeginOverlap(CCollider* _pOther)
{
	++m_iOverlapCount;

	GetOwner()->BeginOverlap(_pOther);
}

void CCollider::OnOverlap(CCollider* _pOther)
{
	GetOwner()->OnOverlap(_pOther);
}

void CCollider::EndOverlap(CCollider* _pOther)
{
	--m_iOverlapCount;

	GetOwner()->EndOverlap(_pOther);
}
