#include "pch.h"
#include "CAxeCrash.h"

#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CSprialAxe.h"

#include "CPlayer.h"

#include "CSound.h"

CAxeCrash::CAxeCrash() :
	m_faccTime(0.f),
	m_bRotEnd(false),
	m_pOwner(nullptr),
	m_iDmg(0),
	m_bIsReleased(false)
{
}

CAxeCrash::~CAxeCrash()
{
}

void CAxeCrash::Init()
{
	float fAngle = 0.f;

	for (int i = 0; i < 8; i++)
	{
		CSprialAxe* pAxe = new CSprialAxe;

		Vec2 vPos = {};
		vPos = GetPos();
		fAngle -= 360.f / 8.f;
		pAxe->SetAngle(fAngle);
		pAxe->SetCenter(vPos);
		pAxe->GetAnimator()->GetCurAnimation()->SetCurFrame(i);
		pAxe->SetDamage(m_iDmg);
		Instantiate(pAxe, vPos, ELAYER::PLAYER_PROJECTILE);

		m_vecAxe.push_back(pAxe);
	}
}


void CAxeCrash::Tick()
{
	CObj::Tick();

	if (!m_bIsReleased)
	{
		if (1.5f <= m_faccTime)
		{
			ReleaseAxe();
			m_bIsReleased = true;
			m_faccTime = 0.f;
		}
	}
	else
	{
		if (1.5f <= m_faccTime)
		{
			if (IsValid((CObj*&)m_pOwner))
			{
				m_pOwner->SetOnCrash(false);
			}
			SetDead();
		}
	}

	m_faccTime += DELTATIME;
}

void CAxeCrash::ReleaseAxe()
{
	for (size_t i = 0; i < m_vecAxe.size(); i++)
	{
		if (IsValid((CObj*&)m_vecAxe[i]))
		{
			m_vecAxe[i]->SetOnThrow(true);
			m_vecAxe[i]->GetCollider()->SetScale(Vec2(100.f, 100.f));
		}
	}

	CSound* pSound = CResMgr::GetInst()->FindSound(L"ONO");
	pSound->Play();
	pSound->SetVolume(50.f);
}
