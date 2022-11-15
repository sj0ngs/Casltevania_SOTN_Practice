#include "pch.h"
#include "CEndingLevel.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CEffect.h"
#include "CAnimDebug.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CTexture.h"
#include "CSound.h"

CEndingLevel::CEndingLevel()	:
	m_pEnding(nullptr),
	m_vScenePos{},
	m_bScrollEnd(false)
{
}

CEndingLevel::~CEndingLevel()
{
}

void CEndingLevel::Init()
{
	m_pEnding = CResMgr::GetInst()->FindTexture(L"Ending");

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	m_vScenePos = vResolution / 2.f;
	m_vScenePos.y += 118.f;

	CSound* pSound = CResMgr::GetInst()->FindSound(L"I_Am_The_Wind");
	pSound->PlayToBGM(true);

	CCamera::GetInst()->FadeIn(5.f);
}

void CEndingLevel::Tick()
{
	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::TITLE);
	}

	if (!m_bScrollEnd)
	{
		m_vScenePos.y -= DELTATIME * 20.f;
		if (360.f >= m_vScenePos.y)
		{
			m_bScrollEnd = true;
		}
	}

}

void CEndingLevel::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vScenePos);

	BitBlt(_DC,
		(int)(vPos.x - m_pEnding->GetWidth() / 2.f),
		(int)(vPos.y - m_pEnding->GetHeight() / 2.f),
		(int)(m_pEnding->GetWidth()),
		(int)(m_pEnding->GetHeight()),
		m_pEnding->GetDC(),
		0, 0,
		SRCCOPY);
}

void CEndingLevel::Enter()
{
	Init();

	CTimeMgr::GetInst()->SetTimeLock(false);

	CLevel::Enter();
}

void CEndingLevel::Exit()
{
	DeleteAllObject();

	CLevel::Exit();

	m_bScrollEnd = false;
}
