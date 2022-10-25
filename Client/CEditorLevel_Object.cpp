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
	// ���콺 ���� Ŭ������ �÷��� ��ġ
	if (IS_TAP(EKEY::LBTN))
	{
		// ���콺 ��ġ�� �޾Ƽ� ������ǥ�� ��ȯ
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

	// ��Ŭ������ �÷����� ���ش�
	if (IS_TAP(EKEY::RBTN))
	{
		// ���콺 ��ġ�� �޾Ƽ� ������ǥ�� ��ȯ
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

// Load �Լ����� ��� �������� ����ؾ� �Ǳ� ������ �ֻ��� Level �� ����Ǿ��ִ�
// ������ ������ ���Ǽ��� ���Ͽ� �����δ� ������ �������� �ۼ��Ѵ�
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
