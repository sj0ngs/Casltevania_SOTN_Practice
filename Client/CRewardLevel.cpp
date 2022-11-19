#include "pch.h"
#include "CRewardLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSound.h"

#include "CTexture.h"

#include "CBench.h"

CRewardLevel::CRewardLevel()
{
}

CRewardLevel::~CRewardLevel()
{
}

void CRewardLevel::Init()
{
	// 레벨 로드
	LoadLevel(L"level\\Reward_Room.level");

	CBench* pBench = (CBench*)CObjMgr::GetInst()->FindObj(L"Bench")->Clone();
	pBench->SetPos(Vec2(512.f, 608.f));
	AddObj(pBench, ELAYER::MAP_OBJECT);

	// HUD 생성
	CreateHUD();

	// Level의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MAP_OBJECT);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::PLAYER);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CRewardLevel::Tick()
{
	CLevel::Tick();
}

void CRewardLevel::Render(HDC _DC)
{
	CLevel::Render(_DC);
}

void CRewardLevel::Enter()
{
	Init();

	CLevel::Enter();
}

void CRewardLevel::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
