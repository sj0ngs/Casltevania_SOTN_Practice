#include "pch.h"
#include "CDiagonal.h"

#include "CCollider.h"
#include "CLineCollider.h"

CDiagonal::CDiagonal()
{
	CreateCollider(ECOLLIDER_TYPE::LINE);
}

CDiagonal::~CDiagonal()
{
}

void CDiagonal::BeginOverlap(CCollider* _pOther)
{
}

void CDiagonal::OnOverlap(CCollider* _pOther)
{
}

void CDiagonal::EndOverlap(CCollider* _pOther)
{
}
