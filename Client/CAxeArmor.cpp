#include "pch.h"
#include "CAxeArmor.h"

#include "CResMgr.h"
#include "CLevelMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CDeadState.h"

#include "CMonsterAttack.h"
#include "CMonsterAxe.h"

#include "CPlayer.h"
#include "CEffect.h"
#include "CLevel.h"

#include "CSound.h"

CAxeArmor::CAxeArmor()	:
	m_bAttackEnd(false),
	m_eState(EAXE_ARMOR_ATTACK::NONE)
{
	GetCollider()->SetScale(Vec2(50.f, 200.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -100.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_IDLE_RIGHT.anim");
													   
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_WALK_RIGHT.anim");
													   
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_HIGH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_HIGH_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_MIDDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_MIDDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_LOW_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_LOW_RIGHT.anim");

	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->ChangeState(L"Idle");
}

CAxeArmor::~CAxeArmor()
{
}

void CAxeArmor::Tick()
{
	CMonster::Tick();

	if (IsAttack())
	{
		m_faccAttackTime += DELTATIME;

		if (EAXE_ARMOR_ATTACK::SLASH == m_eState)
		{
			UINT iCurFrm = GetAnimator()->GetCurAnimation()->GetCurFrame();

			if (1 <= iCurFrm && 2 >= iCurFrm)
			{
				Vec2 vPos = GetPos();
				if (GetFaceDir())
				{
					vPos.x += GetMonsterInfo().m_fTraceSpeed * 10.f * DELTATIME;
				}
				else
				{
					vPos.x -= GetMonsterInfo().m_fTraceSpeed * 10.f * DELTATIME;
				}
				SetPos(vPos);
			}

			if (!m_bAttackEnd && 4 == GetAnimator()->GetCurAnimation()->GetCurFrame())
			{
				Slash();
				m_bAttackEnd = true;
			}

			if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
			{
				SetOnAttack(false);
				m_faccAttackTime = 0.f;
				m_bAttackEnd = false;
			}
		}
		else
		{
			if (!m_bAttackEnd && 0.5 <= m_faccAttackTime)
			{
				Throw();
				m_bAttackEnd = true;
			}

			if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
			{
				SetOnAttack(false);
				m_faccAttackTime = 0.f;
				m_bAttackEnd = false;
			}
		}
	}
}

void CAxeArmor::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CAxeArmor::Idle()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Axe_Armor_Idle_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Axe_Armor_Idle_Left", true);
	}
}

void CAxeArmor::Walk()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Axe_Armor_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Axe_Armor_Walk_Left", true);
	}
}

void CAxeArmor::Turn()
{
	CMonster::Turn();

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Axe_Armor_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Axe_Armor_Walk_Left", true);
	}
}


void CAxeArmor::Attack()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	Vec2 vDir = GetPos() - pPlayer->GetPos();

	if (250.f <= vDir.Length())
	{
		EPLAYER_STATE ePlayerState = pPlayer->GetPlayerState();

		switch (ePlayerState)
		{
		case EPLAYER_STATE::STAND:
		{
			m_eState = EAXE_ARMOR_ATTACK::THROW_MIDDLE;
			if (GetFaceDir())
			{
				GetAnimator()->Play(L"Axe_Armor_Middle_Right", false);
			}
			else
			{
				GetAnimator()->Play(L"Axe_Armor_Middle_Left", false);
			}
		}
		break;
		case EPLAYER_STATE::DUCK:
		{
			m_eState = EAXE_ARMOR_ATTACK::THROW_LOW;
			if (GetFaceDir())
			{
				GetAnimator()->Play(L"Axe_Armor_Low_Right", false);
			}
			else
			{
				GetAnimator()->Play(L"Axe_Armor_Low_Left", false);
			}
		}
		break;
		case EPLAYER_STATE::HIT:
		case EPLAYER_STATE::AIR:
		{
			m_eState = EAXE_ARMOR_ATTACK::THROW_HIGH;
			if (GetFaceDir())
			{
				GetAnimator()->Play(L"Axe_Armor_High_Right", false);
			}
			else
			{
				GetAnimator()->Play(L"Axe_Armor_High_Left", false);
			}
		}
		break;
		}
	}
	else
	{
		m_eState = EAXE_ARMOR_ATTACK::SLASH;
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Axe_Armor_Attack_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Axe_Armor_Attack_Left", false);
		}
	}

	SetOnAttack(true);
}

void CAxeArmor::Dead()
{
	SetDead();

	CEffect* pEffect = new CEffect;

	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\AXE_ARMOR_DEATH_EFFECT.anim");
	pEffect->GetAnimator()->Play(false);
	
	Vec2 vPos = GetPos();
	vPos.y -= 100.f;

	Instantiate(pEffect, vPos, ELAYER::EFFECT);

	PLAY_SOUND(L"AXE_AMOR_DEAD");

	pSound = CResMgr::GetInst()->FindSound(L"DRACULA_FIRE");
	pSound->Play();
}

void CAxeArmor::Slash()
{
	CMonsterAttack* pAttack = new CMonsterAttack;

	pAttack->SetDamage(GetMonsterInfo().m_iAtk);
	pAttack->SetLifeSpan(0.5f);
	pAttack->GetCollider()->SetScale(Vec2(64.f, 64.f));

	Vec2 vPos = {};
	vPos.y -= 80.f;

	if (GetFaceDir())
	{
		vPos.x += (25.f + 32.f);
	}
	else
	{
		vPos.x -= (25.f + 32.f);
	}

	pAttack->GetCollider()->SetOffsetPos(vPos);

	Instantiate(pAttack, GetPos(), ELAYER::MONSTER_PROJECTILE);

	PLAY_SOUND(L"AXE_AMOR_ATK2");
}

void CAxeArmor::Throw()
{
	CMonsterAxe* pAxe = new CMonsterAxe;

	Vec2 vPos = GetPos();

	pAxe->SetDamage(GetMonsterInfo().m_iAtk);
	pAxe->SetFaceDir(GetFaceDir());

	if (GetFaceDir())
	{
		vPos.x += GetCollider()->GetScale().x / 2.f;
		pAxe->GetAnimator()->Play(L"Axe_Armor_Axe_Right", true);
	}
	else
	{
		vPos.x -= GetCollider()->GetScale().x / 2.f;
		pAxe->GetAnimator()->Play(L"Axe_Armor_Axe_Left", true);
	}

	switch (m_eState)
	{
	case EAXE_ARMOR_ATTACK::THROW_HIGH:
		vPos.y -= 250.f;
		break;
	case EAXE_ARMOR_ATTACK::THROW_MIDDLE:
		vPos.y -= 150.f;
		break;
	case EAXE_ARMOR_ATTACK::THROW_LOW:
		vPos.y -= 50.f;
		break;
	}

	Instantiate(pAxe, vPos, ELAYER::MONSTER_PROJECTILE);

	PLAY_SOUND(L"AXE_AMOR_ATK1");
}
