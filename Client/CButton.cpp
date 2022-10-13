#include "pch.h"
#include "CButton.h"

#include "CLevelMgr.h"
#include "CEditorLevel.h"

#include "CTexture.h"

CButton::CButton()	:
	m_pInst(nullptr),
	m_pDelegateFunc(nullptr),
	m_pPressTex(nullptr),
	m_pHighlightTex(nullptr)
{

}

CButton::~CButton()
{
}

void CButton::Render(HDC _DC)
{
	CTexture* pTargetTex = GetIdleTex();

	if (IsLbtnDown())
	{
		if (m_pPressTex)
			pTargetTex = m_pPressTex;
	}
	else if (IsMouseOn())
	{
		if (m_pHighlightTex)
			pTargetTex = m_pHighlightTex;
	}
	
	if (!pTargetTex)
	{
		CUI::Render(_DC);
		return;
	}

	Vec2 vPos = GetFinalPos();
	// 카메라에 영향을 받으면(몬스터 HP 등) 랜더 포즈로 변환
	if (IsCameraAffected())
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	BitBlt(_DC,
		(int)vPos.x,
		(int)vPos.y,
		(int)pTargetTex->GetWidth(),
		(int)pTargetTex->GetHeight(),
		pTargetTex->GetDC(),
		0, 0,
		SRCCOPY);

	Render_ChildUI(_DC);
}

void CButton::MouseLbtnDown()
{
	CUI::MouseLbtnDown();
}

void CButton::MouseLbtnClicked()
{
	if (m_pInst && m_pDelegateFunc)
		(m_pInst->*m_pDelegateFunc)();
}
