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
	m_ePrevState(EPLAYER_STATE::END),
	m_iFaceDir(1),
	m_fRunStartAcc(0.f),
	m_fJumpTimeAcc(0.f),
	m_bDoubleJump(true)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CTexture* pAlucardAtlas = CResMgr::GetInst()->LoadTexture(L"AlucardAtlas", L"texture\\Alucard_Atlast.bmp");
	GetAnimator()->CreateAnimation(L"Idle_Right", pAlucardAtlas, Vec2(240.f, 0.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Idle_Left", pAlucardAtlas, Vec2(240.f, 220.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Walk_Start_Right", pAlucardAtlas, Vec2(0.f, 440.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Start_Left", pAlucardAtlas, Vec2(0.f, 660.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Right", pAlucardAtlas, Vec2(0.f, 880.f), Vec2(240.f, 220.f), 16, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Left", pAlucardAtlas, Vec2(0.f, 1100.f), Vec2(240.f, 220.f), 16, 0.06f);

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
	GetRigidBody()->SetGravityAccel(700.f);

	GetRigidBody()->SetVelocityLimit(500.f);
	GetRigidBody()->SetGravityVelocityLimit(800.f);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	// 지상에 있을 때
	if (GetRigidBody()->IsGround())
	{
		m_bDoubleJump = true;
		m_fJumpTimeAcc = 0.f;

		if (IS_TAP(EKEY::LEFT))
		{
			m_iFaceDir = -1;
			m_eState = EPLAYER_STATE::WALK_START_LEFT;
		}
		else if (IS_TAP(EKEY::RIGHT))
		{
			m_iFaceDir = 1;
			m_eState = EPLAYER_STATE::WALK_START_RIGHT;
		}
		// 왼쪽 이동
		else if (IS_PRESSED(EKEY::LEFT))
		{
			m_fRunStartAcc += DELTATIME;
			if (0.9f < m_fRunStartAcc)
				m_eState = EPLAYER_STATE::WALK_LEFT;

			vPos.x -= m_fSpeed * DELTATIME;
		}
		// 오른쪽 이동
		else if (IS_PRESSED(EKEY::RIGHT))
		{
			m_fRunStartAcc += DELTATIME;
			if (0.9f < m_fRunStartAcc)
				m_eState = EPLAYER_STATE::WALK_RIGHT;

			vPos.x += m_fSpeed * DELTATIME;
		}
		else if (CKeyMgr::GetInst()->IsNoEnter())
		{
			m_fRunStartAcc = 0.f;
			m_eState = EPLAYER_STATE::IDLE1;
		}

		if (IS_TAP(EKEY::SPACE))
		{
			GetRigidBody()->SetGravity(false);
			GetRigidBody()->OffGround();
			GetRigidBody()->AddVelocity(Vec2(0.f, -1500.f * DELTATIME));
		}
	}
	// 공중에 있을 때
	else
	{
		m_fJumpTimeAcc += DELTATIME;

		// 공중에서 점프키 계속 누르고 있으면 상승
		if (IS_PRESSED(EKEY::SPACE) && 0.5f >= m_fJumpTimeAcc)
		{
			vPos.y -= 400.f * DELTATIME;
			//GetRigidBody()->AddVelocity(Vec2(0.f, -1500.f * DELTATIME));
		}
		else
		{
			GetRigidBody()->SetGravity(true);
		}
		
		// 공중에서 점프키 한번 더 누르면 더블 점프
		if (IS_TAP(EKEY::SPACE) && m_bDoubleJump)
		{
			m_bDoubleJump = false;
			m_fJumpTimeAcc = 0.f;
			GetRigidBody()->SetGravity(false);

			Vec2 vVelocity = GetRigidBody()->GetVelocity();

			GetRigidBody()->AddVelocity(Vec2(0.f, -vVelocity.y));
		}

		// 공중에서 왼쪽으로 이동
		if (IS_PRESSED(EKEY::LEFT))
		{
			// 공중에서 방향전환시 애니메이션 변경해야함
			vPos.x -= m_fSpeed * DELTATIME;
		}
		// 공중에서 오른쪽으로 이동
		else if (IS_PRESSED(EKEY::RIGHT))
		{
			vPos.x += m_fSpeed * DELTATIME;
		}
	}

	ChangeAnim();

	// 부모 오브젝트의 Tick도 실행시킨다(Component Tick을 실행시키기 위해)
	CObj::Tick();

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
	if (m_eState == m_ePrevState)
		return;

	switch (m_eState)
	{
	case EPLAYER_STATE::IDLE1:
		if (1 == m_iFaceDir)
			GetAnimator()->Play(L"Idle_Right", true);
		else if(-1 == m_iFaceDir)
			GetAnimator()->Play(L"Idle_Left", true);
		break;
	case EPLAYER_STATE::WALK_START_LEFT:
		GetAnimator()->Play(L"Walk_Start_Left", false);
		break;
	case EPLAYER_STATE::WALK_START_RIGHT:
		GetAnimator()->Play(L"Walk_Start_Right", false);
		break;
	case EPLAYER_STATE::WALK_LEFT:
		m_iFaceDir = -1;
		GetAnimator()->Play(L"Walk_Left", true);
		break;
	case EPLAYER_STATE::WALK_RIGHT:
		m_iFaceDir = 1;
		GetAnimator()->Play(L"Walk_Right", true);
		break;
	case EPLAYER_STATE::JUMP:
		break;
	case EPLAYER_STATE::FALL:
		break;
	case EPLAYER_STATE::ATTACK:
		break;
	}
}









// ====================
// MISSILE_MAKE_EXAMPLE
// ====================
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