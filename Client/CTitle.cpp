#include "pch.h"
#include "CTitle.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CEffect.h"
#include "CAnimDebug.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CSound.h"

CTitle::CTitle()	:
	m_pBackGround(nullptr),
	m_pTitle(nullptr),
	m_pStartMode(nullptr),
	m_pDebugMode(nullptr),
	m_pSelect(nullptr),
	m_eSelect(ETITLE_SELECT::START),
	m_vTitle(510.f, 260.f),
	m_vStartMode(510.f, 460.f),
	m_vDebugMode(510.f, 560.f),
	m_faccStartTime(0.f),
	m_bStart(false)
{
}

CTitle::~CTitle()
{
}

void CTitle::Init()
{
	m_pBackGround = CResMgr::GetInst()->FindTexture(L"Title_BackGround");
	m_pTitle = CResMgr::GetInst()->FindTexture(L"Title");
	m_pStartMode = CResMgr::GetInst()->FindTexture(L"Game_Start_Select");
	m_pDebugMode = CResMgr::GetInst()->FindTexture(L"Debug_Mode_Select");
	m_pSelect = CResMgr::GetInst()->FindTexture(L"Select_Frame");

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	Vec2 vPos = {};

	vPos.x = vResolution.x - 512.f / 2.f;
	vPos.y = vResolution.y - 266.f / 2.f;

	CAnimDebug* pObj = new CAnimDebug;
	pObj->GetAnimator()->LoadAnimation(L"animation\\UI\\TITLE_ANIM.anim");
	pObj->GetAnimator()->Play(true);
	pObj->GetCollider()->SetScale(Vec2(0.f, 0.f));
	Instantiate(pObj, vPos, ELAYER::OBJECT);

	vPos.x = 512.f / 2.f;
	vPos.y = 134.f / 2.f;

	pObj = new CAnimDebug;
	pObj->GetAnimator()->LoadAnimation(L"animation\\UI\\TITLE_ANIM_2.anim");
	pObj->GetAnimator()->Play(true);
	pObj->GetCollider()->SetScale(Vec2(0.f, 0.f));
	Instantiate(pObj, vPos, ELAYER::OBJECT);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Prayer");
	pSound->PlayToBGM(true);
}

void CTitle::Tick()
{
	if (IS_TAP(EKEY::ENTER))
	{
		switch (m_eSelect)
		{
		case ETITLE_SELECT::START:
		{
			CCamera::GetInst()->FadeOut(1.f);

			CSound* pSound = CResMgr::GetInst()->FindSound(L"Start");
			pSound->Play();

			m_bStart = true;
		}
			break;
		case ETITLE_SELECT::DEBUG:
			ChangeLevel(ELEVEL_TYPE::EDITOR);
			CSound* pSound = CResMgr::GetInst()->FindSound(L"Prayer");
			pSound->Stop();
			break;
		}
	}
	else if (IS_TAP(EKEY::UP) || IS_TAP(EKEY::DOWN))
	{
		ChangeMode();
	}

	if (m_bStart)
	{
		m_faccStartTime += DELTATIME;

		if (1.f <= m_faccStartTime)
		{
			m_bStart = false;
			m_faccStartTime = 0.f;

			// Sound 실행
			CSound* pSound = CResMgr::GetInst()->FindSound(L"Dance_of_Gold");
			pSound->PlayToBGM(true);

			CCamera::GetInst()->FadeIn(0.1f);
			ChangeLevel(ELEVEL_TYPE::START);
		}
	}

	CLevel::Tick();
}

void CTitle::Render(HDC _DC)
{
	TransparentBlt(_DC,
		0, 0,
		(int)(m_pBackGround->GetWidth()),
		(int)(m_pBackGround->GetHeight()),
		m_pBackGround->GetDC(),
		0, 0,
		(int)(m_pBackGround->GetWidth()),
		(int)(m_pBackGround->GetHeight()),
		RGB(255, 0, 255));

	// Title 출력
	TransparentBlt(_DC,
		(int)(m_vTitle.x - m_pTitle->GetWidth() / 2.f),
		(int)(m_vTitle.y - m_pTitle->GetHeight() / 2.f),
		(int)(m_pTitle->GetWidth()),
		(int)(m_pTitle->GetHeight()),
		m_pTitle->GetDC(),
		0, 0,
		(int)(m_pTitle->GetWidth()),
		(int)(m_pTitle->GetHeight()),
		RGB(255, 0, 255));

	static float fRatio = 0.f;
	static float Dir = 1;
	fRatio += DELTATIME * Dir * 3;

	if (1.f <= fRatio)
	{
		Dir = -1.f;
		fRatio = 1.f;
	}
	else if (0 >= fRatio)
	{
		Dir = 1.f;
		fRatio = 0.f;
	}

	BLENDFUNCTION tBlend = {};
	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * fRatio);

	// Start 출력
	if (ETITLE_SELECT::START == m_eSelect)
	{
		AlphaBlend(_DC,
			(int)(m_vStartMode.x - m_pStartMode->GetWidth() / 2.f),
			(int)(m_vStartMode.y - m_pStartMode->GetHeight() / 2.f),
			(int)m_pStartMode->GetWidth(), (int)m_pStartMode->GetHeight(),
			m_pStartMode->GetDC(),
			0, 0,
			(int)m_pStartMode->GetWidth(), (int)m_pStartMode->GetHeight(),
			tBlend);

		TransparentBlt(_DC,
			(int)(m_vDebugMode.x - m_pDebugMode->GetWidth() / 2.f),
			(int)(m_vDebugMode.y - m_pDebugMode->GetHeight() / 2.f),
			(int)(m_pDebugMode->GetWidth()),
			(int)(m_pDebugMode->GetHeight()),
			m_pDebugMode->GetDC(),
			0, 0,
			(int)(m_pDebugMode->GetWidth()),
			(int)(m_pDebugMode->GetHeight()),
			RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_DC,
			(int)(m_vStartMode.x - m_pStartMode->GetWidth() / 2.f),
			(int)(m_vStartMode.y - m_pStartMode->GetHeight() / 2.f),
			(int)(m_pStartMode->GetWidth()),
			(int)(m_pStartMode->GetHeight()),
			m_pStartMode->GetDC(),
			0, 0,
			(int)(m_pStartMode->GetWidth()),
			(int)(m_pStartMode->GetHeight()),
			RGB(255, 0, 255));

		AlphaBlend(_DC,
			(int)(m_vDebugMode.x - m_pDebugMode->GetWidth() / 2.f),
			(int)(m_vDebugMode.y - m_pDebugMode->GetHeight() / 2.f),
			(int)m_pDebugMode->GetWidth(), (int)m_pDebugMode->GetHeight(),
			m_pDebugMode->GetDC(),
			0, 0,
			(int)m_pDebugMode->GetWidth(), (int)m_pDebugMode->GetHeight(),
			tBlend);
	}

	Vec2 vPos = {};
	switch (m_eSelect)
	{
	case ETITLE_SELECT::START:
		vPos = m_vStartMode;
		break;
	case ETITLE_SELECT::DEBUG:
		vPos = m_vDebugMode;
		break;
	}

	TransparentBlt(_DC,
		(int)(vPos.x - m_pSelect->GetWidth() / 2.f),
		(int)(vPos.y - m_pSelect->GetHeight() / 2.f),
		(int)(m_pSelect->GetWidth()),
		(int)(m_pSelect->GetHeight()),
		m_pSelect->GetDC(),
		0, 0,
		(int)(m_pSelect->GetWidth()),
		(int)(m_pSelect->GetHeight()),
		RGB(255, 0, 255));

	CLevel::Render(_DC);
}

void CTitle::Enter()
{
	Init();

	CTimeMgr::GetInst()->SetTimeLock(false);

	CLevel::Enter();
}

void CTitle::Exit()
{
	DeleteAllObject();

	CLevel::Exit();
}

void CTitle::ChangeMode()
{
	if (ETITLE_SELECT::START == m_eSelect)
	{
		m_eSelect = ETITLE_SELECT::DEBUG;
	}
	else
	{
		m_eSelect = ETITLE_SELECT::START;
	}

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Select_Change");
	pSound->Play();
}
