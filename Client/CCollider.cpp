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
	// ��øȽ���� ������ ��� ���α׷� �ߴ�
	assert(!(m_iOverlapCount < 0));
}

void CCollider::Final_Tick()
{
	// �浹ü�� ���� ��ġ���� �����Ѵ�
	m_vFinalPos = GetOwner()->GetPos() + GetOffsetPos();
}

void CCollider::Render(HDC _DC)
{
	// �浹ü�� �׸���
	HPEN hPen = nullptr;

	if (0 < m_iOverlapCount)
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::RED);
	else
		hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetFinalPos());
	Vec2 vScale = GetScale();

	Rectangle(_DC, (int)(vPos.x - vScale.x / 2),
					(int)(vPos.y - vScale.y / 2),
					(int)(vPos.x + vScale.x / 2),
					(int)(vPos.y + vScale.y / 2));

	// ���� �Ұ� �귯���� �������´�
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);

	// ����� ����� ���� �����Ѵ�
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
