#include "pch.h"
#include "CPlayerDuckAttackState.h"

#include "CPlayer.h"

CPlayerDuckAttackState::CPlayerDuckAttackState()
{
}

CPlayerDuckAttackState::~CPlayerDuckAttackState()
{
}

void CPlayerDuckAttackState::Final_Tick()
{
	if (6 == GetAnim()->GetCurFrame())
	{
		GetAttack()->GetCollider()->SetScale(Vec2(0.f, 0.f));
		GetAttack()->GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	}

	if (GetAnim()->IsFinish())
	{
		if (IS_PRESSED(EKEY::DOWN))
		{
			ChangeState(L"Duck");
			return;
		}
		else
		{
			ChangeState(L"GetUp");
			return;
		}
	}

	CPlayerState::Final_Tick();
	//Hit();
}

void CPlayerDuckAttackState::Enter()
{
	CPlayerAttackState::Enter();

	GET_PLAYER();

	CAttack* pAttack = new CAttack(GetOwnerObj());
	SetAttack(pAttack);
	pAttack->SetDamage(pPlayer->GetDamage());
	Vec2 vOffsetPos = {};
	Vec2 vScale = {};

	Vec2 vObjPos = pPlayer->GetPos();
	Vec2 vObjScale = pPlayer->GetCollider()->GetScale();

	if (pPlayer->GetWeapon())
	{
		vScale = Vec2(170.f, 40.f);
		// ¿À¸¥ÂÊ ¹Ù¶óº½
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Duck_Attack_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -80.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Duck_Attack_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -80.f);
		}
	}
	else
	{
		vScale = Vec2(90.f, 40.f);
		// ¿À¸¥ÂÊ ¹Ù¶óº½
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Duck_Punch_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -80.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Duck_Punch_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -80.f);
		}
	}

	pAttack->GetCollider()->SetScale(vScale);
	pAttack->GetCollider()->SetOffsetPos(vOffsetPos);
	Instantiate(pAttack, vObjPos, ELAYER::PLAYER_PROJECTILE);
}
