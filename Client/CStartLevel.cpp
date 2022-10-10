#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::Init()
{
	// texture �ε�
	//CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Fighter.bmp");
	CResMgr::GetInst()->LoadTexture(L"Alucard", L"texture\\Alucard_4.bmp");

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(500.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObj(pObj, ELAYER::PLAYER);

	//pObj = pObj->Clone();
	//pObj->SetPos(Vec2(700.f, 100.f));
	//AddObj(pObj, ELAYER::PLAYER);

	CMonster* pMonster = new CMonster;
	pMonster->SetPos(Vec2(300.f, 100.f));
	pMonster->SetScale(Vec2(80.f, 80.f));
	//pMonster->SetTarget(pObj);
	AddObj(pMonster, ELAYER::MONSTER);

	//pMonster = pMonster->Clone();
	//pMonster->SetPos(Vec2(1000.f, 100.f));
	//AddObj(pMonster, ELAYER::MONSTER);

	// Level�� �浹 ����
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::ENTER))
	{
		CCamera::GetInst()->FadeOut(1.f);
		CCamera::GetInst()->FadeIn(1.f);

		ChangeLevel(ELEVEL_TYPE::EDITOR);
	}

	if (IS_TAP(EKEY::key1))
	{
		ChangeLevel(ELEVEL_TYPE::STAGE_01);
	}

	if (IS_TAP(EKEY::LBTN))
	{
		CForce* pForce = new CForce;
		pForce->SetLifeTime(1.5f);
		pForce->SetForceScale(1000.f);
		pForce->SetForceRadius(250.f);

		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		Instantiate(pForce, vMousePos, ELAYER::FORCE);
	}

	if (IS_TAP(EKEY::RBTN))
	{
		CPlatform* pPlatform = new CPlatform;

		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		Instantiate(pPlatform, vMousePos, ELAYER::PLATFORM);
	}
}

void CStartLevel::Enter()
{
	Init();
}

void CStartLevel::Exit()
{
	DeleteAllObject();
}