#include "pch.h"
#include "CBossLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CBackGround.h"

#include "CCollider.h"

#include "CPlatform.h"
#include "CTexture.h"
#include "CSound.h"

CBossLevel::CBossLevel()	:
	m_pLeftBlock(nullptr),
	m_pRightBlock(nullptr),
	m_pWallTex(nullptr),
	m_vLeftPos(32.f, 288.f),
	m_vRightPos(4064.f, 1312.f),
	m_bBossEnd(false)
{
}

CBossLevel::~CBossLevel()
{
}

void CBossLevel::Init()
{
	LoadLevel(L"level\\Boss_Level.level");

	// 보스전 격리벽 생성
	Block();

	// HUD 생성
	CreateHUD();

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

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Dance_of_Gold");

	pSound->Stop();
}

void CBossLevel::Tick()
{
	CLevel::Tick();

	if (nullptr != m_pWallTex)
	{
		if (416.f < m_vLeftPos.y)
		{
			m_vLeftPos.y = 416.f;
			m_bBossEnd = false;
			CSound* pSound = CResMgr::GetInst()->FindSound(L"DOORBS");
			pSound->Stop();
		}
		else if(416.f > m_vLeftPos.y)
		{
			m_vLeftPos.y += DELTATIME * 200.f;
			m_vRightPos.y += DELTATIME * 200.f;
			m_bBossEnd = true;
		}

		if (!m_bBossEnd && 0 == GetLayer(ELAYER::MONSTER).size())
		{
			m_bBossEnd = true;

			if (IsValid((CObj*&)m_pLeftBlock))
			{
				m_pLeftBlock->SetDead();
				m_pLeftBlock = nullptr;
			}

			if (IsValid((CObj*&)m_pRightBlock))
			{
				m_pRightBlock->SetDead();
				m_pRightBlock = nullptr;
			}

			CSound* pSound = CResMgr::GetInst()->FindSound(L"Dance_of_Gold");
			pSound->PlayToBGM(true);

			m_pWallTex = nullptr;
		}
	}
}

void CBossLevel::Render(HDC _DC)
{
	CLevel::Render(_DC);

	if (nullptr != m_pWallTex)
	{
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vLeftPos);
		BitBlt(_DC,
			(int)(vPos.x - m_pWallTex->GetWidth() / 2.f),
			(int)(vPos.y - m_pWallTex->GetHeight() / 2.f),
			(int)(m_pWallTex->GetWidth()),
			(int)(m_pWallTex->GetHeight()),
			m_pWallTex->GetDC(),
			0, 0,
			SRCCOPY);

		vPos = CCamera::GetInst()->GetRenderPos(m_vRightPos);

		BitBlt(_DC,
			(int)(vPos.x - m_pWallTex->GetWidth() / 2.f),
			(int)(vPos.y - m_pWallTex->GetHeight() / 2.f),
			(int)(m_pWallTex->GetWidth()),
			(int)(m_pWallTex->GetHeight()),
			m_pWallTex->GetDC(),
			0, 0,
			SRCCOPY);
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

	m_vLeftPos = Vec2(32.f, 288.f);
	m_vRightPos = Vec2(4064.f, 1312.f);
	m_bBossEnd = false;
}

void CBossLevel::Block()
{
	m_pWallTex = CResMgr::GetInst()->FindTexture(L"Wall");

	if (nullptr == m_pLeftBlock)
	{
		m_pLeftBlock = new CPlatform;
		m_pLeftBlock->GetCollider()->SetScale(Vec2(32.f, 256.f));
		Instantiate(m_pLeftBlock, Vec2(32.f, 416.f), ELAYER::PLATFORM);
	}
		
	if (nullptr == m_pRightBlock)
	{
		m_pRightBlock = new CPlatform;
		m_pRightBlock->GetCollider()->SetScale(Vec2(32.f, 256.f));
		Instantiate(m_pRightBlock, Vec2(4064.f, 1440.f), ELAYER::PLATFORM);
	}

	CSound* pSound = CResMgr::GetInst()->FindSound(L"DOORBS");
	pSound->Play(false);
}
