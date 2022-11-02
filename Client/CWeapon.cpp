#include "pch.h"
#include "CWeapon.h"

#include "CLevelMgr.h"
#include "CAnimator.h"

#include "CLevel.h"
#include "CEffect.h"
#include "CAnimation.h"

#include "CPlayer.h"

CWeapon::CWeapon() :
	m_tInfo{},
	m_pOwner(nullptr),
	m_pSword(nullptr),
	m_pEffect(nullptr)
{
}

CWeapon::CWeapon(const CWeapon& _pOrigin)	:
	CObj(_pOrigin),
	m_tInfo(_pOrigin.m_tInfo),
	m_strSwordRight(_pOrigin.m_strSwordRight),
	m_strSwordLeft(_pOrigin.m_strSwordLeft),
	m_strJumpSwordRight(_pOrigin.m_strJumpSwordRight),
	m_strJumpSwordLeft(_pOrigin.m_strJumpSwordLeft),
	m_strEffectRight(_pOrigin.m_strEffectRight),
	m_strEffectLeft(_pOrigin.m_strEffectLeft),
	m_strJumpEffectRight(_pOrigin.m_strJumpEffectRight),
	m_strJumpEffectLeft(_pOrigin.m_strJumpEffectLeft),
	m_pOwner(nullptr),
	m_pSword(nullptr),
	m_pEffect(nullptr)
{
}

CWeapon::~CWeapon()	
{
}

void CWeapon::Tick()
{
	if (nullptr == m_pOwner)
		return;

	Vec2 vPos = m_pOwner->GetPos();

	if (EPLAYER_STATE::DUCK == m_pOwner->GetPlayerState())
	{
		vPos.y += 70.f;
	}

	if (nullptr != m_pSword && !m_pSword->IsDead())
	{
		m_pSword->SetPos(vPos);
	}
	if (nullptr != m_pEffect && !m_pEffect->IsDead())
	{
		m_pEffect->SetPos(vPos);
	}
}

void CWeapon::Attack(bool _bDir)
{
	assert(m_pOwner);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	m_pEffect = new CEffect;
	m_pSword = new CEffect;

	wstring strSword;
	wstring strEffect;

	switch (m_pOwner->GetPlayerState())
	{
	case EPLAYER_STATE::STAND:
	case EPLAYER_STATE::DUCK:
	{
		if (_bDir)
		{
			strSword = strPath + m_strSwordRight;
			strEffect = strPath + m_strEffectRight;
		}
		else
		{
			strSword = strPath + m_strSwordLeft;
			strEffect = strPath + m_strEffectLeft;
		}
	}
		break;
	case EPLAYER_STATE::AIR:
	{
		if (_bDir)
		{
			strSword = strPath + m_strJumpSwordRight;
			strEffect = strPath + m_strJumpEffectRight;
		}
		else
		{
			strSword = strPath + m_strJumpSwordLeft;
			strEffect = strPath + m_strJumpEffectLeft;
		}
	}
		break;
	}

	Vec2 vPos = m_pOwner->GetPos();
	
	CAnimation* pAnim = m_pEffect->GetAnimator()->LoadAnimation(strEffect);
	m_pEffect->GetAnimator()->Play(pAnim->GetName(), false);
	pAnim = m_pSword->GetAnimator()->LoadAnimation(strSword);
	m_pSword->GetAnimator()->Play(pAnim->GetName(), false);

	Instantiate(m_pEffect, vPos, ELAYER::EFFECT);
	Instantiate(m_pSword, vPos, ELAYER::EFFECT);
}

void CWeapon::AttackEnd()
{
	if (IsValid((CObj*&)m_pSword))
	{
		m_pSword->SetDead();
	}
	if (IsValid((CObj*&)m_pEffect))
	{
		m_pEffect->SetDead();
	}
}
