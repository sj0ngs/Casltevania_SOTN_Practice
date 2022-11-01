#include "pch.h"
#include "CItem.h"

CItem::CItem()	:
	m_pItemTex(nullptr)
{
	CreateCollider();
}

CItem::~CItem()
{
}

void CItem::Render(HDC _DC)
{
	if (nullptr != m_pItemTex)
	{

	}
}

void CItem::BeginOverlap(CCollider* _pOther)
{
}

void CItem::OnOverlap(CCollider* _pOther)
{
}

void CItem::EndOverlap(CCollider* _pOther)
{
}
