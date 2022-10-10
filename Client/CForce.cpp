#include "pch.h"
#include "CForce.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"

#include "CRigidBody.h"
#include "CLevel.h"

CForce::CForce()	:
	m_fAccTime(0.f),
	m_fLifeTime(0.f),
	m_fForce(0.f),
	m_fRadius(0.f)
{
}

CForce::~CForce()
{
}

void CForce::Tick()
{
	m_fAccTime += DELTATIME;

	if (m_fLifeTime < m_fAccTime)
	{
		SetDead();
		return;
	}

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecPlayerLayer = pCurLevel->GetLayer(ELAYER::PLAYER);

	for (size_t i = 0; i < vecPlayerLayer.size(); i++)
	{
		if (nullptr == vecPlayerLayer[i]->GetRigidBody())
			continue;
		// Force 에서 Player를 향하는 벡터
		Vec2 vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();
		float fDistance = vForceDir.Length();

		// Force 에서 Player 사이의 거리
		// 거리에 따라 힘이 일정하게 줄어듬
		//float fRatio = 1.f - fDistance / m_fRadius;
		// 거리에 따라 힘이 코사인 함수처럼 줄어듦
		float fRatio = cosf((fDistance / m_fRadius) * PI * 0.5f);
		Saturate(fRatio);
		// Force 에서 플레이어를 향해 줄 힘의 크기
		vForceDir.Normalize();
		vForceDir *= (m_fForce * fRatio);
		vecPlayerLayer[i]->GetRigidBody()->AddForce(vForceDir);
	}
}

void CForce::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	// DC 의 기존 팬과 브러쉬를 새로 가져온것들로 대체한다
	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Ellipse(_DC, 
		(int)(vPos.x - m_fRadius),
		(int)(vPos.y - m_fRadius),
		(int)(vPos.x + m_fRadius),
		(int)(vPos.y + m_fRadius));

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}
