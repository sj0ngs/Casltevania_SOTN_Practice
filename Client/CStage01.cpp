#include "pch.h"
#include "CStage01.h"

#include "CKeyMgr.h"

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
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(500.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObj(pObj, ELAYER::PLAYER);
}

void CStage01::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::key0))
		ChangeLevel(ELEVEL_TYPE::START);
}

void CStage01::Enter()
{
	Init();
}

void CStage01::Exit()
{
	DeleteAllObject();
}
