#include "pch.h"
#include "CLine.h"

#include "CEngine.h"

#include "CLevelMgr.h"

#include "CPlayer.h"

#include "CRigidBody.h"

CLine::CLine()	:
	m_vPos1{},
	m_vPos2{},
	m_iOverlapCount(0),
	m_eType(ELINE_TYPE::UP)
{
}

CLine::CLine(const CLine& _Other)	:
	m_vPos1(_Other.m_vPos1),
	m_vPos2(_Other.m_vPos2),
	m_iOverlapCount(0)
{
}

CLine::~CLine()
{
}

void CLine::Tick()
{
	Vec2 vPos = GetPos();
	Vec2 vLength = GetScale() / 2.f;
	vLength.y *= -1;

	m_vPos1 = vPos - vLength;
	m_vPos2 = vPos + vLength;
}

void CLine::Render(HDC _DC)
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
	
	Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(m_vPos1);
	Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(m_vPos2);

	MoveToEx(_DC, (int)vPos2.x, (int)vPos2.y, NULL);
	LineTo(_DC, (int)vPos1.x, (int)vPos1.y); 

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}

void CLine::BeginOverlap(CObj* _pOther)
{
	m_iOverlapCount++;
	
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	if (nullptr == pPlayer)
		return; 

   	pPlayer->GetRigidBody()->OnGround();
	pPlayer->GetRigidBody()->AddVelocity(Vec2(0.f, -100.f));
}

void CLine::OnOverlap(CObj* _pOther)
{
}

void CLine::EndOverlap(CObj* _pOther)
{
}
