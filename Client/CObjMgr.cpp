#include "pch.h"
#include "CObjMgr.h"

#include "CAI.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CWeapon.h"

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
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

}

// ����� ������Ʈ �̸� ��� ����
void CObjMgr::Init()
{

	// ==============
	// Monster Origin
	// ==============



	// ===========
	// Item Origin
	// ===========

	CWeapon* pWeapon = new CWeapon;
	pWeapon->SetName(L"Alucard_Sword");
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
	pPlayer->GetAI()->ChangeState(L"Idle");
	pPlayer->SetWeapon(pWeapon);
	m_mapObj.insert(make_pair(pPlayer->GetName(), pPlayer));
}
