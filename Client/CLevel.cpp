#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

#include "CTile.h"

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
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			m_arrLayer[i][j]->Tick();
		}
	}
}

void CLevel::Final_Tick()
{
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		for (size_t j = 0; j < m_arrLayer[i].size(); j++)
		{
			m_arrLayer[i][j]->Final_Tick();
		}
	}
}

void CLevel::Render(HDC _DC)
{
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
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
