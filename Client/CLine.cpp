#include "pch.h"
#include "CLine.h"

#include "CEngine.h"

#include "CLevelMgr.h"
#include "CLevel.h"

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
	m_iOverlapCount(0),
	m_eType(ELINE_TYPE::UP)
{
}

CLine::~CLine()
{
}

void CLine::Tick()
{
}

void CLine::Render(HDC _DC)
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

	Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(m_vPos1);
	Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(m_vPos2);

	MoveToEx(_DC, (int)vPos2.x, (int)vPos2.y, NULL);
	LineTo(_DC, (int)vPos1.x, (int)vPos1.y); 

	// ���� �Ұ� �귯���� �������´�
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}

void CLine::BeginOverlap(CObj* _pOther)
{
	m_iOverlapCount++;

	tLine Line = { GetPos1(), GetPos2() };

	Vec2 vPos = _pOther->GetPos();
	vPos.y += _pOther->GetScale().y / 2.f;

	float y = Line.GetPoint(vPos.x);

	if (y >= vPos.y)
	{
		vPos.y = y;

		_pOther->SetPos(vPos);
		_pOther->GetRigidBody()->OnGround();
	}

	//CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	//if (nullptr == pPlayer)
	//	return; 

 //  	pPlayer->GetRigidBody()->OnGround();

	//tLine ObjLine = tLine(pPlayer->GetPos(), pPlayer->GetPrevPos());
	//tLine Line = tLine(GetPos1(), GetPos2());

	//Vec2 vMeetPoint = {};
	//ObjLine.MeetPoint(Line, vMeetPoint);

	//pPlayer->SetPos(vMeetPoint);

	//Vec2 vGradient = Line.vGradient;

	//if (0 > vGradient.x)
	//{
	//	vGradient *= -1.f;
	//}

	//pPlayer->SetDir(vGradient);
}

void CLine::OnOverlap(CObj* _pOther)
{
}

void CLine::EndOverlap(CObj* _pOther)
{
	m_iOverlapCount--; 

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	if (nullptr == pPlayer)
		return;

	pPlayer->GetRigidBody()->OffGround();
	pPlayer->SetDir(Vec2(1.f, 0.f));
}
