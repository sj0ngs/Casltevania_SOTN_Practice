#include "pch.h"
#include "CGameOverLevel.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CEffect.h"
#include "CAnimDebug.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CSound.h"

CGameOverLevel::CGameOverLevel()
{
}

CGameOverLevel::~CGameOverLevel()
{
}

void CGameOverLevel::Init()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	CObj* pObj = new CAnimDebug;
	pObj->GetAnimator()->LoadAnimation(L"animation\\UI\\GAME_OVER.anim");
	pObj->GetAnimator()->Play(true);
	pObj->GetCollider()->SetScale(Vec2(0.f, 0.f));
	Instantiate(pObj, vResolution / 2.f, ELAYER::OBJECT);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Game_Over");
	pSound->PlayToBGM(false);
}

void CGameOverLevel::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::TITLE);
	}
}

void CGameOverLevel::Enter()
{
	Init();

	CTimeMgr::GetInst()->SetTimeLock(false);

	CLevel::Enter();

	CCamera::GetInst()->FadeIn(1.f);
}

void CGameOverLevel::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
