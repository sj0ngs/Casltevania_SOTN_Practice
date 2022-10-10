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
		// Force ���� Player�� ���ϴ� ����
		Vec2 vForceDir = vecPlayerLayer[i]->GetPos() - GetPos();
		float fDistance = vForceDir.Length();

		// Force ���� Player ������ �Ÿ�
		// �Ÿ��� ���� ���� �����ϰ� �پ��
		//float fRatio = 1.f - fDistance / m_fRadius;
		// �Ÿ��� ���� ���� �ڻ��� �Լ�ó�� �پ��
		float fRatio = cosf((fDistance / m_fRadius) * PI * 0.5f);
		Saturate(fRatio);
		// Force ���� �÷��̾ ���� �� ���� ũ��
		vForceDir.Normalize();
		vForceDir *= (m_fForce * fRatio);
		vecPlayerLayer[i]->GetRigidBody()->AddForce(vForceDir);
	}
}

void CForce::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Ellipse(_DC, 
		(int)(vPos.x - m_fRadius),
		(int)(vPos.y - m_fRadius),
		(int)(vPos.x + m_fRadius),
		(int)(vPos.y + m_fRadius));

	// ���� �Ұ� �귯���� �������´�
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);
}
