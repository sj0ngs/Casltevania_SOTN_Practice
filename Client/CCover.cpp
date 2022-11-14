#include "pch.h"
#include "CCover.h"

CCover::CCover()
{
}

CCover::~CCover()
{
}

void CCover::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CCover::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);
}

void CCover::OnOverlap(CCollider* _pOther)
{
}

void CCover::EndOverlap(CCollider* _pOther)
{
}
