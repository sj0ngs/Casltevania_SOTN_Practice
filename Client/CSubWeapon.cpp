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

CSubWeapon::CSubWeapon()	:
	m_eType(ESUB_WEAPON_TYPE::NONE),
	m_pTex(nullptr),
	vOffsetPos{}
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
}

void CSubWeapon::Render(HDC _DC)
{
	CObj::Render(_DC);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	vPos += vOffsetPos; 

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
