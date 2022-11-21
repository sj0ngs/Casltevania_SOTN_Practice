#include "pch.h"
#include "CStage03.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"

#include "CObj.h"
#include "CPlayer.h"

CStage03::CStage03()
{
}

CStage03::~CStage03()
{
}

void CStage03::Init()
{
	LoadLevel(L"level\\Room_3.level");

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

void CStage03::Tick()
{
	CLevel::Tick();
}

void CStage03::Enter()
{
	Init();

	CLevel::Enter();
}

void CStage03::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
