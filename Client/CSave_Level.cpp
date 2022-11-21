#include "pch.h"
#include "CSave_Level.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSound.h"

#include "CTexture.h"
#include "CBackGround.h"

#include "CSaveTrigger.h"

#include "CParticle.h"

CSave_Level::CSave_Level()
{
}

CSave_Level::~CSave_Level()
{
}

void CSave_Level::Init()
{
	// 레벨 로드
	LoadLevel(L"level\\Save_Room.level");

	// HUD 생성
	CreateHUD();

	// Level의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::TRIGGER);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"Save_Room_Front");
	CBackGround* pBGFront = new CBackGround;
	pBGFront->SetBackGroundImg(pTex);
	pBGFront->SetIsForeGround(true);
	Instantiate(pBGFront, Vec2(0.f, 0.f), ELAYER::OBJECT);

	SetTrigger();

	//CSound* pSound = CResMgr::GetInst()->FindSound(L"Dance_of_Gold");
	//pSound->Stop();
}

void CSave_Level::Tick()
{
	CLevel::Tick();
}

void CSave_Level::Render(HDC _DC)
{
	CLevel::Render(_DC);
}

void CSave_Level::Enter()
{
	Init();

	CLevel::Enter();
}

void CSave_Level::Exit()
{
	DeleteAllObject();

	CLevel::Exit();

	//CSound* pSound = CResMgr::GetInst()->FindSound(L"Dance_of_Gold");
	//pSound->PlayToBGM(true);
}

void CSave_Level::SetTrigger()
{
	CSaveTrigger* pTrigger = new CSaveTrigger;
	pTrigger->GetCollider()->SetScale(Vec2(180.f, 390.f));
	pTrigger->GetCollider()->SetOffsetPos(Vec2(0.f, -195.f));
	Instantiate(pTrigger, Vec2(500.f, 670.f), ELAYER::TRIGGER);

	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int iRandX = rand();
	int iRandY = 0;

	CParticle* pParticle;
	for (int i = 0; i < 10; i++)
	{
		Vec2 vPos = Vec2(510.f, 250.f);
		pParticle = new CParticle;
		pParticle->SetFrm(rand());

		iRandX = rand() % 500 - 250;
		iRandY = rand() % 150 - 75;

		vPos.x += (float)iRandX;
		vPos.y += (float)iRandY;
		Instantiate(pParticle, vPos, ELAYER::FRONT_EFFECT);

		pTrigger->AddParticle(pParticle);
	}
}
