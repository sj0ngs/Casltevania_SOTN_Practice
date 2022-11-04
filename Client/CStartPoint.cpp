#include "pch.h"
#include "CStartPoint.h"

#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CObjMgr.h"

#include "clevel.h"
#include "CEditorLevel.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTexture.h"

CStartPoint::CStartPoint() :
	m_iIdx(0),
	m_pTexture(nullptr)
{
	SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
}

CStartPoint::~CStartPoint()
{
}

void CStartPoint::Tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (dynamic_cast<CEditorLevel*>(pCurLevel) || IsDead())
		return;

	if (nullptr != pCurLevel)
	{
		UINT iLevelStart = pCurLevel->GetStartPointIdx();

		if (iLevelStart == m_iIdx)
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::GetInst()->FindObj(L"Player"));
			assert(pPlayer);
			pPlayer = pPlayer->Clone();
			//pPlayer->SetFaceDir(GetFaceDir());
			pPlayer->SetPos(GetPos());
			pCurLevel->AddObj(pPlayer, ELAYER::PLAYER);
		}
	}

	SetDead();
}

void CStartPoint::Render(HDC _DC)
{
	// 오른쪽일때
	if (GetFaceDir())
	{
		m_pTexture = CResMgr::GetInst()->LoadTexture(L"Right_Arrow", L"texture\\spawn_point\\Right_Arrow.bmp");
	}
	// 왼쪽일때
	else
	{
		m_pTexture = CResMgr::GetInst()->LoadTexture(L"Left_Arrow", L"texture\\spawn_point\\Left_Arrow.bmp");
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

	wstring strNum = L"Start Point : ";
	strNum += std::to_wstring(m_iIdx);
	TextOut(_DC, (int)vPos.x, (int)vPos.y - TILE_SIZE, strNum.c_str(), (int)strNum.length());
}

void CStartPoint::Save(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);
	
	fwrite(&m_iIdx, sizeof(UINT), 1, _pFile);

	bool bFaceDir = GetFaceDir();
	fwrite(&bFaceDir, sizeof(bool), 1, _pFile);
}

void CStartPoint::Load(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	fread(&m_iIdx, sizeof(UINT), 1, _pFile);

	bool bFaceDir;
	fread(&bFaceDir, sizeof(bool), 1, _pFile);
	SetFaceDir(bFaceDir);
}