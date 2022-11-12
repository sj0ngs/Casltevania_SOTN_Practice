#include "pch.h"
#include "CButtonTrigger.h"

#include "CResMgr.h"

#include "CCollider.h"

#include "CTexture.h"

CButtonTrigger::CButtonTrigger() :
	m_iBoxIdx(0),
	m_pTex(nullptr),
	m_vOffset(0.f, -10.f)
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"Button");
	SetTriggerType(ETRIGGER_TYPE::BUTTON);
}

CButtonTrigger::~CButtonTrigger()
{
}

void CButtonTrigger::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	vPos += m_vOffset;

	TransparentBlt(_DC,
		(int)(vPos.x - m_pTex->GetWidth() / 2.f),
		(int)(vPos.y - m_pTex->GetHeight() / 2.f),
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		m_pTex->GetDC(),
		0, 0,
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		RGB(255, 0, 255));

	CObj::Render(_DC);
}

void CButtonTrigger::BeginOverlap(CCollider* _pOther)
{
	m_vOffset = Vec2(0.f, 0.f);
}

void CButtonTrigger::OnOverlap(CCollider* _pOther)
{
}

void CButtonTrigger::EndOverlap(CCollider* _pOther)
{
	m_vOffset = Vec2(0.f, -10.f);
}

void CButtonTrigger::Save(FILE* _pFile)
{
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	Vec2 vScale = GetCollider()->GetScale();
	fwrite(&vScale, sizeof(Vec2), 1, _pFile);

	fwrite(&m_iBoxIdx, sizeof(UINT), 1, _pFile);
}

void CButtonTrigger::Load(FILE* _pFile)
{
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	Vec2 vScale;
	fread(&vScale, sizeof(Vec2), 1, _pFile);
	GetCollider()->SetScale(vScale);

	fread(&m_iBoxIdx, sizeof(UINT), 1, _pFile);
}
