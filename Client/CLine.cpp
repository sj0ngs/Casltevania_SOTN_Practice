#include "pch.h"
#include "CLine.h"

#include "CEngine.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAI.h"

#include "CState.h"

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
	tLine tLine{ m_vPos1, m_vPos2 };
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

	Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(m_vPos1);
	Vec2 vPos2 = CCamera::GetInst()->GetRenderPos(m_vPos2);

	MoveToEx(_DC, (int)vPos2.x, (int)vPos2.y, NULL);
	LineTo(_DC, (int)vPos1.x, (int)vPos1.y); 

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);

	Vec2 vPos = vPos1 + vPos2;
	vPos /= 2.f;

	wstring strName;
	switch (m_eType)
	{
	case ELINE_TYPE::UP:
		strName = L"Up Line";
		break;
	case ELINE_TYPE::DOWN:
		strName = L"Down Line";
		break;
	}

	TextOut(_DC, (int)vPos.x, (int)vPos.y, strName.c_str(), (int)strName.length());
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
		{
			if (pPlayer->IsHit())
			{
				Vec2 vVelocity = pPlayer->GetRigidBody()->GetVelocity();
				vVelocity.y = 0.f;
				pPlayer->GetRigidBody()->SetVelocity(vVelocity);
			}
			else
				pPlayer->GetAI()->GetCurState()->ChangeState(L"Fall");
		}
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

void CLine::Save(FILE* _pFile)
{
	fwrite(&m_vPos1, sizeof(Vec2), 1, _pFile);
	fwrite(&m_vPos2, sizeof(Vec2), 1, _pFile);
	fwrite(&m_eType, sizeof(ELINE_TYPE), 1, _pFile);
}

void CLine::Load(FILE* _pFile)
{
	fread(&m_vPos1, sizeof(Vec2), 1, _pFile);
	fread(&m_vPos2, sizeof(Vec2), 1, _pFile);
	fread(&m_eType, sizeof(ELINE_TYPE), 1, _pFile);
}
