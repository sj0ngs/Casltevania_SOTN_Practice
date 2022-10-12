#include "pch.h"
#include "CUIMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Tick()
{
	// ���� ���� ����
	// UI layer ��������

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(ELAYER::UI);
}
