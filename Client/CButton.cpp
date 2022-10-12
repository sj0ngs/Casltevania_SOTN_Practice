#include "pch.h"
#include "CButton.h"

#include "CLevelMgr.h"
#include "CEditorLevel.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

void CButton::MouseLbtnClicked()
{
	//CEditorLevel* pLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

	//if (nullptr == pLevel)
	//	return;

	//pLevel->SaveTile();
}
