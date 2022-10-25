#include "pch.h"
#include "CSpawnPoint.h"

#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"

#include "clevel.h"
#include "CEditorLevel.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTexture.h"

CSpawnPoint::CSpawnPoint()	:
	m_eOption(ESPAWNABLE_OBJECT::NONE),
	m_pTexture(nullptr)
{
	SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
}

CSpawnPoint::~CSpawnPoint()
{
}

void CSpawnPoint::Tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (dynamic_cast<CEditorLevel*>(pCurLevel))
		return;

	if (IsDead())
		return;

	switch (m_eOption)
	{
	case ESPAWNABLE_OBJECT::PLAYER:
	{
		CPlayer* pPlayer = new CPlayer;
		pPlayer->SetPos(GetPos());
		pPlayer->SetFaceDir(GetFaceDir());
		pCurLevel->AddObj(pPlayer, ELAYER::PLAYER);
		//Instantiate(pPlayer, GetPos(), ELAYER::PLAYER);
	}
		break;
	case ESPAWNABLE_OBJECT::BONE_SCIMITAR:
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(GetPos());
		pMonster->SetFaceDir(GetFaceDir());
		Instantiate(pMonster, GetPos(), ELAYER::MONSTER);
	}
		break;
	case ESPAWNABLE_OBJECT::AXE_ARMOR:
		break;
	case ESPAWNABLE_OBJECT::SKELETON:
		break;
	case ESPAWNABLE_OBJECT::SPITTLE_BONE:
		break;
	case ESPAWNABLE_OBJECT::GAIBON:
		break;
	case ESPAWNABLE_OBJECT::SLOGRA:
		break;
	}

	SetDead();
}

void CSpawnPoint::Render(HDC _DC)
{
	// 오른쪽일때
	if (GetFaceDir())
	{
		switch (m_eOption)
		{
		case ESPAWNABLE_OBJECT::PLAYER:
			m_pTexture = CResMgr::GetInst()->LoadTexture(L"Right_Arrow", L"texture\\spawn_point\\Right_Arrow.bmp");
			break;
		case ESPAWNABLE_OBJECT::BONE_SCIMITAR:
			m_pTexture = CResMgr::GetInst()->LoadTexture(L"Right_Arrow", L"texture\\spawn_point\\Right_Arrow.bmp");
			break;
		case ESPAWNABLE_OBJECT::AXE_ARMOR:
			break;
		case ESPAWNABLE_OBJECT::SKELETON:
			break;
		case ESPAWNABLE_OBJECT::SPITTLE_BONE:
			break;
		case ESPAWNABLE_OBJECT::GAIBON:
			break;
		case ESPAWNABLE_OBJECT::SLOGRA:
			break;
		}
	}
	// 왼쪽일때
	else
	{
		switch (m_eOption)
		{
		case ESPAWNABLE_OBJECT::PLAYER:
			m_pTexture = CResMgr::GetInst()->LoadTexture(L"Left_Arrow", L"texture\\spawn_point\\Left_Arrow.bmp");
			break;
		case ESPAWNABLE_OBJECT::BONE_SCIMITAR:
			m_pTexture = CResMgr::GetInst()->LoadTexture(L"Left_Arrow", L"texture\\spawn_point\\Left_Arrow.bmp");
			break;
		case ESPAWNABLE_OBJECT::AXE_ARMOR:
			break;
		case ESPAWNABLE_OBJECT::SKELETON:
			break;
		case ESPAWNABLE_OBJECT::SPITTLE_BONE:
			break;
		case ESPAWNABLE_OBJECT::GAIBON:
			break;
		case ESPAWNABLE_OBJECT::SLOGRA:
			break;
		case ESPAWNABLE_OBJECT::NONE:
			break;
		}
	}
		
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	BitBlt(_DC,
	(int)(vPos.x - m_pTexture->GetWidth() / 2.f),
	(int)(vPos.y - m_pTexture->GetHeight()),
	(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
	m_pTexture->GetDC(),
	0, 0,
	SRCCOPY);

	CObj::Render(_DC);
}

void CSpawnPoint::Save(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	fwrite(&m_eOption, sizeof(ESPAWNABLE_OBJECT), 1, _pFile);

	bool bFaceDir = GetFaceDir();
	fwrite(&bFaceDir, sizeof(bool), 1, _pFile);
}

void CSpawnPoint::Load(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	fread(&m_eOption, sizeof(ESPAWNABLE_OBJECT), 1, _pFile);

	bool bFaceDir;
	fread(&bFaceDir, sizeof(bool), 1, _pFile);
	SetFaceDir(bFaceDir);
}
