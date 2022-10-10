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
	m_iJumpStack(2)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CTexture* pAlucardAtlas = CResMgr::GetInst()->LoadTexture(L"AlucardAtlas", L"texture\\Alucard_Atlast.bmp");
	GetAnimator()->CreateAnimation(L"Idle_Right", pAlucardAtlas, Vec2(240.f, 0.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Idle_Left", pAlucardAtlas, Vec2(240.f, 220.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Run_Start_Right", pAlucardAtlas, Vec2(0.f, 440.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Run_Start_Left", pAlucardAtlas, Vec2(0.f, 660.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Run_Right", pAlucardAtlas, Vec2(0.f, 880.f), Vec2(240.f, 220.f), 16, 0.06f);
	GetAnimator()->CreateAnimation(L"Run_Left", pAlucardAtlas, Vec2(0.f, 1100.f), Vec2(240.f, 220.f), 16, 0.06f);

	// �̹��� �ε�
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
	m_ePrevState(EPLAYER_STATE::END),
	m_iFaceDir(0)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	if (IS_TAP(EKEY::LEFT))
	{
		m_iFaceDir = -1;
		GetAnimator()->Play(L"Run_Start_Left", false);
	}
	else if (IS_TAP(EKEY::RIGHT))
	{
		m_iFaceDir = 1;
		GetAnimator()->Play(L"Run_Start_Right", false);
	}
	// ���� �̵�
	else if(IS_PRESSED(EKEY::LEFT))
	{
		m_fRunStartAcc += DELTATIME;
		if (0.9f < m_fRunStartAcc)
			m_eState = EPLAYER_STATE::WALK_LEFT;

		vPos.x -= m_fSpeed * DELTATIME;
		//GetRigidBody()->AddForce(Vec2(-1000.f, 0.f));
	}
	// ������ �̵�
	else if (IS_PRESSED(EKEY::RIGHT))
	{
		m_fRunStartAcc += DELTATIME;
		if (0.9f < m_fRunStartAcc)
			m_eState = EPLAYER_STATE::WALK_RIGHT;

		vPos.x += m_fSpeed * DELTATIME;
		//GetRigidBody()->AddForce(Vec2(1000.f, 0.f));
	}
	else if (IS_PRESSED(EKEY::SPACE))
	{
		if (IS_PRESSED(EKEY::DOWN))
			GetRigidBody()->OffGround();
		else
		{
			Vec2 vVelocity = GetRigidBody()->GetVelocity();

			if (0.f < vVelocity.y)
			{
				GetRigidBody()->AddVelocity(Vec2(0.f, -(vVelocity.y + 100.f)));
			}
			else
			{
				GetRigidBody()->AddVelocity(Vec2(0.f, -1.5f));
			}
		}
		//CCamera::GetInst()->CameraShake(0.1f, 10.f, 500.f);
		//// �̻��� ����
		//for (int i = 0; i < 3; i++)
		//{
		//	CMissile* pMissile = new CMissile;
		//	pMissile->SetScale(Vec2{ 20.f, 20.f });
		//	pMissile->SetSpeed(400.f);
		//	pMissile->SetDir(75.f + 15.f * (float)i);

		//	Instantiate(pMissile, GetPos(), ELAYER::PLAYER_PROJECTILE);
		//}
	}
	else if(IS_NONE(EKEY::LEFT) && IS_NONE(EKEY::RIGHT))
	{
		m_fRunStartAcc = 0.f; 
		m_eState = EPLAYER_STATE::IDLE1;
	}

	//Vec2 vDir = (GetPos() - m_vPrevPos);

	//if (0.f < vDir.y)
	//	m_eState = EPLAYER_STATE::FALL;
	//else if (0.f > vDir.y)
	//	m_eState = EPLAYER_STATE::JUMP;
	//else if(0.f == vDir.x && 0.f == vDir.y)
	//{

	//}

	ChangeAnim();

	m_ePrevState = m_eState;

	// �θ� ������Ʈ�� Tick�� �����Ų��(Component Tick�� �����Ű�� ����)
	CObj::Tick();
	
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
	case EPLAYER_STATE::WALK_LEFT:
		m_iFaceDir = -1;
		GetAnimator()->Play(L"Run_Left", true);
		break;
	case EPLAYER_STATE::WALK_RIGHT:
		m_iFaceDir = 1;
		GetAnimator()->Play(L"Run_Right", true);
		break;
	case EPLAYER_STATE::JUMP:
		break;
	case EPLAYER_STATE::FALL:
		break;
	case EPLAYER_STATE::ATTACK:
		break;
	}
}