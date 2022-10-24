#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CPathMgr.h"

#include "CLine.h"
#include "CTile.h"
#include "CBackGround.h"

CLevel::CLevel()	:
	m_iTileXCount(0),
	m_iTileYCount(0)
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

		fclose(pFile);
	}
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
