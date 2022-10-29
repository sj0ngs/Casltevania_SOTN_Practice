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
#include "CPlayerMoveEndState.h"
#include "CPlayerJumpState.h"
#include "CPlayerFallState.h"
#include "CPlayerLanding.h"

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

	// IDLE
	LoadAnim(L"IDLE_FIRST");
	LoadAnim(L"IDLE_SECOND");
	LoadAnim(L"IDLE_THIRD");
	LoadAnim(L"IDLE_FOURTH");		

	// WALK
	LoadAnim(L"WALK_START");
	LoadAnim(L"WALK");
	LoadAnim(L"WALK_END");
	LoadAnim(L"WALK_END_SMALL");
	LoadAnim(L"WALK_END_HILL");
	LoadAnim(L"TURN");

	// SKILL
	LoadAnim(L"PRESS_UP");
	LoadAnim(L"PRESS_UP_HILL");
	LoadAnim(L"HELLFIRE");

	//KICK
	LoadAnim(L"DRAGON_KICK");
	LoadAnim(L"FLYING_KICK");

	// DUCK
	LoadAnim(L"DUCK");
	LoadAnim(L"GET_UP");

	// JUMP
	LoadAnim(L"JUMP");
	LoadAnim(L"JUMP_FOWARD");
	LoadAnim(L"DOUBLE_JUMP");
	LoadAnim(L"SUPER_JUMP");

	// FALL
	LoadAnim(L"FALL");
	LoadAnim(L"SUPER_JUMP_FALL");
	LoadAnim(L"LANDING");
	LoadAnim(L"LANDING_HILL");

	// ATTACK - PUNCH
	LoadAnim(L"STAND_PUNCH");
	LoadAnim(L"DUCK_PUNCH");
	LoadAnim(L"JUMP_PUNCH");
	LoadAnim(L"JUMP_DOWN_PUNCH");
	
	// ATTACK - SWORD
	LoadAnim(L"STAND_ATTACK");
	LoadAnim(L"STAND_ATTACK_DEFAULT");
	LoadAnim(L"STAND_ATTACK_SWORD");
	LoadAnim(L"STAND_SWORD");
	LoadAnim(L"STAND_PARTICLE");

	LoadAnim(L"JUMP_ATTACK");

	LoadAnim(L"DUCK_ATTACK");
	LoadAnim(L"DUCK_DOWN_ATTACK");
	LoadAnim(L"DUCK_DOWN_ATTACK_DEFUALT");
	LoadAnim(L"DUCK_DOWN_SWORD");
	LoadAnim(L"DUCK_DOWN_EFFECT");
	LoadAnim(L"DUCK_DOWN_PARTICLE");

	// COVER
	LoadAnim(L"STAND_COVER");
	LoadAnim(L"DUCK_COVER");
	LoadAnim(L"DUCK_COVER");

	// HIT
	LoadAnim(L"GET_UP_LYING");
	LoadAnim(L"HIT_1");
	LoadAnim(L"HIT_2");
	LoadAnim(L"HIT_3");
	LoadAnim(L"HIT_4");
	LoadAnim(L"HIT_5");
	LoadAnim(L"HIT_6");
	
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
	GetAI()->AddState(L"MoveEnd", new CPlayerMoveEndState);
	GetAI()->AddState(L"Jump", new CPlayerJumpState);
	GetAI()->AddState(L"Fall", new CPlayerFallState);
	GetAI()->AddState(L"Landing", new CPlayerLanding);
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

void CPlayer::LoadAnim(const wstring& _strFile)
{
	wstring strPath = L"animation\\Player\\";
	strPath += _strFile;
		
	wstring strDir = L"_LEFT.anim";
	wstring strLeft = strPath + strDir;
	GetAnimator()->LoadAnimation(strLeft);

	strDir = L"_RIGHT.anim";
	wstring strRight = strPath + strDir;
	GetAnimator()->LoadAnimation(strRight);
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