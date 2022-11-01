#include "pch.h"
#include "CPlayerStandAttackState.h"

#include "CPlayer.h"

CPlayerStandAttackState::CPlayerStandAttackState()
{
}

CPlayerStandAttackState::~CPlayerStandAttackState()
{
}

void CPlayerStandAttackState::Final_Tick()
{
	if (6 == GetAnim()->GetCurFrame())
		GetAttack()->GetCollider()->SetScale(Vec2(0.f, 0.f));
	else if (6 < GetAnim()->GetCurFrame())
	{
		if (IS_PRESSED(EKEY::RIGHT))
			ChangeState(L"Move_Right");
		else if (IS_PRESSED(EKEY::LEFT))
			ChangeState(L"Move_Left");
	}

	if (GetAnim()->IsFinish())
	{
		ChangeState(L"Idle");
	}
}

void CPlayerStandAttackState::Enter()
{
	GET_PLAYER();

	CAttack* pAttack = new CAttack(GetOwnerObj());
	SetAttack(pAttack);
	Vec2 vOffsetPos = {};
	Vec2 vScale = {};

	Vec2 vObjPos = pPlayer->GetPos();
	Vec2 vObjScale = pPlayer->GetCollider()->GetScale();


	if (pPlayer->GetWeapon())
	{
		vScale = Vec2(150.f, 40.f);
		// ¿À¸¥ÂÊ ¹Ù¶óº½
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Stand_Attack_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -150.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Stand_Attack_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -150.f);
		}
	}
	else
	{
		vScale = Vec2(80.f, 40.f);
		// ¿À¸¥ÂÊ ¹Ù¶óº½
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Stand_Punch_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -150.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Stand_Punch_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -150.f);
		}
	}

	pAttack->GetCollider()->SetScale(vScale);
	pAttack->GetCollider()->SetOffsetPos(vOffsetPos);
	Instantiate(pAttack, vObjPos, ELAYER::PLAYER_PROJECTILE);
}
