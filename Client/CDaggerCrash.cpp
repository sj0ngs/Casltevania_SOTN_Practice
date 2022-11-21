#include "pch.h"
#include "CDaggerCrash.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"

#include "CPlayer.h"

#include "CDagger.h"

#include "CAnimDebug.h"

#include "CSound.h"

CDaggerCrash::CDaggerCrash()	:
	m_faccTime(0.f),
	m_bGateOpen(false),
	m_iSpawnCount(0),
	m_arrGate{},
	m_pOwner(nullptr),
	m_iDmg(0)
{
}

CDaggerCrash::~CDaggerCrash()
{
	for (int i = 0; i < 4; i++)
	{
		m_arrGate[i]->SetDead();
	}
}

void CDaggerCrash::Tick()
{
	//CObj::Tick();

	m_faccTime += DELTATIME;

	if (!m_bGateOpen)
	{
		if (0.2f <= m_faccTime)
		{
			CreateGate();

			m_faccTime = 0.f;

			if (4 <= ++m_iSpawnCount)
			{
				m_iSpawnCount = 0;
				m_bGateOpen = true;
			}
		}
	}
	else
	{
		if (0.05f <= m_faccTime)
		{
			ShootDagger();

			m_faccTime = 0.f;
			if (100 <= ++m_iSpawnCount)
			{
				SetDead();
				
				if (IsValid((CObj*&)m_pOwner))
				{
					m_pOwner->SetOnCrash(false);
				}
			}
		}
	}

}

void CDaggerCrash::CreateGate()
{
	Vec2 vPos = GetPos();

	CAnimDebug* pGate = new CAnimDebug;
	pGate->GetCollider()->SetScale(Vec2(0.f, 0.f));

	if (GetFaceDir())
	{
		pGate->GetAnimator()->LoadAnimation(L"animation\\Weapon\\DAGGER_GATE_RIGHT.anim");
	}
	else
	{
		pGate->GetAnimator()->LoadAnimation(L"animation\\Weapon\\DAGGER_GATE_LEFT.anim");
	}

	pGate->GetAnimator()->Play(false);

	switch (m_iSpawnCount)
	{
	case 0:
	{
		vPos.y -= 70.f;
	}
		break;
	case 1:
	{
		vPos.x -= 30.f;
		vPos.y -= 25.f;
	}
		break;
	case 2:
	{
		vPos.x += 30.f;
		vPos.y += 25.f;
	}
		break;
	case 3:
	{
		vPos.y += 70.f;
	}
		break;
	}

	Instantiate(pGate, vPos, ELAYER::EFFECT);
	m_arrGate[m_iSpawnCount] = pGate;
}

void CDaggerCrash::ShootDagger()
{
	int iNumGate = m_iSpawnCount % 4;

	CDagger* pDagger = new CDagger;
	pDagger->SetFaceDir(GetFaceDir());
	pDagger->SetDamage(m_iDmg);

	Instantiate(pDagger, m_arrGate[iNumGate]->GetPos(), ELAYER::PLAYER_PROJECTILE);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"KNIFE");
	pSound->Play();
	pSound->SetVolume(50.f);
}
