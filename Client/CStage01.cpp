#include "pch.h"
#include "CStage01.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"

#include "CObj.h"
#include "CPlayer.h"

CStage01::CStage01()
{
}

CStage01::~CStage01()
{
}

void CStage01::Init()
{
	LoadLevel(L"level\\Room_1.level");

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

void CStage01::Tick()
{
	CLevel::Tick();

	const vector<CObj*>& vecPlayer = GetLayer(ELAYER::PLAYER);

	CPlayer* pPlayer = (CPlayer*)vecPlayer[0];

	if (nullptr != pPlayer)
	{
		Vec2 vPlayerPos = pPlayer->GetPos();
		vPlayerPos.y -= 100.f;
		CCamera::GetInst()->TracePlayer(vPlayerPos);
	}
}

void CStage01::Enter()
{
	Init();

	CLevel::Enter();
}

void CStage01::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
