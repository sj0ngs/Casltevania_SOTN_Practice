#include "pch.h"
#include "CDagger.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CEffect.h"
#include "CAnimator.h"

CDagger::CDagger()	:
	m_fSpeed(1000.f),
	m_pRightTex(nullptr),
	m_pLeftTex(nullptr),
	m_faccTime(0.f)
{
	SetPenatrate(false);

	GetCollider()->SetScale(Vec2(70.f, 20.f));
	m_pRightTex = CResMgr::GetInst()->FindTexture(L"Dagger_Right");
	m_pLeftTex = CResMgr::GetInst()->FindTexture(L"Dagger_Left");
}

CDagger::~CDagger()
{
}

void CDagger::Tick()
{
	Vec2 vPos = GetPos();

	if (GetFaceDir())
		vPos.x += m_fSpeed * DELTATIME;
	else
		vPos.x -= m_fSpeed * DELTATIME;

	m_faccTime += DELTATIME;

	SetPos(vPos);

	MapOut();
}

void CDagger::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	HPEN hPen = nullptr;

	hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::DAGGER_TRAIL);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	Vec2 vPos1 = GetPos();
	if (GetFaceDir())
	{	
		vPos1.x -= 200.f * (m_faccTime + 0.5f);
	}
	else
	{
		vPos1.x += 200.f * (m_faccTime + 0.5f);
	}
	vPos1 = CCamera::GetInst()->GetRenderPos(vPos1);

	MoveToEx(_DC, (int)vPos1.x, (int)vPos1.y, NULL);
	LineTo(_DC, (int)vPos.x, (int)vPos.y);

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);

	CTexture* pTex = nullptr;
	if (GetFaceDir())
		pTex = m_pRightTex;
	else
		pTex = m_pLeftTex;

	TransparentBlt(_DC,
		(int)(vPos.x - pTex->GetWidth() / 2.f),
		(int)(vPos.y - pTex->GetHeight() / 2.f),
		(int)(pTex->GetWidth()), 
		(int)(pTex->GetHeight()),
		pTex->GetDC(),
		0, 0,
		(int)(pTex->GetWidth()),
		(int)(pTex->GetHeight()),
		RGB(255, 0, 255));

	CObj::Render(_DC);
}

void CDagger::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);
}

void CDagger::Dead()
{
	CEffect* pEffect = new CEffect;
	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\HIT_EFFECT.anim");
	pEffect->GetAnimator()->Play(L"Hit_Effect", false);

	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	CProjectile::Dead();
}
