#include "pch.h"
#include "CObjMgr.h"

#include "CAI.h"
#include "CResMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CWeapon.h"

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
	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\Alucard\\alucard_right_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\Alucard\\alucard_left_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_2", L"texture\\Alucard\\alucard_right_2.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_2", L"texture\\Alucard\\alucard_left_2.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Right", L"texture\\Weapon\\Axe_Right.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Weapon\\Axe_Left.bmp");


	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Map\\Room_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Weapon\\BackGround.bmp");

	//CResMgr::GetInst()->LoadTexture(L"Bible_Crash_Right", L"texture\\Weapon\\Item_Crash_Bible.bmp");

	// ==============
	// Monster Origin
	// ==============



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
