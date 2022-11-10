#include "pch.h"
#include "CBossLevel.h"

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
#include "CBackGround.h"

CBossLevel::CBossLevel()
{
}

CBossLevel::~CBossLevel()
{
}

void CBossLevel::Init()
{
	LoadLevel(L"level\\Boss_Level.level");

	// Level의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::MONSTER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::TRIGGER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::PLAYER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::MONSTER);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CBossLevel::Tick()
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
		CCamera::GetInst()->TracePlayer(vPlayerPos);
	}

	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::EDITOR);
	}
}

void CBossLevel::Enter()
{
	Init();

	CLevel::Enter();
}

void CBossLevel::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
