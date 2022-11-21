#include "pch.h"
#include "CStage02.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"

#include "CObj.h"
#include "CPlayer.h"

CStage02::CStage02()
{
}

CStage02::~CStage02()
{
}

void CStage02::Init()
{
	LoadLevel(L"level\\Room_2.level");

	// HUD 생성
	CreateHUD();

	// Level의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::MONSTER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::TRIGGER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::PLAYER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::MONSTER);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStage02::Tick()
{
	CLevel::Tick();
}

void CStage02::Enter()
{
	Init();

	CLevel::Enter();
}


void CStage02::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
