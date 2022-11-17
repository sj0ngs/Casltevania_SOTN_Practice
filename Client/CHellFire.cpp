#include "pch.h"
#include "CHellFire.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CSound.h"

#include "CEffect.h"

CHellFire::CHellFire() :
	m_fSpeed(500.f),
	m_pTex(nullptr),
	m_faccTime(0.f),
	m_fTheta(0.f),
	m_fRatio(0.f),
	m_fDir(0.f),
	m_bIsFire(false)
{
	SetPenatrate(false);

	GetCollider()->SetScale(Vec2(100.f, 100.f));
	m_pTex = CResMgr::GetInst()->FindTexture(L"HellFire");


}

CHellFire::~CHellFire()
{
}

void CHellFire::Tick()
{
	if (!m_bIsFire)
	{
		if (0.5f <= m_faccTime)
		{
			m_faccTime = 0.f;
			m_bIsFire = true;
		}
	}
	else
	{
		Vec2 vPos = GetPos();

		if (GetFaceDir())
			vPos.x += m_fSpeed * DELTATIME;
		else
			vPos.x -= m_fSpeed * DELTATIME;

		SetPos(vPos);

		if (0.2f <= m_faccTime)
		{
			Effect();
			m_faccTime = 0.f;
		}
	}

	m_faccTime += DELTATIME;

	MapOut();
}

void CHellFire::Render(HDC _DC)
{
	Vec2 vPos = {};
	vPos.x= m_pTex->GetWidth() / 2.f;
	vPos.y= m_pTex->GetHeight() / 2.f;

	HDC hMemDC = CreateCompatibleDC(_DC);
	HBITMAP hBit = CreateCompatibleBitmap(_DC, m_pTex->GetWidth(), m_pTex->GetHeight());
	HBITMAP hDefaultBit = (HBITMAP)SelectObject(hMemDC, hBit);
	DeleteObject(hDefaultBit);

	POINT pt[3] = {};	
	Vec2 vScale = {};
	vScale.x = (float)m_pTex->GetWidth();
	vScale.y = (float)m_pTex->GetHeight();

	pt[0].x = (int)(vPos.x - vScale.x / 2.f);
	pt[0].y = (int)(vPos.y - vScale.y / 2.f);
	pt[1].x = (int)(vPos.x + vScale.x / 2.f);
	pt[1].y = (int)(vPos.y - vScale.y / 2.f);
	pt[2].x = (int)(vPos.x - vScale.x / 2.f);
	pt[2].y = (int)(vPos.y + vScale.y / 2.f);

	float fDist[3] = {};
	Vec2 vDir[3] = {};
	Vec2 vRotVec[3] = {};

	m_fTheta += 180.f * DELTATIME * PI / 180;

	for (int i = 0; i < 3; i++)
	{
		vDir[i].x = pt[i].x - vPos.x;
		vDir[i].y = pt[i].y - vPos.y;

		fDist[i] = vDir[i].Length();

		vDir[i].Normalize(); 

		vRotVec[i].x = vDir[i].x * cosf(m_fTheta) - vDir[i].y * sinf(m_fTheta);
		vRotVec[i].y = vDir[i].x * sinf(m_fTheta) + vDir[i].y * cosf(m_fTheta);

		vRotVec[i] *= fDist[i]; 
		 
		pt[i].x = (int)(vRotVec[i].x + vPos.x);
		pt[i].y = (int)(vRotVec[i].y + vPos.y);
	}

	PlgBlt(hMemDC, pt,
		m_pTex->GetDC(),
		0, 0,
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		nullptr, 0, 0);

	m_fRatio += DELTATIME * m_fDir * 10;

	if (1.f <= m_fRatio)
	{
		m_fDir = -1.f;
		m_fRatio = 1.f;
	}
	else if (0.5 >= m_fRatio)
	{
		m_fDir = 1.f;
		m_fRatio = 0.5f;
	}

	BLENDFUNCTION tBlend = {};
	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);

	vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	AlphaBlend(_DC,
		(int)(vPos.x - m_pTex->GetWidth() / 2.f),
		(int)(vPos.y - m_pTex->GetHeight() / 2.f),
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		hMemDC,
		0, 0,
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		tBlend);

	CObj::Render(_DC);

	DeleteObject(hBit);
	DeleteDC(hMemDC);
}

void CHellFire::BeginOverlap(CCollider* _pOther)
{
	//CPlayerProjectile::BeginOverlap(_pOther);

	CObj* pOther = _pOther->GetOwner();
	if (ELAYER::MONSTER == pOther->GetLayer())
	{
		Dead();
	}
}

void CHellFire::Dead()
{
	CEffect* pEffect = new CEffect;
	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\SLOGRA_DEATH_EFFECT.anim");
	pEffect->GetAnimator()->Play(false);

	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	PLAY_SOUND(L"DRACULA_FIRE");
	CProjectile::Dead();
}

void CHellFire::Effect()
{
	Vec2 vPos = GetPos();
	vPos.y += 50.f;

	CEffect* pEffect = new CEffect;

	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\SLOGRA_DEATH_EFFECT.anim");
	pEffect->GetAnimator()->Play(false);

	Instantiate(pEffect, vPos, ELAYER::EFFECT);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Mon_Explot");
	pSound->SetVolume(100.f);
	pSound->Play();
}
