#include "pch.h"
#include "CPlayerJumpAttackState.h"

#include "CPlayer.h"

CPlayerJumpAttackState::CPlayerJumpAttackState()
{
}

CPlayerJumpAttackState::~CPlayerJumpAttackState()
{
}

void CPlayerJumpAttackState::Final_Tick()
{
	GET_PLAYER();

	Vec2 vPos = GetOwnerObj()->GetPos();

	GetAttack()->SetPos(vPos);

	if (pPlayer->GetRigidBody()->IsGround())
	{
		pPlayer->ResetJump();
		ChangeState(L"Landing");
		return;
	}
	else if (GetAnim()->IsFinish())
	{
		ChangeState(L"Fall");
		return;
	}

	Move();


	CPlayerState::Final_Tick();
	//Hit();
}

void CPlayerJumpAttackState::Enter()
{
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
			SET_ANIM(L"Jump_Attack_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -150.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Jump_Attack_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -150.f);
		}
	}
	else
	{
		vScale = Vec2(120.f, 40.f);
		// ¿À¸¥ÂÊ ¹Ù¶óº½
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Jump_Punch_Right");
			vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -150.f);
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Jump_Punch_Left");
			vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -150.f);
		}
	}

	pAttack->GetCollider()->SetScale(vScale);
	pAttack->GetCollider()->SetOffsetPos(vOffsetPos);
	Instantiate(pAttack, vObjPos, ELAYER::PLAYER_PROJECTILE);

	pPlayer->GetRigidBody()->SetGravity(true);
}