#include "pch.h"
#include "CObjMgr.h"

#include "CAI.h"
#include "CResMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CEffect.h"

#include "CSkeleton.h"
#include "CBloodSkeleton.h"
#include "CBoneScimitar.h"
#include "CAxeArmor.h"

#include "CSlogra.h"
#include "CGaibon.h"

#include "CAnimator.h"

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	map<wstring, CObj*>::iterator iter, iterEnd = m_mapObj.end();
	for (iter = m_mapObj.begin(); iter != iterEnd; ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
}

CObj* CObjMgr::FindObj(wstring _strName)
{
	map<wstring, CObj*>::iterator iter = m_mapObj.find(_strName);

	if (iter == m_mapObj.end())
		return nullptr;
	
	return iter->second;
}

// 레벨이 바뀔 때, 현재 레벨의 플레이어 정보를 원본에 업데이트 해준다
void CObjMgr::UpDatePlayer(CPlayer* _pPlayer)
{
	CPlayer* pOrigin = dynamic_cast<CPlayer*>(FindObj(L"Player"));

	pOrigin->Copy(_pPlayer);
}

// 사용할 오브젝트 미리 모두 생성
void CObjMgr::Init()
{
	// 텍스쳐 모두 로딩

	// 플레이어 텍스쳐
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\Alucard\\alucard_left_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\Alucard\\alucard_right_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_2", L"texture\\Alucard\\alucard_left_2.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_2", L"texture\\Alucard\\alucard_right_2.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Weapon\\Axe_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Right", L"texture\\Weapon\\Axe_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Room_1", L"texture\\Map\\Room_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"BackGround", L"texture\\Map\\BackGround.bmp");

	// =======
	// Monster
	// =======
	
	// Skeleton
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Left", L"texture\\Monster\\SKeleton\\Skeleton_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Right", L"texture\\Monster\\SKeleton\\Skeleton_Right.bmp");
																				
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Death_Left", L"texture\\Monster\\SKeleton\\Skeleton_Death_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Death_Right", L"texture\\Monster\\SKeleton\\Skeleton_Death_Right.bmp");

	// Blood Skeleton
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Collapse_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Collapse_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Collapse_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Collapse_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Rise_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Rise_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Rise_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Rise_Right.bmp");

	// Bone Scimitar
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Left", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Right", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Attack_Left", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Attack_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Attack_Right", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Attack_Right.bmp");

	// Axe Armor
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Idle_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Idle_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Idle_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Idle_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Walk_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Walk_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Walk_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Walk_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Throw_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Throw_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Throw_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Throw_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Attack_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Attack_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Attack_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Attack_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Axe_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Axe_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Axe_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Axe_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Death", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Death.bmp");

	// Slogra
	CResMgr::GetInst()->LoadTexture(L"Slogra_Left", L"texture\\Monster\\Slogra\\Slogra_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Slogra_Right", L"texture\\Monster\\Slogra\\Slogra_Right.bmp");

	// Gaibon
	CResMgr::GetInst()->LoadTexture(L"Gaibon_Left", L"texture\\Monster\\Gaibon\\Gaibon_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Gaibon_Right", L"texture\\Monster\\Gaibon\\Gaibon_Right.bmp");

	//CResMgr::GetInst()->LoadTexture(L"Bible_Crash_Right", L"texture\\Weapon\\Item_Crash_Bible.bmp");

	// ======
	// Effect
	// ======

	// Hit
	CResMgr::GetInst()->LoadTexture(L"Hit_Effect", L"texture\\Effect\\Hit_Effect.bmp");

	// Burn 1
	CResMgr::GetInst()->LoadTexture(L"Burn_Effect_1", L"texture\\Effect\\Burn_Effect_1.bmp");

	// Burn 2
	CResMgr::GetInst()->LoadTexture(L"Burn_Effect_2", L"texture\\Effect\\Burn_Effect_2.bmp");

	// ==============
	// Monster Origin
	// ==============
	tMonsterInfo tMonInfo = {};

	// Blood Skeleton
	CMonster* pMon = new CBloodSkeleton;
	pMon->SetName(L"Blood_Skeleton");
	tMonInfo.m_iMaxHP = 20;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 5;
	tMonInfo.m_iDef = 0;
	tMonInfo.m_fPatrolSpeed = 50.f;
	tMonInfo.m_fTraceSpeed = 0.f;
	tMonInfo.m_fDetectRange = 0.f;
	tMonInfo.m_fAttackRange = 200.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// Skeleton
	pMon = new CSkeleton;
	pMon->SetName(L"Skeleton");
	tMonInfo.m_iMaxHP = 30;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 10;
	tMonInfo.m_iDef = 2;
	tMonInfo.m_fPatrolSpeed = 50.f;
	tMonInfo.m_fTraceSpeed = 100.f;
	tMonInfo.m_fDetectRange = 600.f;
	tMonInfo.m_fAttackRange = 400.f;
	tMonInfo.m_fDodgeRange = 300.f;
	tMonInfo.m_fAttackTime = 1.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// Bone Scimitar
	pMon = new CBoneScimitar;
	pMon->SetName(L"Bone_Scimitar");
	tMonInfo.m_iMaxHP = 40;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 15;
	tMonInfo.m_iDef = 5;
	tMonInfo.m_fPatrolSpeed = 50.f;
	tMonInfo.m_fTraceSpeed = 120.f;
	tMonInfo.m_fDetectRange = 600.f;
	tMonInfo.m_fAttackRange = 200.f;
	tMonInfo.m_fDodgeRange = 0.f;
	tMonInfo.m_fAttackTime = 2.f;
	tMonInfo.m_fAttackCoolTime = 2.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// Axe Armor
	pMon = new CAxeArmor;
	pMon->SetName(L"Axe_Armor");
	tMonInfo.m_iMaxHP = 50;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 20;
	tMonInfo.m_iDef = 10;
	tMonInfo.m_fPatrolSpeed = 50.f;
	tMonInfo.m_fTraceSpeed = 50.f;
	tMonInfo.m_fDetectRange = 600.f;
	tMonInfo.m_fAttackRange = 500.f;
	tMonInfo.m_fDodgeRange = 0.f;
	tMonInfo.m_fAttackTime = 2.f;
	tMonInfo.m_fAttackCoolTime = 2.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// BOSS : Slogra
	pMon = new CSlogra;
	pMon->SetName(L"Slogra");
	tMonInfo.m_iMaxHP = 200;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 25;
	tMonInfo.m_iDef = 10;
	tMonInfo.m_fPatrolSpeed = 100.f;
	tMonInfo.m_fTraceSpeed = 150.f;
	tMonInfo.m_fDetectRange = 600.f;
	tMonInfo.m_fAttackRange = 300.f;
	tMonInfo.m_fDodgeRange = 0.f;
	tMonInfo.m_fAttackTime = 1.f;
	tMonInfo.m_fAttackCoolTime = 2.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// BOSS : Gaibon
	pMon = new CGaibon;
	pMon->SetName(L"Gaibon");
	tMonInfo.m_iMaxHP = 200;
	tMonInfo.m_iHP = tMonInfo.m_iMaxHP;
	tMonInfo.m_iAtk = 25;
	tMonInfo.m_iDef = 10;
	tMonInfo.m_fPatrolSpeed = 100.f;
	tMonInfo.m_fTraceSpeed = 500.f;
	tMonInfo.m_fDetectRange = 600.f;
	tMonInfo.m_fAttackRange = 300.f;
	tMonInfo.m_fDodgeRange = 0.f;
	tMonInfo.m_fAttackTime = 1.f;
	tMonInfo.m_fAttackCoolTime = 2.f;
	pMon->SetMonsterInfo(tMonInfo);
	m_mapObj.insert(make_pair(pMon->GetName(), pMon));

	// =============
	// Effect Origin
	// =============


	// ===========
	// Item Origin
	// ===========

	CWeapon* pWeapon = new CWeapon;
	pWeapon->SetName(L"Alucard_Sword");
	tWeaponInfo tWeaponInfo;
	tWeaponInfo.m_iStr = 5;
	pWeapon->SetWeaponInfo(tWeaponInfo);
	pWeapon->SetWeaponAnim(L"SWORD_RIGHT.anim", L"SWORD_LEFT.anim",
							L"JUMP_SWORD_RIGHT.anim", L"JUMP_SWORD_LEFT.anim",
							L"EFFECT_RIGHT.anim", L"EFFECT_LEFT.anim",
							L"JUMP_EFFECT_RIGHT.anim", L"JUMP_EFFECT_LEFT.anim");
	m_mapObj.insert(make_pair(pWeapon->GetName(), pWeapon));

	// =============
	// Player Origin
	// =============
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetFaceDir(false);
	pPlayer->GetAI()->ChangeState(L"Idle");
	pPlayer->SetWeapon(pWeapon);
	m_mapObj.insert(make_pair(pPlayer->GetName(), pPlayer));
}
