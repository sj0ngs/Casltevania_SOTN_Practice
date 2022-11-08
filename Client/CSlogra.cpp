#include "pch.h"
#include "CSlogra.h"

#include "CTimeMgr.h"

#include "CAnimator.h"

#include "CSlograIdleState.h"
#include "CSlograMoveState.h"
#include "CSlograAttackState.h"
#include "CSlograHitState.h"
#include "CSlograFireState.h"

#include "CProjectile.h"
#include "CMonsterAttack.h"

CSlogra::CSlogra()	:
	m_eState(ESLOGRA_STATE::SPEAR),
	m_bAttackEnd(false),
	m_faccAttackCool(0.f),
	m_bCanAttack(true),
	m_bCanFire(true),	
	m_bFireEnd(false),
	m_faccFireCool(0.f)
{
	GetCollider()->SetScale(Vec2(70.f, 220.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -100.f));

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
	GetAI()->ChangeState(L"SlograMove");
}

CSlogra::~CSlogra()
{
}

void CSlogra::Tick()
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

		if (GetAI()->FindState(L"SlograHit") != GetAI()->GetCurState())
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
		GetRigidBody()->AddVelocity(Vec2(-200.f, -800.f));
	}
	else
	{
		GetRigidBody()->AddVelocity(Vec2(200.f, -800.f));
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

void CSlogra::Fire()
{

}

void CSlogra::Dead()
{
}
