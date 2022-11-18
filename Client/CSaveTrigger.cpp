#include "pch.h"
#include "CSaveTrigger.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"


#include "CCollider.h"

#include "CPlayer.h"
#include "CParticle.h"

#include "CSound.h"

CSaveTrigger::CSaveTrigger()	:
	m_bReleased(false)
{
}

CSaveTrigger::~CSaveTrigger()
{
}

void CSaveTrigger::Render(HDC _DC)
{
	CTrigger::Render(_DC);
}

void CSaveTrigger::BeginOverlap(CCollider* _pOther)
{
}

void CSaveTrigger::OnOverlap(CCollider* _pOther)
{
	if (!m_bReleased)
	{
		CObj* pObj = _pOther->GetOwner();

		if (ELAYER::PLAYER == pObj->GetLayer())
		{
			if (IS_PRESSED(EKEY::UP))
			{
				ReleaseParticle();
			}
		}
	}
}

void CSaveTrigger::EndOverlap(CCollider* _pOther)
{
}

void CSaveTrigger::AddParticle(CParticle* _pParticle)
{
	if (nullptr != _pParticle)
	{
		m_vecParticle.push_back(_pParticle);
	}
}

void CSaveTrigger::ReleaseParticle()
{
	vector<CParticle*>::iterator iter = m_vecParticle.begin();
	vector<CParticle*>::iterator iterEnd = m_vecParticle.end();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	for (; iter != iterEnd; iter++)
	{
		CParticle* pParticle = *iter;

		pParticle->SetTarget(pPlayer);
	}

	m_vecParticle.clear();

	pPlayer->Heal();

	PLAY_SOUND(L"GETMEAT");

	m_bReleased = true;
}
