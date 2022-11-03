#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CTexture.h"

CCamera::CCamera()	:
	m_vLook{},
	m_vDiff{},
	m_pBlindText(nullptr),
	m_fCameraSpeed(200.f),
	m_iCameraMove(false),
	m_ptResolution{},
	m_iLevelWidth(0.f),
	m_iLevelHeight(0.f),
	m_fRatio(0.f),
	m_bShakeOn(false),
	m_fShakeSpeed(1.f),
	m_fShakeAccTime(0.f),
	m_fShakeMaxTime(0.f),
	m_fShakeRange(0.f),
	m_fShakeDir(1),
	m_vShakeOffset{}
{
	POINT ptResolution = CEngine::GetInst()->GetResolution();

	m_pBlindText = CResMgr::GetInst()->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);
}

CCamera::~CCamera()
{
}

void CCamera::Tick()
{
	if (m_iCameraMove)
	{
		if (IS_PRESSED(EKEY::W))
			m_vLook.y -= m_fCameraSpeed * DELTATIME;

		if (IS_PRESSED(EKEY::S))
			m_vLook.y += m_fCameraSpeed * DELTATIME;

		if (IS_PRESSED(EKEY::A))
			m_vLook.x -= m_fCameraSpeed * DELTATIME;

		if (IS_PRESSED(EKEY::D))
			m_vLook.x += m_fCameraSpeed * DELTATIME;
	}

	CameraShake();

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	m_vDiff = m_vLook + m_vShakeOffset - vResolution;

	CameraEffect();
}

void CCamera::Render(HDC _hDC)
{
	BLENDFUNCTION tBlend = {};
	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	if (0.0001 > m_fRatio)
		return;

	AlphaBlend(_hDC, 0, 0,
		m_pBlindText->GetWidth(), m_pBlindText->GetHeight(),
		m_pBlindText->GetDC(),
		0, 0,
		m_pBlindText->GetWidth(), m_pBlindText->GetHeight(),
		tBlend);
}

void CCamera::CameraEffect()
{
	if (m_CamEffectList.empty())
		return;

	tCamEffect& Effect = m_CamEffectList.front();

	Effect.m_fAccTime += DELTATIME;

	if (Effect.m_fMaxTime <= Effect.m_fAccTime)
	{
		m_CamEffectList.pop_front();
		return;
	}

	m_fRatio = Effect.m_fAccTime / Effect.m_fMaxTime;

	if (ECAMERA_EFFECT::FADE_IN == Effect.m_eCurEffect)
		m_fRatio = 1.f - m_fRatio;
}

void CCamera::CameraShake()
{
	if (!m_bShakeOn)
		return;

	m_fShakeAccTime += DELTATIME;

	if (m_fShakeAccTime >= m_fShakeMaxTime)
	{
		m_bShakeOn = false;
		m_vShakeOffset = Vec2(0.f, 0.f);
	}

	m_vShakeOffset.y += DELTATIME * m_fShakeSpeed * m_fShakeDir;

	if (m_fShakeRange < fabsf(m_vShakeOffset.y))
	{
		m_vShakeOffset.y = m_fShakeRange * m_fShakeDir;
		m_fShakeDir *= -1;
	}
}

void CCamera::FadeOut(float _fTerm)
{
	tCamEffect Effect = {};
	Effect.m_eCurEffect = ECAMERA_EFFECT::FADE_OUT;
	Effect.m_fAccTime = 0.f;
	Effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(Effect);
}

void CCamera::FadeIn(float _fTerm)
{
	tCamEffect Effect = {};
	Effect.m_eCurEffect = ECAMERA_EFFECT::FADE_IN;
	Effect.m_fAccTime = 0.f;
	Effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(Effect);
}

void CCamera::CameraShake(float _fTerm, float _fRange, float _fSpeed)
{
	if (m_bShakeOn)
		return;
	m_bShakeOn = true;
	m_fShakeMaxTime = _fTerm;
	m_fShakeRange = _fRange;
	m_fShakeDir = 1;
	m_fShakeSpeed = _fSpeed;
	m_fShakeAccTime = 0.f;
}

void CCamera::SetMapSize(POINT _ptResoltion, UINT _iLevelWidth, UINT _iLevelHeight)
{
	m_ptResolution = _ptResoltion;

	m_iLevelWidth = _iLevelWidth;
	m_iLevelHeight = _iLevelHeight;
}

void CCamera::TracePlayer(Vec2 _vPos)
{
	if (0 > _vPos.x - (float)m_ptResolution.x / 2.f)
	{
		_vPos.x = (float)m_ptResolution.x / 2.f;
	}
	else if(m_iLevelWidth < _vPos.x + (float)m_ptResolution.x / 2.f)
	{
		_vPos.x = m_iLevelWidth - m_ptResolution.x / 2.f;
	}

	if (0 > _vPos.y - (float)m_ptResolution.y / 2.f)
	{
		_vPos.y = (float)m_ptResolution.y / 2.f;
	}
	else if (m_iLevelHeight < _vPos.y + (float)m_ptResolution.y / 2.f)
	{
		_vPos.y = m_iLevelHeight - m_ptResolution.y / 2.f;
	}

	SetLook(_vPos);
}
