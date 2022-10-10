#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CLevel.h"
#include "CMissile.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CRigidBody.h"

CPlayer::CPlayer() :
	m_fSpeed(200.f),
	m_vPrevPos{},
	m_eState(EPLAYER_STATE::END),
	m_ePrevState(EPLAYER_STATE::END)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CTexture* pAlucardAtlas = CResMgr::GetInst()->LoadTexture(L"AlucardAtlas", L"texture\\Alucrad_Atlas.bmp");
	GetAnimator()->CreateAnimation(L"Idle_1", pAlucardAtlas, Vec2(240.f, 0.f), Vec2(240.f, 220.f), 6, 0.15f);
	// 이미지 로딩
	//CTexture* pLinkTex = CResMgr::GetInst()->LoadTexture(L"LINK", L"texture\\link.bmp");
	//GetAnimator()->CreateAnimation(L"WALK_DOWN", pLinkTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pLinkTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_UP", pLinkTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pLinkTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 0.1f);

	//GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\WALK_DOWN.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\WALK_LEFT.anim");
	//GetAnimator()->FindAnimation(L"WALK_UP")->Save(L"animation\\WALK_UP.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");

	GetRigidBody()->SetFriction(300.f);
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(800.f);

	GetRigidBody()->SetVelocityLimit(500.f);
	GetRigidBody()->SetGravityVelocityLimit(1000.f);
}

CPlayer::CPlayer(const CPlayer& _Other)	:
	CObj(_Other),
	m_fSpeed(_Other.m_fSpeed),
	m_vPrevPos{},
	m_eState(EPLAYER_STATE::END),
	m_ePrevState(EPLAYER_STATE::END)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vDir = (GetPos() - m_vPrevPos);

	//if (0.f < vDir.y)
	//	m_eState = EPLAYER_STATE::FALL;
	//else if (0.f > vDir.y)
	//	m_eState = EPLAYER_STATE::JUMP;
	if (0.f < vDir.x)
		m_eState = EPLAYER_STATE::WALK_START_RIGHT;
	else if (0.f > vDir.x)
		m_eState = EPLAYER_STATE::WALK_START_LEFT;
	else
		m_eState = EPLAYER_STATE::IDLE1;


	Vec2 vPos = GetPos();
	// 왼쪽 이동
	if(IS_PRESSED(EKEY::LEFT))
	{
		vPos.x -= m_fSpeed * DELTATIME;
		//GetRigidBody()->AddForce(Vec2(-1000.f, 0.f));
	}
	// 오른쪽 이동
	if (IS_PRESSED(EKEY::RIGHT))
	{
		vPos.x += m_fSpeed * DELTATIME;
		//GetRigidBody()->AddForce(Vec2(1000.f, 0.f));
	}
	//// 위로 이동
	//if (IS_PRESSED(EKEY::UP))
	//{
	//	GetRigidBody()->AddForce(Vec2(0.f, -30000.f));
	//}
	//// 아래로 이동
	//if (IS_PRESSED(EKEY::DOWN))
	//{
	//	GetRigidBody()->AddForce(Vec2(0.f, 30000.f));
	//}
	//if (IS_TAP(EKEY::UP))
	//	GetAnimator()->Play(L"WALK_UP", true);
	//if(IS_TAP(EKEY::DOWN))
	//	GetAnimator()->Play(L"WALK_DOWN", true);
	//if (IS_TAP(EKEY::LEFT))
	//{
	//	m_eState = EPLAYER_STATE::WALK_START_LEFT;
	//}
	//if (IS_TAP(EKEY::RIGHT))
	//{
	//	m_eState = EPLAYER_STATE::WALK_START_RIGHT;
	//}
	if (IS_TAP(EKEY::SPACE))
	{
		if (IS_PRESSED(EKEY::DOWN))
			GetRigidBody()->OffGround();
		else
		{
			Vec2 vVelocity = GetRigidBody()->GetVelocity();

			if (0.f < vVelocity.y)
				GetRigidBody()->AddVelocity(Vec2(0.f, -(vVelocity.y + 500.f)));
			else
				GetRigidBody()->AddVelocity(Vec2(0.f, -500.f));
		}
		//CCamera::GetInst()->CameraShake(0.1f, 10.f, 500.f);
		//// 미사일 생성
		//for (int i = 0; i < 3; i++)
		//{
		//	CMissile* pMissile = new CMissile;
		//	pMissile->SetScale(Vec2{ 20.f, 20.f });
		//	pMissile->SetSpeed(400.f);
		//	pMissile->SetDir(75.f + 15.f * (float)i);

		//	Instantiate(pMissile, GetPos(), ELAYER::PLAYER_PROJECTILE);
		//}
	}

	// 부모 오브젝트의 Tick도 실행시킨다(Component Tick을 실행시키기 위해)
	CObj::Tick();

	if (m_eState != m_ePrevState)
		ChangeAnim();

	m_ePrevState = m_eState;
	
	m_vPrevPos = GetPos();

	SetPos(vPos);
}

void CPlayer::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CPlayer::BeginOverlap(CCollider* _pOther)
{
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
}

void CPlayer::EndOverlap(CCollider* _pOther)
{
}

void CPlayer::ChangeAnim()
{
	switch (m_eState)
	{
	case EPLAYER_STATE::IDLE1:
		GetAnimator()->Play(L"Idle_1", true);
		break;
	case EPLAYER_STATE::WALK_START_LEFT:
		GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case EPLAYER_STATE::WALK_START_RIGHT:
		GetAnimator()->Play(L"WALK_RIGHT", true);
		break;
	case EPLAYER_STATE::WALK_LEFT:
		break;
	case EPLAYER_STATE::WALK_RIGHT:
		break;
	case EPLAYER_STATE::JUMP:
		break;
	case EPLAYER_STATE::FALL:
		break;
	case EPLAYER_STATE::ATTACK:
		break;
	}
}