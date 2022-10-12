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
	m_eState(EPLAYER_ANIM_STATE::END),
	m_ePrevState(EPLAYER_ANIM_STATE::END),
	m_iFaceDir(1),
	m_iPrevFaceDir(1),
	m_fRunStartAcc(0.f),
	m_fJumpTimeAcc(0.f),
	m_bDoubleJump(true),
	m_iMoveState(0)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(80.f, 180.f));

	CTexture* pAlucardAtlas = CResMgr::GetInst()->LoadTexture(L"AlucardAtlas", L"texture\\Alucard_Atlast.bmp");
	GetAnimator()->CreateAnimation(L"Idle_Right", pAlucardAtlas, Vec2(240.f, 0.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Idle_Left", pAlucardAtlas, Vec2(240.f, 220.f), Vec2(240.f, 220.f), 6, 0.15f);
	GetAnimator()->CreateAnimation(L"Walk_Start_Right", pAlucardAtlas, Vec2(0.f, 440.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Start_Left", pAlucardAtlas, Vec2(0.f, 660.f), Vec2(240.f, 220.f), 15, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Right", pAlucardAtlas, Vec2(0.f, 880.f), Vec2(240.f, 220.f), 16, 0.06f);
	GetAnimator()->CreateAnimation(L"Walk_Left", pAlucardAtlas, Vec2(0.f, 1100.f), Vec2(240.f, 220.f), 16, 0.06f);

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

	// ��ü������ ���������Ƿ� ���� �ֽ� �ؾ���
	// ���� ���� ��
	if (GetRigidBody()->IsGround())
	{
		if (IS_TAP(EKEY::LEFT))
		{
			m_iFaceDir = -1;
			if (m_iPrevFaceDir == m_iFaceDir)
				m_eState = EPLAYER_ANIM_STATE::WALK_START_LEFT;
			else
				m_eState = EPLAYER_ANIM_STATE::TURN_AROUND_LEFT;
		}
		else if (IS_TAP(EKEY::RIGHT))
		{
			m_iFaceDir = 1;
			if (m_iPrevFaceDir == m_iFaceDir)	
				m_eState = EPLAYER_ANIM_STATE::WALK_START_RIGHT;
			else
				m_eState = EPLAYER_ANIM_STATE::TURN_AROUND_RIGHT;
		}
		else if (IS_TAP(EKEY::SPACE))
		{
			if (m_iMoveState & DUCK)
			{
				GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
				GetCollider()->SetScale(Vec2(80.f, 180.f));
				m_iMoveState ^= DUCK;
			}
			GetRigidBody()->SetGravity(false);
			GetRigidBody()->OffGround();
			m_eState = EPLAYER_ANIM_STATE::JUMP;
		}
		// ���̸� �ݸ��� ũ��� �������� �������ְ� �̵� ���¸� �������ش�
		else if (IS_TAP(EKEY::DOWN))
		{
			m_eState = EPLAYER_ANIM_STATE::DUCK_DOWN;
			m_iMoveState |= DUCK;
			GetCollider()->SetScale(Vec2(80.f, 60.f));
			GetCollider()->SetOffsetPos(Vec2(0.f, 60.f));
		}
		else if (IS_PRESSED(EKEY::DOWN))
		{
		}
		else if (IS_RELEASED(EKEY::DOWN))
		{
			GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
			GetCollider()->SetScale(Vec2(80.f, 180.f));
			m_eState = EPLAYER_ANIM_STATE::DUCK_UP;
			m_iMoveState ^= DUCK;
		}
		// ���� �̵�
		else if (IS_PRESSED(EKEY::LEFT))
		{
			m_fRunStartAcc += DELTATIME;
			if (0.9f < m_fRunStartAcc)
				m_eState = EPLAYER_ANIM_STATE::WALK_LEFT;
			
			// ���� �̵� ���� ���°� �ƴ϶�� �̵�
			if(!(LEFT_BLOCK & m_iMoveState))
				vPos.x -= m_fSpeed * DELTATIME;
		}
		// ������ �̵�
		else if (IS_PRESSED(EKEY::RIGHT))
		{
			m_fRunStartAcc += DELTATIME;
			if (0.9f < m_fRunStartAcc)
				m_eState = EPLAYER_ANIM_STATE::WALK_RIGHT;

			// ������ �̵� ���� ���°� �ƴ϶�� �̵�
			if(!(RIGHT_BLOCK & m_iMoveState))
				vPos.x += m_fSpeed * DELTATIME;
		}
		else if (CKeyMgr::GetInst()->IsNoEnter())
		{
			m_fRunStartAcc = 0.f;
			m_eState = EPLAYER_ANIM_STATE::IDLE1;
		}
	}
	// ���߿� ���� ��
	else
	{
		m_fJumpTimeAcc += DELTATIME;

		// ���߿��� ����Ű ��� ������ ������ ���
		if (IS_PRESSED(EKEY::SPACE) && 0.5f >= m_fJumpTimeAcc)
		{
			if (!(UP_BLOCK & m_iMoveState))
				vPos.y -= 400.f * DELTATIME;
		}
		// ü���ð��� �����ų�, �����̽� �� �Է��� ���߸� �߷��� �ٽ� ��
		else
		{
			GetRigidBody()->SetGravity(true);
			m_eState = EPLAYER_ANIM_STATE::FALL;
		}
		
		// ���߿��� ����Ű �ѹ� �� ������ ���� ����
		if (IS_TAP(EKEY::SPACE) && m_bDoubleJump && !(m_iMoveState & UP_BLOCK))
		{
			m_bDoubleJump = false;
			m_fJumpTimeAcc = 0.f;
			GetRigidBody()->SetGravity(false);

			m_eState = EPLAYER_ANIM_STATE::DOULBE_JUMP;

			Vec2 vVelocity = GetRigidBody()->GetVelocity();
			GetRigidBody()->AddVelocity(Vec2(0.f, -vVelocity.y));
		}

		// ���߿��� �������� �̵�
		if (IS_PRESSED(EKEY::LEFT))
		{
			// ���߿��� ������ȯ�� �ִϸ��̼� �����ؾ���
			if (!(LEFT_BLOCK & m_iMoveState))
				vPos.x -= m_fSpeed * DELTATIME;
		}
		// ���߿��� ���������� �̵�
		else if (IS_PRESSED(EKEY::RIGHT))
		{
			if (!(RIGHT_BLOCK & m_iMoveState))
				vPos.x += m_fSpeed * DELTATIME;
		}
	}
	
	// �ִϸ��̼� ������ ��ȭ�� �־��� �� �ش� �ִϸ��̼��� play ���ش�
	ChangeAnim();

	// �θ� ������Ʈ�� Tick�� �����Ų��(Component Tick�� �����Ű�� ����)
	CObj::Tick();

	// ���� ������ �÷��̾� ������ ����(���߿� �������� ���� �Ҽ��� ����)
	m_ePrevState = m_eState;
	m_iPrevFaceDir = m_iFaceDir;
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
	case EPLAYER_ANIM_STATE::IDLE1:
		if (1 == m_iFaceDir)
			GetAnimator()->Play(L"Idle_Right", true);
		else if (-1 == m_iFaceDir)
			GetAnimator()->Play(L"Idle_Left", true);
		break;
	case EPLAYER_ANIM_STATE::WALK_START_LEFT:
		GetAnimator()->Play(L"Walk_Start_Left", false);
		break;
	case EPLAYER_ANIM_STATE::WALK_START_RIGHT:
		GetAnimator()->Play(L"Walk_Start_Right", false);
		break;
	case EPLAYER_ANIM_STATE::WALK_LEFT:
		m_iFaceDir = -1;
		GetAnimator()->Play(L"Walk_Left", true);
		break;
	case EPLAYER_ANIM_STATE::WALK_RIGHT:
		m_iFaceDir = 1;
		GetAnimator()->Play(L"Walk_Right", true);
		break;
	case EPLAYER_ANIM_STATE::TURN_AROUND_LEFT:
		GetAnimator()->Play(L"Idle_Left", true);
		break;
	case EPLAYER_ANIM_STATE::TURN_AROUND_RIGHT:
		GetAnimator()->Play(L"Idle_Right", true);
		break;
	case EPLAYER_ANIM_STATE::JUMP:
		break;
	case EPLAYER_ANIM_STATE::DOULBE_JUMP:
		break;
	case EPLAYER_ANIM_STATE::SUPER_JUMP:
		break;
	case EPLAYER_ANIM_STATE::FALL:
		GetAnimator()->Play(L"Idle_Right", true);
		break;
	case EPLAYER_ANIM_STATE::ATTACK:
		break;
	}
}



// ====================
// MISSILE_MAKE_EXAMPLE
// ====================
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