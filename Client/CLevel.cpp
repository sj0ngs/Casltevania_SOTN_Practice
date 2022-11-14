#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CObjMgr.h"
#include "CTimeMgr.h"
#include "CPlayer.h"

#include "CLine.h"
#include "CTile.h"
#include "CBackGround.h"

#include "CTexture.h"

#include "CHUD.h"
#include "CMPBar.h"
#include "CHP.h"
#include "CHeartUI.h"
#include "CSubWeaponUI.h"

CLevel::CLevel()	:
	m_iStartPointIdx(0),
	m_iTileXCount(0),
	m_iTileYCount(0),
	m_iWidth(0),
	m_iHeight(0)
{
}

CLevel::~CLevel()
{
	DeleteAllObject();
}

void CLevel::Tick()
{
	FindTileSreen();
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		if (i == (UINT)ELAYER::TILE)
		{
			for (int j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->Tick();
			}
		}
		else
		{
			for (size_t j = 0; j < m_arrLayer[i].size(); j++)
			{
				m_arrLayer[i][j]->Tick();
			}
		}
	}
}

void CLevel::Final_Tick()
{
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		if (i == (UINT)ELAYER::TILE)
		{
			for (int j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->Tick();
			}
		}
		else
		{
 			for (size_t j = 0; j < m_arrLayer[i].size(); j++)
			{
				m_arrLayer[i][j]->Final_Tick();
			}
		}
	}
}

void CLevel::Render(HDC _DC)
{
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		if (i == (UINT)ELAYER::TILE)
		{
			for (int j = 0; j < m_vecTile.size(); j++)
			{
				m_vecTile[j]->Render(_DC);
			}
		}
		else
		{
			vector<CObj*>::iterator iter = m_arrLayer[i].begin();

			for (; iter != m_arrLayer[i].end();)
			{
				if ((*iter)->IsDead())
					iter = m_arrLayer[i].erase(iter);
				else
				{
					(*iter)->Render(_DC);
					++iter;
				}
			}
		}
	}
}

void CLevel::Enter()
{
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetMapSize(ptResolution, m_iWidth, m_iHeight);

	//CTimeMgr::GetInst()->SetTimeLock(false);
}

void CLevel::Exit()
{
	POINT ptResolution = {};
	CCamera::GetInst()->SetMapSize(ptResolution, 0, 0);

	CTimeMgr::GetInst()->SetTimeLock(true);
}

void CLevel::LoadLevel(const wstring& _strRelativePath)
{
	FILE* pFile = nullptr;

	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	strContentPath += _strRelativePath;

	_wfopen_s(&pFile, strContentPath.c_str(), L"rb");

	if (nullptr != pFile)
	{
		LoadBackGround(pFile);
		LoadForeGround(pFile);
		LoadPlatform(pFile);
		LoadLine(pFile);

		LoadStartPoint(pFile);
		LoadSpawnPoint(pFile);
		LoadTrigger(pFile);

		fclose(pFile);
	}
}

void CLevel::AddObj(CObj* _pObj, ELAYER _Layer)
{
	m_arrLayer[(UINT)_Layer].push_back(_pObj); 
	_pObj->SetLayer(_Layer);
}

CPlayer* CLevel::GetPlayer()
{
	assert(!m_arrLayer[(UINT)ELAYER::PLAYER].empty());

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_arrLayer[(UINT)ELAYER::PLAYER][0]);

	return pPlayer;
}

void CLevel::DeleteAllObject()
{
	// 오브젝트 삭제
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			DYNAMIC_DELETE(m_arrLayer[i][j]);
		}
		m_arrLayer[i].clear();
	}

	for (size_t i = 0; i < m_vecLine.size(); i++)
	{
		if (m_vecLine[i]->IsDead())
			continue;

		DYNAMIC_DELETE(m_vecLine[i]);
	}
	m_vecLine.clear();
}

void CLevel::DeleteObject(ELAYER _Layer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_Layer].size(); i++)
	{
		delete m_arrLayer[(UINT)_Layer][i];
	}
	m_arrLayer[(UINT)_Layer].clear();
}

void CLevel::CreateTile(UINT _X, UINT _Y)
{
	DeleteObject(ELAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	for (UINT iRow = 0; iRow < m_iTileYCount; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; iCol++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol), (float)(TILE_SIZE * iRow)));
			AddObj(pTile, ELAYER::TILE);
		}
	}
}

void CLevel::SetFocusedUI(CObj* _pUI)
{
	vector<CObj*>& vecUI = m_arrLayer[(UINT)ELAYER::UI];

	if (vecUI.back() == _pUI)
		return;

	vector<CObj*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	assert(nullptr);
}

void CLevel::CreateHUD()
{
	// UI 배치

	// MP Bar
	CMPBar* pMPBar = new CMPBar;
	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"MPBar");
	pMPBar->SetIdleTex(pTex);
	pMPBar->SetPos(Vec2(130.f, 42.f));

	// SubWeapon UI
	CSubWeaponUI* pSbUI = new CSubWeaponUI;
	pSbUI->SetPos(Vec2(390.f, 56.f));

	// HUD
	CHUD* pHUD = new CHUD;
	pTex = CResMgr::GetInst()->FindTexture(L"HUD");
	pHUD->SetIdleTex(pTex);
	pHUD->SetPos(Vec2(10.f, 10.f));

	// HP 
	CHP* pHP = new CHP;
	pTex = CResMgr::GetInst()->FindTexture(L"HP_Num");
	pHP->SetPos(Vec2(40.f, 56.f));
	pHP->SetIdleTex(pTex);
	pHUD->AddChildUI(pHP);

	// Heart
	CHeartUI* pHeart = new CHeartUI;
	pTex = CResMgr::GetInst()->FindTexture(L"Heart_Num");
	pHeart->SetPos(Vec2(232.f, 52.f));
	pHeart->SetIdleTex(pTex);
	pHUD->AddChildUI(pHeart);
	
	AddObj(pMPBar, ELAYER::UI);
	AddObj(pSbUI, ELAYER::UI);
	AddObj(pHUD, ELAYER::UI);
}

void CLevel::FindTileSreen()
{
	m_vecTile.clear();

	Vec2 vLeftTop = CCamera::GetInst()->GetLook();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vLeftTop -= (vResolution / 2.f);

	int iLTCol = (int)vLeftTop.x / TILE_SIZE;
	int iLTRow = (int)vLeftTop.y / TILE_SIZE;

	if (0.f > vLeftTop.x)
		iLTCol = 0;
	if (0.f > vLeftTop.y)
		iLTRow = 0;

	int iMaxCol = ((int)vResolution.x / TILE_SIZE) + iLTCol + 1;
	int iMaxRow = ((int)vResolution.y / TILE_SIZE) + iLTRow + 2;

	if (m_iTileXCount < (unsigned int)iMaxCol)
		iMaxCol = m_iTileXCount;
	if (m_iTileYCount < (unsigned int)iMaxRow)
		iMaxRow = m_iTileYCount;

	for (int iRow = iLTRow; iRow < iMaxRow; iRow++)
	{
		for (int iCol = iLTCol; iCol < iMaxCol; iCol++)
		{
			int iTileIdx = iRow * m_iTileXCount + iCol;
			m_vecTile.push_back(m_arrLayer[(UINT)ELAYER::TILE][iTileIdx]);
		}
	}
}
