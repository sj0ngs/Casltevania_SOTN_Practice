#include "pch.h"
#include "CSpawnPoint.h"

#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CObjMgr.h"

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

	if (dynamic_cast<CEditorLevel*>(pCurLevel) || IsDead())
		return;

	switch (m_eOption)
	{
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
		m_pTexture = CResMgr::GetInst()->LoadTexture(L"Right_Arrow", L"texture\\spawn_point\\Right_Arrow.bmp");
	// 왼쪽일때
	else
		m_pTexture = CResMgr::GetInst()->LoadTexture(L"Left_Arrow", L"texture\\spawn_point\\Left_Arrow.bmp");
		
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	BitBlt(_DC,
	(int)(vPos.x - m_pTexture->GetWidth() / 2.f),
	(int)(vPos.y - m_pTexture->GetHeight()),
	(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
	m_pTexture->GetDC(),
	0, 0,
	SRCCOPY);

	CObj::Render(_DC);

	wstring strName;
	switch (m_eOption)
	{
	case ESPAWNABLE_OBJECT::BONE_SCIMITAR:
		strName = L"Bone Scimitar";
		break;
	case ESPAWNABLE_OBJECT::AXE_ARMOR:
		strName = L"Axe Armor";
		break;
	case ESPAWNABLE_OBJECT::SKELETON:
		strName = L"Skeleton";
		break;
	case ESPAWNABLE_OBJECT::SPITTLE_BONE:
		strName = L"Spittle Boner";
		break;
	case ESPAWNABLE_OBJECT::GAIBON:
		strName = L"Gaibon";
		break;
	case ESPAWNABLE_OBJECT::SLOGRA:
		strName = L"Slogra";
		break;
	}

	vPos.y -= ((float)TILE_SIZE * 1.5f);

	TextOut(_DC, (int)vPos.x, (int)vPos.y, strName.c_str(), (int)strName.length());
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
