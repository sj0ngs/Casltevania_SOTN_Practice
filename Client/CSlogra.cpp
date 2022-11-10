#include "pch.h"
#include "CSlogra.h"

#include "CTimeMgr.h"

#include "CAnimator.h"

#include "CSlograIdleState.h"
#include "CSlograMoveState.h"
#include "CSlograAttackState.h"
#include "CSlograHitState.h"
#include "CSlograFireState.h"
#include "CSlograStandBy.h"
#include "CSlograDropState.h"

#include "CProjectile.h"
#include "CMonsterAttack.h"
#include "CStraightProjectile.h"

#include "CEffect.h"

CSlogra::CSlogra()	:
	m_eState(ESLOGRA_STATE::SPEAR),
	m_bAttackEnd(false),
	m_faccAttackCool(0.f),
	m_bCanAttack(true),
	m_bCanFire(true),	
	m_bFireEnd(false),
	m_faccFireCool(0.f),
	m_bDeadSequence(false),
	m_faccDeathTime(0.f),
	m_faccDeathEffectSpawnTime(0.f),
	m_bIsHit(false),
	m_bIsCatch(false)
{
	GetCollider()->SetScale(Vec2(70.f, 220.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -110.f));

	GetRigidBody()->SetFriction(1000.f);
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(1500.f);
	GetRigidBody()->SetVelocityLimit(1000.f);

	// Spear
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_IDLE_RIGHT.anim");
								   		
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_MOVE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_MOVE_RIGHT.anim");
								   			 
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_HIT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_HIT_RIGHT.anim");
								   			
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_ATTACK_RIGHT.anim");
								   			
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_FIRE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_FIRE_RIGHT.anim");
								   		
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_DROP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_SPEAR_DROP_RIGHT.anim");
								   			
	// Beak						   			 
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_IDLE_RIGHT.anim");
								   			
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_MOVE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_MOVE_RIGHT.anim");
								   			 
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_HIT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_HIT_RIGHT.anim");
								   			
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_ATTACK_RIGHT.anim");
								   			
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_DROP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_BEAK_DROP_RIGHT.anim");
									
	GetAI()->AddState(L"SlograIdle", new CSlograIdleState);
	GetAI()->AddState(L"SlograMove", new CSlograMoveState);
	GetAI()->AddState(L"SlograAttack", new CSlograAttackState);
	GetAI()->AddState(L"SlograHit", new CSlograHitState);
	GetAI()->AddState(L"SlograFire", new CSlograFireState);
	GetAI()->AddState(L"SlograStandBy", new CSlograStandBy);
	GetAI()->AddState(L"SlograDrop", new CSlograDropState);
	GetAI()->ChangeState(L"SlograStandBy");
}

CSlogra::~CSlogra()
{
}

void CSlogra::Tick()
{
	if (!m_bDeadSequence)
	{
		CObj::Tick();

		if (IsAttack())
		{
			m_faccAttackTime += DELTATIME;

			switch (m_eState)
			{
			case ESLOGRA_STATE::SPEAR:
			{
				if (!m_bAttackEnd && 5 == GetAnimator()->GetCurAnimation()->GetCurFrame())
				{
					Sting();
					m_bAttackEnd = true;
				}

				if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
				{
					SetOnAttack(false);
					m_faccAttackTime = 0.f;
					m_bAttackEnd = false;
					m_bCanAttack = false;
				}
			}
			break;
			case ESLOGRA_STATE::BEAK:
			{
				if (!m_bAttackEnd && 5 == GetAnimator()->GetCurAnimation()->GetCurFrame())
				{
					Sting();
					m_bAttackEnd = true;
				}

				if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
				{
					SetOnAttack(false);
					m_faccAttackTime = 0.f;
					m_bAttackEnd = false;
					m_bCanAttack = false;
				}
			}
			break;
			}
		}

		if (!m_bCanAttack)
		{
			m_faccAttackCool += DELTATIME;

			if (SLOGRA_ATTACK_COOL <= m_faccAttackCool)
			{
				m_faccAttackCool = 0.f;
				m_bCanAttack = true;
			}
		}

		if (!m_bCanFire)
		{
			m_faccFireCool += DELTATIME;

			if (SLOGRA_FIRE_COOL <= m_faccFireCool)
			{
				m_faccFireCool = 0.f;
				m_bCanFire = true;
			}
		}
	}
	else
	{
		m_faccDeathTime += DELTATIME;
		m_faccDeathEffectSpawnTime += DELTATIME;

		if (3.f <= m_faccDeathTime)
		{
			SetDead();
			return;
		}

		if (0.1f <= m_faccDeathEffectSpawnTime)
		{
			DeathEffect();
			m_faccDeathEffectSpawnTime = 0.f;
		}
	}
}

void CSlogra::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CSlogra::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::PLAYER_PROJECTILE == pObj->GetLayer())
	{
		CProjectile* pProjectile = (CProjectile*)pObj;

		TakeDamage(pProjectile->GetDamage());

		if (GetAI()->FindState(L"SlograHit") != GetAI()->GetCurState() && 
			GetAI()->FindState(L"SlograDrop") != GetAI()->GetCurState())
		{
			GetAI()->ChangeState(L"SlograHit");
		}
	}
}

void CSlogra::Idle()
{
	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Spear_Idle_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Spear_Idle_Left", false);
		}
		break;
	case ESLOGRA_STATE::BEAK:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Beak_Idle_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Beak_Idle_Left", false);
		}
		break;
	}
}

void CSlogra::Walk()
{
	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Spear_Move_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Spear_Move_Left", true);
		}
		break;
	case ESLOGRA_STATE::BEAK:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Beak_Move_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Beak_Move_Left", true);
		}
		break;
	}
}

void CSlogra::Turn()
{
	CMonster::Turn();

	Walk();
}

void CSlogra::Attack()
{
	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Spear_Attack_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Spear_Attack_Left", false);
		}
	}
		break;
	case ESLOGRA_STATE::BEAK:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Beak_Attack_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Beak_Attack_Left", false);
		}
	}
		break;
	}

	SetOnAttack(true);
}

void CSlogra::Hit()
{
	SetSlograHit(true);

	if (ESLOGRA_STATE::SPEAR == GetSlograState() && (int)GetMonsterInfo().m_iMaxHP / 2 >= GetMonsterInfo().m_iHP)
	{
		ChangeSlograState(ESLOGRA_STATE::BEAK);
	}

	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Spear_Hit_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Spear_Hit_Left", false);
		}
	}
	break;
	case ESLOGRA_STATE::BEAK:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Beak_Hit_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Beak_Hit_Left", false);
		}
	}
	break;
	}

	if (GetFaceDir())
	{
		GetRigidBody()->AddVelocity(Vec2(-100.f, -800.f));
	}
	else
	{
		GetRigidBody()->AddVelocity(Vec2(100.f, -800.f));
	}
}

void CSlogra::Sting()
{
	CMonsterAttack* pAttack = new CMonsterAttack;

	pAttack->SetDamage(GetMonsterInfo().m_iAtk);
	pAttack->SetLifeSpan(0.3f);

	Vec2 vPos = {};
	Vec2 vScale = {};

	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
	{
		vPos.y -= 150.f;
		vScale = Vec2(240.f, 50.f);

		if (GetFaceDir())
		{
			vPos.x += (120.f + 35.f);
		}
		else
		{
			vPos.x -= (120.f + 35.f);
		}
	}
		break;
	case ESLOGRA_STATE::BEAK:
	{
		vPos.y -= 100.f;
		vScale = Vec2(240.f, 50.f);

		if (GetFaceDir())
		{
			vPos.x += (120.f + 35.f);
		}
		else
		{
			vPos.x -= (120.f + 35.f);
		}
	}
		break;
	}
	pAttack->GetCollider()->SetScale(vScale);
	pAttack->GetCollider()->SetOffsetPos(vPos);

	Instantiate(pAttack, GetPos(), ELAYER::MONSTER_PROJECTILE);
}

void CSlogra::DeathEffect()
{
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);

	int iRand = rand();

	Vec2 vPos = GetPos();
	Vec2 vScale = Vec2(200.f, 200.f);

	int iX1 = (int)(vPos.x - vScale.x / 2.f);
	int iX2 = (int)(vPos.x + vScale.x / 2.f);

	int iY1 = (int)(vPos.y - vScale.y / 2.f);
	int iY2 = (int)(vPos.y + vScale.y / 2.f);

	int iRandX = rand() % 200 + iX1;
	int iRandY = rand() % 200 + iY1;

	CEffect* pEffect = new CEffect;

	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\SLOGRA_DEATH_EFFECT.anim");
	pEffect->GetAnimator()->Play(false);

	vPos = Vec2((float)iRandX, (float)iRandY);

	Instantiate(pEffect, vPos, ELAYER::EFFECT);
}

void CSlogra::Fire()
{
	CStraightProjectile* pPrj = new CStraightProjectile;

	Vec2 vPos = GetPos();

	vPos.y -= 150.f;

	pPrj->SetDamage(GetMonsterInfo().m_iAtk);
	pPrj->SetFaceDir(GetFaceDir());
	pPrj->SetSpeed(500.f);

	pPrj->GetCollider()->SetScale(Vec2(30.f, 30.f));

	if (pPrj->GetFaceDir())
	{
		pPrj->GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_FIREBALL_RIGHT.anim");
		vPos.x += 250.f;
	}
	else
	{
		pPrj->GetAnimator()->LoadAnimation(L"animation\\Monster\\Slogra\\SLOGRA_FIREBALL_LEFT.anim");
		vPos.x -= 250.f;
	}

	pPrj->GetAnimator()->Play(true);

	Instantiate(pPrj, vPos, ELAYER::MONSTER_PROJECTILE);
}

void CSlogra::Wake()
{
	GetAI()->ChangeState(L"SlograMove");
}

void CSlogra::Drop()
{
	switch (m_eState)
	{
	case ESLOGRA_STATE::SPEAR:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Spear_Drop_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Spear_Drop_Left", false);
		}
	}
	break;
	case ESLOGRA_STATE::BEAK:
	{
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Slogra_Beak_Drop_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Slogra_Beak_Drop_Left", false);
		}
	}
	break;
	}
}

void CSlogra::Dead()
{
	m_bDeadSequence = true;

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Slogra_Beak_Hit_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Slogra_Beak_Hit_Left", true);
	}

	GetCollider()->SetScale(Vec2(0.f, 0.f));
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
}
