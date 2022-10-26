#include "pch.h"
#include "CEditorLevel.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"

#include "CSpawnPoint.h"
#include "CStartPoint.h"
#include "CTrigger.h"
#include "CLevelChangeTrigger.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

void CEditorLevel::Object_Update()
{
	switch (m_eObjectOption)
	{
	case EOBJ_OPTION::PLAYER_START_POINT:
	case EOBJ_OPTION::SPAWN_POINT:
		EditSpawnPoint();
		break;
	case EOBJ_OPTION::OBJECT:
		break;
	case EOBJ_OPTION::TRIGGER:
		EditTrigger();
		break;
	}
}

void CEditorLevel::EditSpawnPoint()
{
	// 마우스 왼쪽 클릭으로 플랫폼 설치
	if (IS_TAP(EKEY::LBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && (int)GetTileXCount() > iCol &&
			0.f <= vMousePos.y && (int)GetTileYCount() > iRow)
		{
			int iIdx = iRow * GetTileXCount() + iCol;

			const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);

			Vec2 vPos = vecTile[iIdx]->GetPos();
			vPos.x += (float)(TILE_SIZE / 2.f);
			vPos.y += (float)(TILE_SIZE);

			if (m_eObjectOption == EOBJ_OPTION::PLAYER_START_POINT)
			{
				CStartPoint* pStartPoint = new CStartPoint;
				pStartPoint->SetPos(vPos);
				pStartPoint->SetFaceDir(m_bFaceDir);
				pStartPoint->SetStartIdx(GetStartPointIdx());

				AddObj(pStartPoint, ELAYER::PLAYER_START);
			}
			else
			{
				CSpawnPoint* pSpawnPoint = new CSpawnPoint;
				pSpawnPoint->SetSpawnObjectOption(GetSpawnObjectOption());
				pSpawnPoint->SetPos(vPos);
				pSpawnPoint->SetFaceDir(m_bFaceDir);

				AddObj(pSpawnPoint, ELAYER::SPAWN_POINT);
			}
		}
	}

	// 우클릭으로 플랫폼을 없앤다
	if (IS_TAP(EKEY::RBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	
		ELAYER eLayer = ELAYER::SPAWN_POINT;
		if (m_eObjectOption == EOBJ_OPTION::PLAYER_START_POINT)
		{
			eLayer = ELAYER::PLAYER_START;
		}
		const vector<CObj*>& vecSpawnPoint = GetLayer(eLayer);

		for (size_t i = 0; i < vecSpawnPoint.size(); i++)
		{
			Vec2 vPos = vecSpawnPoint[i]->GetPos();
			Vec2 vScale = vecSpawnPoint[i]->GetScale();
			vScale /= 2.f;

			if (vPos.x - vScale.x <= vMousePos.x && vPos.x + vScale.x >= vMousePos.x &&
				vPos.y - vScale.y * 2.f <= vMousePos.y && vPos.y >= vMousePos.y)
			{
				vecSpawnPoint[i]->SetDead();
				break;
			}
		}
	}
}

void CEditorLevel::EditObject()
{
}

void CEditorLevel::EditTrigger()
{
	// 마우스 왼쪽 클릭으로 트리거 설치
	if (IS_TAP(EKEY::LBTN))
	{
		if (m_vMousePos1 == Vec2(-1.f, -1.f))
		{
			// 마우스 위치를 받아서 실제좌표로 변환
			Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

			int iCol = (int)vMousePos.x / TILE_SIZE;
			int iRow = (int)vMousePos.y / TILE_SIZE;

			if (0.f <= vMousePos.x && (int)GetTileXCount() > iCol &&
				0.f <= vMousePos.y && (int)GetTileYCount() > iRow)
			{
				int iIdx = iRow * GetTileXCount() + iCol;

				const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
				m_vMousePos1 = vecTile[iIdx]->GetPos();
			}
		}
		else
		{
			// 마우스 위치를 받아서 실제좌표로 변환
			Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

			int iCol = (int)vMousePos.x / TILE_SIZE;
			int iRow = (int)vMousePos.y / TILE_SIZE;

			if (0.f <= vMousePos.x && (int)GetTileXCount() > iCol &&
				0.f <= vMousePos.y && (int)GetTileYCount() > iRow)
			{
				int iIdx = iRow * GetTileXCount() + iCol;

				const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
				Vec2 vPos = vecTile[iIdx]->GetPos();
				vPos += Vec2((float)TILE_SIZE, (float)TILE_SIZE);

				if (m_vMousePos1.x > vPos.x)
				{
					float temp = m_vMousePos1.x;
					m_vMousePos1.x = vPos.x;
					vPos.x = temp;
					m_vMousePos1.x -= TILE_SIZE;
					vPos.x += TILE_SIZE;
				}
				if (m_vMousePos1.y > vPos.y)
				{
					float temp = m_vMousePos1.y;
					m_vMousePos1.y = vPos.y;
					vPos.y = temp;
					m_vMousePos1.y -= TILE_SIZE;
					vPos.y += TILE_SIZE;
				}
				if (m_vMousePos1.x < vPos.x && m_vMousePos1.y < vPos.y)
				{
					Vec2 vScale = vPos - m_vMousePos1;
					m_vMousePos1 += (vScale / 2.f);

					CTrigger* pTrigger = nullptr;

					switch (m_eTriggerType)
					{
					case ETRIGGER_TYPE::LEVEL_CHANGE:
					{
						CLevelChangeTrigger* pLevelChange = new CLevelChangeTrigger();
						pLevelChange->GetCollider()->SetScale(vScale);
						pLevelChange->SetPos(m_vMousePos1);
						pLevelChange->SetLevelType(GetChangeLevelType());
						pLevelChange->SetStartPointIdx(GetStartPointIdx());
						pTrigger = pLevelChange;
					}
						break;
					}
					AddObj(pTrigger, ELAYER::TRIGGER);
				}
			}
			m_vMousePos1 = Vec2(-1.f, -1.f);
		}
	}

	// 우클릭으로 플랫폼을 없앤다
	if (IS_TAP(EKEY::RBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		const vector<CObj*>& vecTrigger = GetLayer(ELAYER::TRIGGER);

		for (size_t i = 0; i < vecTrigger.size(); i++)
		{
			Vec2 vPos = vecTrigger[i]->GetPos();
			Vec2 vScale = vecTrigger[i]->GetCollider()->GetScale();
			vScale /= 2.f;

			if (vPos.x - vScale.x <= vMousePos.x && vPos.x + vScale.x >= vMousePos.x &&
				vPos.y - vScale.y <= vMousePos.y && vPos.y + vScale.y >= vMousePos.y)
			{
				vecTrigger[i]->SetDead();
				break;
			}
		}
	}
}

void CEditorLevel::SaveStartPoint(FILE* _pFile)
{
	const vector<CObj*>& vecStartPoint = GetLayer(ELAYER::PLAYER_START);

	size_t iSize = vecStartPoint.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecStartPoint[i]->Save(_pFile);
	}
}

void CEditorLevel::SaveSpawnPoint(FILE* _pFile)
{
	const vector<CObj*>& vecSpawnPoint = GetLayer(ELAYER::SPAWN_POINT);

	size_t iSize = vecSpawnPoint.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecSpawnPoint[i]->Save(_pFile);
	}
}

void CEditorLevel::SaveTrigger(FILE* _pFile)
{
	const vector<CObj*>& vecTrigger = GetLayer(ELAYER::TRIGGER);

	size_t iSize = vecTrigger.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CTrigger* pTrigger = (CTrigger*)vecTrigger[i];

		ETRIGGER_TYPE eType = pTrigger->GetTriggerType();

		fwrite(&eType, sizeof(ETRIGGER_TYPE), 1, _pFile);
		vecTrigger[i]->Save(_pFile);
	}
}

// ================
// Level Load Funcs
// ================
// 
// Load 함수들은 모든 레벨에서 사용해야 되기 때문에 최상위 Level 에 선언되어있다
// 하지만 편집의 편의성을 위하여 구현부는 에디터 레벨에다 작성한다

void CLevel::LoadStartPoint(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CStartPoint* pStartPoint = new CStartPoint;
		pStartPoint->Load(_pFile);
		AddObj(pStartPoint, ELAYER::PLAYER_START);
	}
}

void CLevel::LoadSpawnPoint(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CSpawnPoint* pSpawnPoint = new CSpawnPoint;
		pSpawnPoint->Load(_pFile);
		AddObj(pSpawnPoint, ELAYER::SPAWN_POINT);
	}
}

void CLevel::LoadTrigger(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		ETRIGGER_TYPE _eType;
		fread(&_eType, sizeof(ETRIGGER_TYPE), 1, _pFile);

		CTrigger* pTrigger = nullptr;
		switch (_eType)
		{
		case ETRIGGER_TYPE::LEVEL_CHANGE:
			pTrigger = new CLevelChangeTrigger;
			break;
		}
		pTrigger->Load(_pFile);
		AddObj(pTrigger, ELAYER::TRIGGER);
	}
}
