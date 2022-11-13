#include "pch.h"
#include "CSubWeaponUI.h"

#include "CObjMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"

#include "CPlayer.h"

#include "CTexture.h"

CSubWeaponUI::CSubWeaponUI()	:
	m_eType(ESUB_WEAPON_TYPE::NONE),
	m_pTex(nullptr)
{
	CreateAnimator();
	
	GetAnimator()->SetCameraAffected(false);
	GetAnimator()->LoadAnimation(L"animation\\UI\\SUBWEAPON_SHINE.anim");
}

CSubWeaponUI::~CSubWeaponUI()
{
}

void CSubWeaponUI::Tick()
{
	CPlayer* pPlayer = (CPlayer*)CObjMgr::GetInst()->FindObj(L"Player");
	m_eType = pPlayer->GetSubWeapon();
	
	switch (m_eType)
	{
	case ESUB_WEAPON_TYPE::DAGGER:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Dagger_UI");
		break;
	case ESUB_WEAPON_TYPE::AXE:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Axe_UI");
		break;
	case ESUB_WEAPON_TYPE::BIBLE:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Bible_UI");
		break;
	case ESUB_WEAPON_TYPE::NONE:
		m_pTex = nullptr;
		break;
	}

	GetAnimator()->Play(true);

	CObj::Tick();
	CUI::Tick();
}

void CSubWeaponUI::Render(HDC _DC)
{
	if (m_pTex)
	{
		Vec2 vPos = GetPos();

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
}
