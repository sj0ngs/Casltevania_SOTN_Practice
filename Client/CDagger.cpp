#include "pch.h"
#include "CDagger.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CEffect.h"
#include "CAnimator.h"

CDagger::CDagger()	:
	m_fSpeed(1000.f),
	m_pRightTex(nullptr),
	m_pLeftTex(nullptr)
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

	SetPos(vPos);

	MapOut();
}

void CDagger::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

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
