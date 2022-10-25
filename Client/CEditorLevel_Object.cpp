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

#include "CCollider.h"
#include "CTexture.h"
#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

void CEditorLevel::Object_Update()
{
	switch (m_eObjectOption)
	{
	case EOBJ_OPTION::SPAWN_POINT:
		EditSpawnPoint();
		break;
	case EOBJ_OPTION::OBJECT:
		break;
	case EOBJ_OPTION::TRIGGER:
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

			CSpawnPoint* pSpawnPoint = new CSpawnPoint;
			pSpawnPoint->SetSpawnObjectOption(GetSpawnObjectOption());
			pSpawnPoint->SetPos(vPos);
			pSpawnPoint->SetFaceDir(m_bFaceDir);

			AddObj(pSpawnPoint, ELAYER::SPAWN_POINT);
		}
	}

	// 우클릭으로 플랫폼을 없앤다
	if (IS_TAP(EKEY::RBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	
		const vector<CObj*>& vecSpawnPoint = GetLayer(ELAYER::SPAWN_POINT);

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


// ================
// Level Load Funcs
// ================

// Load 함수들은 모든 레벨에서 사용해야 되기 때문에 최상위 Level 에 선언되어있다
// 하지만 편집의 편의성을 위하여 구현부는 에디터 레벨에다 작성한다
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
