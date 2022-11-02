#include "pch.h"
#include "CDagger.h"

#include "CResMgr.h"
#include "CTexture.h"

CDagger::CDagger()	:
	m_fSpeed(1000.f),
	m_pRightTex(nullptr),
	m_pLeftTex(nullptr)
{
	GetCollider()->SetScale(Vec2(70.f, 20.f));
	m_pRightTex = CResMgr::GetInst()->LoadTexture(L"Dagger_Right", L"texture\\Weapon\\Dagger_Right.bmp");
	m_pLeftTex = CResMgr::GetInst()->LoadTexture(L"Dagger_Left", L"texture\\Weapon\\Dagger_Left.bmp");
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
