#include "pch.h"
#include "CLine.h"

#include "CEngine.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRigidBody.h"

CLine::CLine()	:
	m_vPos1{},
	m_vPos2{},
	m_iOverlapCount(0),
	m_eType(ELINE_TYPE::UP),
	m_tLine{}
{
}

CLine::CLine(const CLine& _Other)	:
	m_vPos1(_Other.m_vPos1),
	m_vPos2(_Other.m_vPos2),
	m_iOverlapCount(0),
	m_eType(_Other.m_eType),
	m_tLine{}
{
}

CLine::~CLine()
{
}

void CLine::Tick()
{
	tLine tLine{ GetPos1(), GetPos2() };
	m_tLine = tLine;
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

	if (ELINE_TYPE::UP == m_eType)
	{
		_pOther->GetRigidBody()->OnGround();

		Vec2 vPos = _pOther->GetPos();

		vPos.y = m_tLine.GetPoint(vPos.x);

		_pOther->SetPos(vPos);

		Vec2 Gradient = m_tLine.vGradient;
		if (0.f > Gradient.x)
			Gradient *= -1.f;

		_pOther->SetDir(Gradient);
	}
	else
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

		if (nullptr != pPlayer)
			pPlayer->EndJump();
	}
}

void CLine::OnOverlap(CObj* _pOther)
{

}

void CLine::EndOverlap(CObj* _pOther)
{
	m_iOverlapCount--; 

	if (ELINE_TYPE::UP == m_eType)
	{
		_pOther->GetRigidBody()->OffGround();
		_pOther->SetDir(Vec2(1.f, 0.f));
	}
}
