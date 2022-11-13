#include "pch.h"
#include "CGaibon.h"

#include "CLevelMgr.h"

#include "CLevel.h"

#include "CSlogra.h"

#include "CGaibonMoveState.h"
#include "CGaibonSkyAttack.h"
#include "CGaibonLandAttackState.h"
#include "CGaibonChangeState.h"
#include "CGaibonStandByState.h"
#include "CGaibonTraceSlograState.h"
#include "CGaibonPickUpState.h"

#include "CGaibonFireBall.h"
#include "CGaibonFireBallDg.h"

#include "CEffect.h"

CGaibon::CGaibon()	:
	m_eState(EGAIBON_STATE::PHASE_1),
	m_pSlogra(nullptr),
	m_bDeadSequence(false),
	m_faccDeathTime(0.f),
	m_faccDeathEffectSpawnTime(0.f),
	m_bFallSequence(false)
{
	GetCollider()->SetScale(Vec2(70.f, 220.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -110.f));

	GetRigidBody()->SetFriction(1000.f);
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetGravityAccel(1500.f);
	GetRigidBody()->SetVelocityLimit(1000.f);

	// Phase 1
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LANDING_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LANDING_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LAND_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LAND_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_CHANGE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_CHANGE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_PICK_UP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_PICK_UP_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_RIGHT.anim");

	// Phase 2
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LANDING_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LANDING_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LAND_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LAND_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_PICK_UP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_PICK_UP_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_DEATH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_DEATH_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_EFFECT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_EFFECT_RIGHT.anim");

	GetAI()->AddState(L"GaibonMove", new CGaibonMoveState);
	GetAI()->AddState(L"GaibonSkyAttack", new CGaibonSkyAttack);
	GetAI()->AddState(L"GaibonLandAttack", new CGaibonLandAttackState);
	GetAI()->AddState(L"GaibonChange", new CGaibonChangeState);
	GetAI()->AddState(L"GaibonStandBy", new CGaibonStandByState);
	GetAI()->AddState(L"GaibonTraceSlogra", new CGaibonTraceSlograState);
	GetAI()->AddState(L"GaibonPickUp", new CGaibonPickUpState);
	GetAI()->ChangeState(L"GaibonStandBy");
}

CGaibon::~CGaibon()
{
}

void CGaibon::Tick()
{
	CObj::Tick();

	IsValid((CObj*&)m_pSlogra);

	if (m_bFallSequence)
	{
		if (GetRigidBody()->IsGround())
		{
			m_bFallSequence = false;
			DeathStart();
		}
	}

	if (m_bDeadSequence)
	{
		m_faccDeathTime += DELTATIME;
		m_faccDeathEffectSpawnTime += DELTATIME;

		if (4.f <= m_faccDeathTime)
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

void CGaibon::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

CSlogra* CGaibon::GetSlogra()
{
	if (IsValid((CObj*&)m_pSlogra))
	{
		return m_pSlogra;
	}
	else
	{
		return nullptr;
	}
}

void CGaibon::Walk()
{
	GetRigidBody()->SetGravity(false);

	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Sky_Idle_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Sky_Idle_Left", true);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Idle_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Idle_Left", true);
		}
		break;
	}
}

void CGaibon::Turn()
{
	CMonster::Turn();

	Walk();
}

void CGaibon::SkyAttack()
{
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Sky_Attack_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Sky_Attack_Left", true);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Attack_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Attack_Left", true);
		}
		break;
	}
}

void CGaibon::LandAttack()
{
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Land_Attack_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Land_Attack_Left", false);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Land_Attack_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Land_Attack_Left", false);
		}
		break;
	}
}

void CGaibon::Landing()
{
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Landing_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Landing_Left", false);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Landing_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Landing_Left", false);
		}
		break;
	}
}

void CGaibon::SkyFire()
{
	CGaibonFireBallDg* pPrj = new CGaibonFireBallDg;

	Vec2 vPos = GetPos();

	vPos.y -= 150.f;

	pPrj->SetDamage(GetMonsterInfo().m_iAtk);
	pPrj->SetFaceDir(GetFaceDir());
	pPrj->SetSpeed(500.f);

	pPrj->GetCollider()->SetScale(Vec2(30.f, 30.f));
	Vec2 vOffset = {};

	if (pPrj->GetFaceDir())
	{
		pPrj->GetAnimator()->Play(L"Gaibon_Sky_Fire_Right", true);
		vPos.x += 60.f;
	}
	else
	{
		pPrj->GetAnimator()->Play(L"Gaibon_Sky_Fire_Left", true);
		vPos.x -= 60.f;
	}

	Instantiate(pPrj, vPos, ELAYER::MONSTER_PROJECTILE);
}

void CGaibon::LandFire()
{
	CGaibonFireBall* pPrj = new CGaibonFireBall;

	Vec2 vPos = GetPos();

	vPos.y -= 150.f;

	pPrj->SetDamage(GetMonsterInfo().m_iAtk);
	pPrj->SetFaceDir(GetFaceDir());
	pPrj->SetSpeed(500.f);

	pPrj->GetCollider()->SetScale(Vec2(30.f, 30.f));
	Vec2 vOffset = {};

	if (pPrj->GetFaceDir())
	{
		pPrj->GetAnimator()->Play(L"Gaibon_Land_Fire_Right", true);
		vPos.x += 60.f;
	}
	else
	{
		pPrj->GetAnimator()->Play(L"Gaibon_Land_Fire_Left", true);
		vPos.x -= 60.f;
	}

	Instantiate(pPrj, vPos, ELAYER::MONSTER_PROJECTILE);
}

void CGaibon::Wake()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecMon = pCurLevel->GetLayer(ELAYER::MONSTER);

	const vector<CObj*>::const_iterator iter = vecMon.begin();

	for (size_t i = 0; i < vecMon.size(); i++)
	{
		if (L"Slogra" == vecMon[i]->GetName())
		{
			m_pSlogra = (CSlogra*)vecMon[i];
			break;
		}
	}
	assert(iter != vecMon.end());

	//m_pSlogra->Wake();
}

void CGaibon::Change()
{
	ChangeGaibonState(EGAIBON_STATE::PHASE_2);

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Gaibon_Change_Right", false);
	}
	else
	{
		GetAnimator()->Play(L"Gaibon_Change_Left", false);
	}

	// 데미지 올려주는 작업 등등 페이즈 변경 작업
}

void CGaibon::PickUp()
{
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Sky_Pick_Up_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Sky_Pick_Up_Left", true);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Pick_Up_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Pick_Up_Left", true);
		}
		break;
	}
}

void CGaibon::DeathEffect()
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

void CGaibon::DeathStart()
{
	m_bDeadSequence = true;
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Death_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Death_Left", false);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Death_Right", false);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Death_Left", false);
		}
		break;
	}

	GetCollider()->SetScale(Vec2(0.f, 0.f));
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CGaibon::Dead()
{
	m_bFallSequence = true;
	GetRigidBody()->SetGravity(true);
	Landing();

	if (m_pSlogra)
	{
		m_pSlogra->SetSlograCatch(false);
	}
}
