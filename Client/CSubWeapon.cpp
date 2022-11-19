#include "pch.h"
#include "CSubWeapon.h"

#include "CCamera.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CPlayer.h"

#include "CSound.h"

CSubWeapon::CSubWeapon() :
	m_eType(ESUB_WEAPON_TYPE::NONE),
	m_pTex(nullptr),
	vOffsetPos{},
	m_faccDeathTime(0.f),
	m_bDeadSoon(false),
	m_fRatio(0.f),
	m_fDir(1.f)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();

	GetCollider()->SetScale(Vec2(80.f, 80.f));

	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(1000.f);

	GetAnimator()->LoadAnimation(L"animation\\Effect\\DROP_SUBWEAPON.anim");
}

CSubWeapon::~CSubWeapon()
{
}

void CSubWeapon::SetSubWeaponType(ESUB_WEAPON_TYPE _eType)
{
	m_eType = _eType;

	switch (m_eType)
	{
	case ESUB_WEAPON_TYPE::DAGGER:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Drop_Dagger");
		GetCollider()->SetScale(Vec2(80.f, 20.f));
		break;
	case ESUB_WEAPON_TYPE::AXE:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Drop_Axe");
		break;
	case ESUB_WEAPON_TYPE::BIBLE:
		m_pTex = CResMgr::GetInst()->FindTexture(L"Bible");
		GetCollider()->SetScale(Vec2(60.f, 80.f));
		break;
	}

	GetAnimator()->Play(L"Drop_SubWeapon");
}


void CSubWeapon::Tick()
{
	m_faccDeathTime += DELTATIME;

	if (!m_bDeadSoon)
	{
		if (3.f <= m_faccDeathTime)
		{
			m_bDeadSoon = true;
			GetAnimator()->SetAnimOpt(EANIM_OPT::ALPHA_BLEND);
			m_faccDeathTime = 0.f;
		}
	}
	else
	{
		if (3.f <= m_faccDeathTime)
		{
			SetDead();
			return;
		}
	}
}

void CSubWeapon::Render(HDC _DC)
{
	CObj::Render(_DC);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	vPos += vOffsetPos; 

	if (!m_bDeadSoon)
	{
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
	}
	else
	{
		m_fRatio += DELTATIME * m_fDir * 5;

		if (1.f <= m_fRatio)
		{
			m_fDir = -1.f;
			m_fRatio = 1.f;
		}
		else if (0.0 >= m_fRatio)
		{
			m_fDir = 1.f;
			m_fRatio = 0.0f;
		}

		BLENDFUNCTION tBlend = {};
		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);

		AlphaBlend(_DC,
			(int)(vPos.x - m_pTex->GetWidth() / 2.f),
			(int)(vPos.y - m_pTex->GetHeight() / 2.f),
			(int)(m_pTex->GetWidth()),
			(int)(m_pTex->GetHeight()),
			m_pTex->GetDC(),
			0, 0,
			(int)(m_pTex->GetWidth()),
			(int)(m_pTex->GetHeight()),
			tBlend);
	}
}

void CSubWeapon::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::PLAYER == pObj->GetLayer())
	{
		CPlayer* pPlayer = (CPlayer*)pObj;
		pPlayer->ChangeSubWeapon(m_eType);
		SetDead();

		PLAY_SOUND(L"GETSUB");
	}
}
