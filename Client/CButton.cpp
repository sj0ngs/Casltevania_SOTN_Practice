#include "pch.h"
#include "CButton.h"

#include "CLevelMgr.h"
#include "CEditorLevel.h"

CButton::CButton()	:
	m_pInst(nullptr),
	m_pDelegateFunc(nullptr)
{
}

CButton::~CButton()
{
}

void CButton::Render(HDC _DC)
{
	CUI::Render(_DC);
}

void CButton::MouseLbtnClicked()
{
	//CEditorLevel* pLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

	//if (nullptr == pLevel)
	//	return;

	//pLevel->SaveTile();

	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}
}
