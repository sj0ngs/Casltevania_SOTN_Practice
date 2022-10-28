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

// State 
#include "CPlayerIdleState.h"
#include "CPlayerLeftMoveState.h"
#include "CPlayerRightMoveState.h"

// ��Ʋ�� �̹��� ��ġ ���
const float ATLAS_X_BORDER = 0.f;
const float ATLAS_Y_BORDER = 0.f;
const float ATLAS_X_SIZE = 476.f;
const float ATLAS_Y_SIZE = 396.f;
const float ATLAS_X_PADDING = 16.f;
const float ATLAS_Y_PADDING = 16.f;
#define RIGHT_OFFSET Vec2(70.f, -180.f)
#define LEFT_OFFSET Vec2(-70.f, -180.f)

CPlayer::CPlayer() :
	m_fSpeed(200.f),
	m_bPrevFaceDir(true),
	m_fRunStartAcc(0.f),
	m_fJumpTimeAcc(0.f),
	m_bDoubleJump(true)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();
	CreateAI();

	// ================
	// Collider Setting
	// ================
	GetCollider()->SetScale(Vec2(64.f, 180.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -90.f));

	// ================
	// Animator Setting
	// ================
	//CTexture* pAlucardAtlas = CResMgr::GetInst()->LoadTexture(L"AlucardAtlas", L"texture\\Alucard_Atlast.bmp");
	//GetAnimator()->CreateAnimation(L"Idle_Right", pAlucardAtlas, Vec2(240.f, 0.f), Vec2(240.f, 220.f), 6, 0.15f);
	//GetAnimator()->CreateAnimation(L"Idle_Left", pAlucardAtlas, Vec2(240.f, 220.f), Vec2(240.f, 220.f), 6, 0.15f);
	//GetAnimator()->CreateAnimation(L"Walk_Start_Right", pAlucardAtlas, Vec2(0.f, 440.f), Vec2(240.f, 220.f), 15, 0.06f);
	//GetAnimator()->CreateAnimation(L"Walk_Start_Left", pAlucardAtlas, Vec2(0.f, 660.f), Vec2(240.f, 220.f), 15, 0.06f);
	//GetAnimator()->CreateAnimation(L"Walk_Right", pAlucardAtlas, Vec2(0.f, 880.f), Vec2(240.f, 220.f), 16, 0.06f);
	//GetAnimator()->CreateAnimation(L"Walk_Left", pAlucardAtlas, Vec2(0.f, 1100.f), Vec2(240.f, 220.f), 16, 0.06f);

	CTexture* pAlucardAtlas_right = CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\alucard_right_1.bmp");
	CTexture* pAlucardAtlas_left = CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\alucard_left_1.bmp");

	float fLeftWidth = (float)pAlucardAtlas_left->GetWidth();

	GetAnimator()->CreateAnimation(L"Idle_Right", pAlucardAtlas_right, 
					Vec2(ATLAS_X_BORDER, ATLAS_Y_BORDER + ATLAS_Y_SIZE * 0.f), 
					Vec2(ATLAS_X_SIZE, ATLAS_Y_SIZE), 6, 0.15f, Vec2(0.f, 0.f), RIGHT_OFFSET);
	GetAnimator()->CreateAnimation(L"Idle_Left", pAlucardAtlas_left,
					Vec2(fLeftWidth - (ATLAS_X_BORDER + ATLAS_X_SIZE * 1.f), ATLAS_Y_BORDER + ATLAS_Y_SIZE * 0.f),
					Vec2(-ATLAS_X_SIZE, ATLAS_Y_SIZE), 6, 0.15f, Vec2(0.f, 0.f), LEFT_OFFSET);

	GetAnimator()->CreateAnimation(L"Walk_Start_Right", pAlucardAtlas_right, 
					Vec2(ATLAS_X_BORDER, ATLAS_Y_BORDER + ATLAS_Y_SIZE * 1.f),
					Vec2(ATLAS_X_SIZE, ATLAS_Y_SIZE), 15, 0.06f, Vec2(0.f, 0.f), RIGHT_OFFSET);
	GetAnimator()->CreateAnimation(L"Walk_Start_Left", pAlucardAtlas_left,
					Vec2(fLeftWidth - (ATLAS_X_BORDER + ATLAS_X_SIZE * 1.f), ATLAS_Y_BORDER + ATLAS_Y_SIZE * 1.f),
					Vec2(-ATLAS_X_SIZE, ATLAS_Y_SIZE), 15, 0.06f, Vec2(0.f, 0.f), LEFT_OFFSET);

	GetAnimator()->CreateAnimation(L"Walk_Right", pAlucardAtlas_right, 
					Vec2(ATLAS_X_BORDER, ATLAS_Y_BORDER + ATLAS_Y_SIZE * 2.f),
					Vec2(ATLAS_X_SIZE, ATLAS_Y_SIZE), 16, 0.06f, Vec2(0.f, 0.f), RIGHT_OFFSET);
	GetAnimator()->CreateAnimation(L"Walk_Left", pAlucardAtlas_left,
					Vec2(fLeftWidth - (ATLAS_X_BORDER + ATLAS_X_SIZE * 1.f), ATLAS_Y_BORDER + ATLAS_Y_SIZE * 2.f),
					Vec2(-ATLAS_X_SIZE, ATLAS_Y_SIZE), 16, 0.06f, Vec2(0.f, 0.f), LEFT_OFFSET);

	GetAnimator()->CreateAnimation(L"Jump_Right", pAlucardAtlas_right,
					Vec2(ATLAS_X_BORDER, ATLAS_Y_BORDER + ATLAS_Y_SIZE * 8.f),
					Vec2(ATLAS_X_SIZE, ATLAS_Y_SIZE), 7, 0.0715f, Vec2(0.f, 0.f), RIGHT_OFFSET);

	//GetAnimator()->CreateAnimation(L"Jump_Left", pAlucardAtlas_left,
	//				Vec2(fLeftWidth - (ATLAS_X_BORDER + ATLAS_X_SIZE * 1.f), ATLAS_Y_BORDER + ATLAS_Y_SIZE * 8.f),
	//				Vec2(-ATLAS_X_SIZE, ATLAS_Y_SIZE), 7, 0.0715f, Vec2(0.f, 0.f), LEFT_OFFSET);
	
	GetAnimator()->LoadAnimation(L"animation\\Player\\JUMP_LEFT.anim");
		
	GetAnimator()->CreateAnimation(L"Fall_Right", pAlucardAtlas_right,
					Vec2(ATLAS_X_BORDER, ATLAS_Y_BORDER + ATLAS_Y_SIZE * 9.f),
					Vec2(ATLAS_X_SIZE, ATLAS_Y_SIZE), 8, 0.0715f, Vec2(0.f, 0.f), RIGHT_OFFSET);

	//GetAnimator()->CreateAnimation(L"Fall_Left", pAlucardAtlas_left,
	//				Vec2(fLeftWidth - (ATLAS_X_BORDER + ATLAS_X_SIZE * 1.f), ATLAS_Y_BORDER + ATLAS_Y_SIZE * 9.f),
	//				Vec2(-ATLAS_X_SIZE, ATLAS_Y_SIZE), 8, 0.0715f, Vec2(0.f, 0.f), LEFT_OFFSET);

	GetAnimator()->LoadAnimation(L"animation\\Player\\FALL_LEFT.anim");

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

	//GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");

	// =================
	// RigidBody Setting
	// =================
	GetRigidBody()->SetFriction(300.f);
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(1000.f);
	GetRigidBody()->SetVelocityLimit(1000.f);

	// ==========
	// AI Setting
	// ==========
	GetAI()->AddState(L"Idle", new CPlayerIdleState);
	GetAI()->AddState(L"Move_Left", new CPlayerMoveLeftState);
	GetAI()->AddState(L"Move_Right", new CPlayerRightMoveState);
	GetAI()->ChangeState(L"Idle");
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	//// ��ü������ ���������Ƿ� ���� �ֽ� �ؾ���
	//// ���� ���� ��
	//if (GetRigidBody()->IsGround())
	//{
	//	if (IS_TAP(EKEY::LEFT))
	//	{
	//		SetFaceDir(false);
	//		if (m_bPrevFaceDir == GetFaceDir())
	//		{
	//			GetAnimator()->Play(L"Walk_Start_Left", false);
	//		}
	//		else
	//			GetAnimator()->Play(L"Walk_Start_Left", false);
	//	}
	//	else if (IS_TAP(EKEY::RIGHT))
	//	{
	//		SetFaceDir(true);
	//		if (m_bPrevFaceDir == GetFaceDir())
	//		{
	//			GetAnimator()->Play(L"Walk_Start_Right", false);
	//		}
	//		else
	//			GetAnimator()->Play(L"Walk_Start_Right", false);
	//	}
	//	else if (IS_TAP(EKEY::SPACE))
	//	{
	//		GetRigidBody()->SetGravity(false);
	//		GetRigidBody()->OffGround();
	//		if (GetFaceDir())
	//			GetAnimator()->Play(L"Jump_Right", false);
	//		else
	//			GetAnimator()->Play(L"Jump_Left", false);
	//	}
	//	// ���� �̵�
	//	else if (IS_PRESSED(EKEY::LEFT))
	//	{
	//		// walk start �ִϸ��̼��� ������ ����ǵ��� ����
	//		m_fRunStartAcc += DELTATIME;
	//		if (GetAnimator()->IsAnimationFinish(L"Walk_Start_Left"))
	//		{
	//			SetFaceDir(false);
	//			GetAnimator()->Play(L"Walk_Left", true);
	//		}
	//		
	//		// ���� �̵� ���� ���°� �ƴ϶�� �̵�
	//		vPos -= GetDir() * m_fSpeed * DELTATIME;
	//	}
	//	// ������ �̵�
	//	else if (IS_PRESSED(EKEY::RIGHT))
	//	{
	//		m_fRunStartAcc += DELTATIME;
	//		if (GetAnimator()->IsAnimationFinish(L"Walk_Start_Right"))
	//		{
	//			SetFaceDir(true);
	//			GetAnimator()->Play(L"Walk_Right", true);
	//		}

	//		// ������ �̵� ���� ���°� �ƴ϶�� �̵�
	//		vPos += GetDir() * m_fSpeed * DELTATIME;
	//	}
	//	// ���̸� �ݸ��� ũ��� �������� �������ְ� �̵� ���¸� �������ش�
	//	else if (IS_TAP(EKEY::DOWN))
	//	{
	//		GetCollider()->SetScale(Vec2(80.f, 60.f));
	//		GetCollider()->SetOffsetPos(Vec2(0.f, 60.f));
	//	}
	//	else if (IS_PRESSED(EKEY::DOWN))
	//	{
	//	}
	//	else if (IS_RELEASED(EKEY::DOWN))
	//	{
	//		GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	//		GetCollider()->SetScale(Vec2(80.f, 180.f));
	//	}
	//	else if (IS_TAP(EKEY::LSHIFT))
	//	{

	//	}
	//	// �ƹ� Ű�� �Էµ��� ������ ���̵�
	//	else if (CKeyMgr::GetInst()->IsNoEnter())
	//	{
	//		m_fRunStartAcc = 0.f;
	//		ResetJump();
	//		if (GetFaceDir())
	//			GetAnimator()->Play(L"Idle_Right", true);
	//		else
	//			GetAnimator()->Play(L"Idle_Left", true);
	//	}
	//}
	//// ���߿� ���� ��
	//else
	//{
	//	m_fJumpTimeAcc += DELTATIME;

	//	// ���߿��� ����Ű ��� ������ ������ ���
	//	if (IS_PRESSED(EKEY::SPACE) && 0.5f >= m_fJumpTimeAcc)
	//	{
	//		vPos.y -= 600.f * DELTATIME;
	//	}
	//	// ü���ð��� �����ų�, �����̽� �� �Է��� ���߸� �߷��� �ٽ� ��
	//	else
	//	{
	//		GetRigidBody()->SetGravity(true);
	//		if (GetFaceDir())
	//			GetAnimator()->Play(L"Fall_Right", false);
	//		else
	//			GetAnimator()->Play(L"Fall_Left", false);
	//	}
	//	
	//	// ���߿��� ����Ű �ѹ� �� ������ ���� ����
	//	if (IS_TAP(EKEY::SPACE) && m_bDoubleJump)
	//	{
	//		m_bDoubleJump = false;
	//		m_fJumpTimeAcc = 0.f;
	//		GetRigidBody()->SetGravity(false);

	//		Vec2 vVelocity = GetRigidBody()->GetVelocity();
	//		GetRigidBody()->AddVelocity(Vec2(0.f, -vVelocity.y));
	//	}

	//	// ���߿��� �������� �̵�
	//	if (IS_PRESSED(EKEY::LEFT))
	//	{
	//		// ���߿��� ������ȯ�� �ִϸ��̼� �����ؾ���
	//		vPos.x -= m_fSpeed * DELTATIME;
	//	}
	//	// ���߿��� ���������� �̵�
	//	else if (IS_PRESSED(EKEY::RIGHT))
	//	{
	//		vPos.x += m_fSpeed * DELTATIME;
	//	}
	//}

	// �θ� ������Ʈ�� Tick�� �����Ų��(Component Tick�� �����Ű�� ����)
	CObj::Tick();

	// SetPos(vPos);
}

void CPlayer::Render(HDC _DC)
{
	CObj::Render(_DC);

	m_bPrevFaceDir = GetFaceDir();
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