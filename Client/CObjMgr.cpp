#include "pch.h"
#include "CObjMgr.h"

#include "CAI.h"
#include "CResMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CWeapon.h"

#include "CSkeleton.h"
#include "CBloodSkeleton.h"

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

// ������ �ٲ� ��, ���� ������ �÷��̾� ������ ������ ������Ʈ ���ش�
void CObjMgr::UpDatePlayer(CPlayer* _pPlayer)
{
	CPlayer* pOrigin = dynamic_cast<CPlayer*>(FindObj(L"Player"));

	pOrigin->Copy(_pPlayer);
}

// ����� ������Ʈ �̸� ��� ����
void CObjMgr::Init()
{
	// �ؽ��� ��� �ε�

	// �÷��̾� �ؽ���
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\Alucard\\alucard_left_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\Alucard\\alucard_right_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_2", L"texture\\Alucard\\alucard_left_2.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_2", L"texture\\Alucard\\alucard_right_2.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Weapon\\Axe_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Right", L"texture\\Weapon\\Axe_Right.bmp");


	CResMgr::GetInst()->LoadTexture(L"Room_1", L"texture\\Map\\Room_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"BackGround", L"texture\\Map\\BackGround.bmp");

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


	//CResMgr::GetInst()->LoadTexture(L"Bible_Crash_Right", L"texture\\Weapon\\Item_Crash_Bible.bmp");

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
