#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CSound.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CBackGround.h"

CStartLevel::CStartLevel()
{
	SetStartPointIdx(0);
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::Init()
{
	// ���� ���� �ε�
	LoadLevel(L"level\\Debug_Level.level");

	// HUD ����
	CreateHUD();

	// Level�� �浹 ����
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER_PROJECTILE, ELAYER::MAP_OBJECT);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::MONSTER, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::ITEM, ELAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(ELAYER::PLAYER, ELAYER::TRIGGER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::PLAYER);
	CLineCollisionMgr::GetInst()->CollisionSet(ELAYER::MONSTER);
	
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::Tick()
{
	CLevel::Tick();

	// �߸ŷ� ���� ī�޶� �÷��̾� ������� �ڵ� 
	// ���߿� ���� �ν��Ͻ� �����ɷ� �÷��̾� ���� �����ؼ� ���;� ��
	//const vector<CObj*>& vecPlayer = GetLayer(ELAYER::PLAYER);

	//CPlayer* pPlayer = (CPlayer*)vecPlayer[0];

	//if (nullptr != pPlayer)
	//{
	//	Vec2 vPlayerPos = pPlayer->GetPos();
	//	vPlayerPos.y -= 100.f;
	//	CCamera::GetInst()->TracePlayer(vPlayerPos);
	//}
	
	//if (IS_TAP(EKEY::key1))
	//{
	//	ChangeLevel(ELEVEL_TYPE::STAGE_01);
	//}

	//if (IS_TAP(EKEY::LBTN))
	//{
	//	//CForce* pForce = new CForce;
	//	//pForce->SetLifeTime(1.5f);
	//	//pForce->SetForceScale(1000.f);
	//	//pForce->SetForceRadius(250.f);

	//	//Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	//Instantiate(pForce, vMousePos, ELAYER::FORCE);

	//	CLine* pLine = new CLine;
	//	Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	pLine->SetPos1(vMousePos - Vec2(100.f, -50.f));
	//	pLine->SetPos2(vMousePos + Vec2(100.f, -50.f));
	//	//pLine->SetPos1(vMousePos - Vec2(100.f, 0.f));
	//	//pLine->SetPos2(vMousePos + Vec2(100.f, 0.f));
	//	Instantiate(pLine, vMousePos, ELAYER::LINE);
	//}

	//if (IS_TAP(EKEY::RBTN))
	//{
	//	CPlatform* pPlatform = new CPlatform;

	//	Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	Instantiate(pPlatform, vMousePos, ELAYER::PLATFORM);
	//}
}

void CStartLevel::Enter()
{
	Init();

	CLevel::Enter();
}

void CStartLevel::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}
