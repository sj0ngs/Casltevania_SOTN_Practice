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
