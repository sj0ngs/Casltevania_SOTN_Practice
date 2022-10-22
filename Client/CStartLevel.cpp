#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CLine.h"

CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::Init()
{
	// texture 로딩
	//CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Fighter.bmp");

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(500.f, 100.f));
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

	// Level의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::PLAYER);
	
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::Tick()
{
	CLevel::Tick();

	// 야매로 만든 카메라가 플레이어 따라오는 코드 
	// 나중에 게임 인스턴스 같은걸로 플레이어 따로 저장해서 블러와야 함
	const vector<CObj*>& vecPlayer = GetLayer(ELAYER::PLAYER);
	CPlayer* pPlayer = (CPlayer*)vecPlayer[0];

	if (nullptr != pPlayer)
	{
		Vec2 vPlayerPos = pPlayer->GetPos();
		vPlayerPos.y -= 100.f;
		CCamera::GetInst()->SetLook(vPlayerPos);
	}
	
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
		//CForce* pForce = new CForce;
		//pForce->SetLifeTime(1.5f);
		//pForce->SetForceScale(1000.f);
		//pForce->SetForceRadius(250.f);

		//Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		//Instantiate(pForce, vMousePos, ELAYER::FORCE);

		CLine* pLine = new CLine;
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		//pLine->SetPos1(vMousePos - Vec2(100.f, -50.f));
		//pLine->SetPos2(vMousePos + Vec2(100.f, -50.f));
		pLine->SetPos1(vMousePos - Vec2(100.f, 0.f));
		pLine->SetPos2(vMousePos + Vec2(100.f, 0.f));
		Instantiate(pLine, vMousePos, ELAYER::LINE);
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
