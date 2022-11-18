#include "pch.h"
#include "CBibleCrash.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CPlayer.h"

#include "CEffect.h"
#include "CTexture.h"

#include "CSound.h"

CBibleCrash::CBibleCrash()	:
	m_pOwner(nullptr),
	m_pEffect(nullptr),
	m_bOnCollider(false),
	m_faccTime(0.f),
	m_bHit(false)
{
	//CTexture* pTex = CResMgr::GetInst()->FindTexture(L"Item_Crash_Bible_Left");
	//GetAnimator()->CreateAnimation(L"Bible_Crash_Left", pTex, Vec2(0.f, 0.f), Vec2(868.f, 444.f), 14, 0.02f, 14);

	//pTex = CResMgr::GetInst()->FindTexture(L"Item_Crash_Bible_Right");
	//GetAnimator()->CreateAnimation(L"Bible_Crash_Right", pTex, Vec2(pTex->GetWidth() - 868.f, 0.f), Vec2(-868.f, 444.f), 14, 0.02f, 14);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"Bible_Crash_Left");
	//pAnim->Save(L"animation\\Weapon\\BIBLE_CRASH_LEFT.anim");

	//pAnim = GetAnimator()->FindAnimation(L"Bible_Crash_Right");
	//pAnim->Save(L"animation\\Weapon\\BIBLE_CRASH_RIGHT.anim");

	GetCollider()->SetScale(Vec2(0.f, 0.f));
}

CBibleCrash::~CBibleCrash()
{
}

void CBibleCrash::SetOwner(CPlayer* _pOwner)
{
	m_pOwner = _pOwner;
	m_pEffect = new CEffect;

	if (_pOwner->GetFaceDir())
	{
		m_pEffect->GetAnimator()->LoadAnimation(L"animation\\Weapon\\BIBLE_CRASH_RIGHT.anim");

	}
	else
	{
		m_pEffect->GetAnimator()->LoadAnimation(L"animation\\Weapon\\BIBLE_CRASH_LEFT.anim");
	}

	m_pEffect->GetAnimator()->Play(false);
	Instantiate(m_pEffect, GetPos(), ELAYER::EFFECT);
}

void CBibleCrash::Tick()
{
	CObj::Tick();

	if (IsValid((CObj*&)m_pEffect))
	{
		if (!m_bOnCollider)
		{
			if (140 == m_pEffect->GetAnimator()->GetCurAnimation()->GetCurFrame())
			{
				GetCollider()->SetScale(Vec2(750.f, 360.f));
				m_bOnCollider = true;

				CSound* pSound = CResMgr::GetInst()->FindSound(L"BOSSEYE_BEAM");
				pSound->Play(false);
			}
		}
		else
		{
			m_faccTime += DELTATIME;

			if (m_bHit)
			{
				m_bHit = false;
				GetCollider()->SetScale(Vec2(750.f, 360.f));
			}
			else
			{
				if (0.4f <= m_faccTime)
				{
					m_bHit = true;
					GetCollider()->SetScale(Vec2(0.f, 0.f));
					m_faccTime = 0.f;
				}
			}
			if (m_pEffect->GetAnimator()->GetCurAnimation()->IsFinish())
			{
				if (IsValid((CObj*&)m_pOwner))
				{
					m_pOwner->SetOnCrash(false);
				}
				SetDead();
			}
		}
	}
}

void CBibleCrash::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CBibleCrash::BeginOverlap(CCollider* _pOther)
{
}
