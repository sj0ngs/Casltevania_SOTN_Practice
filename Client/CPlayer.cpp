#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CObjMgr.h"

#include "CLevel.h"
#include "CMissile.h"
#include "CTexture.h"
#include "CWeapon.h"
#include "CMonster.h"
#include "CEffect.h"

#include "CDagger.h"
#include "CAxe.h"
#include "CBible.h"

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
#include "CPlayerLandingState.h"
#include "CPlayerBackDashState.h"
#include "CPlayerDuckState.h"
#include "CPlayerGetUp.h"
#include "CPlayerStandAttackState.h"
#include "CPlayerJumpAttackState.h"
#include "CPlayerDuckAttackState.h"
#include "CPlayerStandCoverState.h"
#include "CPlayerDuckCoverState.h"
#include "CPlayerHitState.h"
#include "CPlayerDeathState.h"

CPlayer::CPlayer() :
	m_tInfo{},
	m_bPrevFaceDir(true),
	m_bDoubleJump(true),
	m_bGoDown(false),
	m_bIsDuck(false),
	m_eState(EPLAYER_STATE::STAND),
	m_fAttackAcc(ATTACK_COOL),
	m_pWeapon(nullptr),
	m_eSubWeapon(ESUB_WEAPON_TYPE::AXE),
	m_bIsHit(false)
{
	// 플레이어 초기 정보 세팅
	m_tInfo.m_iMaxHP = 100;
	m_tInfo.m_iHP = m_tInfo.m_iMaxHP;

	m_tInfo.m_iMaxMP = 50;
	m_tInfo.m_iMP = m_tInfo.m_iMaxMP;

	m_tInfo.m_iHeart = 50;

	m_tInfo.m_iStr = 10;
	m_tInfo.m_iCon = 5;
	m_tInfo.m_iInt = 10;

	m_tInfo.m_fSpeed = 300.f;

	// 컴포넌트 세팅
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();
	CreateAI();

	// ================
	// Collider Setting
	// ================
	GetCollider()->SetScale(Vec2(50.f, 180.f));
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
	GetRigidBody()->SetGravityAccel(1500.f);
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
	GetAI()->AddState(L"Landing", new CPlayerLandingState);
	GetAI()->AddState(L"BackDash", new CPlayerBackDashState);
	GetAI()->AddState(L"Duck", new CPlayerDuckState);
	GetAI()->AddState(L"GetUp", new CPlayerGetUp);
	GetAI()->AddState(L"StandAttack", new CPlayerStandAttackState);
	GetAI()->AddState(L"JumpAttack", new CPlayerJumpAttackState);
	GetAI()->AddState(L"DuckAttack", new CPlayerDuckAttackState);
	GetAI()->AddState(L"StandCover", new CPlayerStandCoverState);
	GetAI()->AddState(L"DuckCover", new CPlayerDuckCoverState);
	GetAI()->AddState(L"Hit", new CPlayerHitState);
	GetAI()->AddState(L"Death", new CPlayerDeathState);
	GetAI()->ChangeState(L"Idle");
}

CPlayer::CPlayer(const CPlayer& _pOrigin)	:
	CObj(_pOrigin),
	m_tInfo(_pOrigin.m_tInfo),
	m_bPrevFaceDir(_pOrigin.m_bPrevFaceDir),
	m_bDoubleJump(_pOrigin.m_bDoubleJump),
	m_bGoDown(_pOrigin.m_bGoDown),
	m_bIsDuck(_pOrigin.m_bIsDuck),
	m_eState(_pOrigin.m_eState),
	m_fAttackAcc(_pOrigin.m_fAttackAcc),
	m_pWeapon(_pOrigin.m_pWeapon),
	m_eSubWeapon(_pOrigin.m_eSubWeapon),
	m_bIsHit(_pOrigin.m_bIsHit)
{
	SetWeapon(_pOrigin.m_pWeapon);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	if (m_bIsDuck)
		m_eState = EPLAYER_STATE::DUCK;
	else if (!GetRigidBody()->IsGround())
		m_eState = EPLAYER_STATE::AIR;
	else
		m_eState = EPLAYER_STATE::STAND;

	if (ATTACK_COOL > m_fAttackAcc)
	{
		m_fAttackAcc += DELTATIME;

		if (ATTACK_COOL <= m_fAttackAcc)
			m_fAttackAcc = ATTACK_COOL;
	}

	if (IS_TAP(EKEY::TAB))
	{
		if (nullptr == m_pWeapon)
			SetWeapon((CWeapon*)CObjMgr::GetInst()->FindObj(L"Alucard_Sword"));
		else
			SetWeapon(nullptr);
	}

	//if (IS_TAP(EKEY::key1))
	//{
	//	Skill();
	//}

	if (nullptr != m_pWeapon)
		m_pWeapon->Tick();

	CObj::Tick();
}

void CPlayer::Render(HDC _DC)
{
	CObj::Render(_DC);

	m_bPrevFaceDir = GetFaceDir();

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	wstring strDebug = L"xPos : ";
	strDebug += std::to_wstring(GetPos().x);
	TextOut(_DC, (int)vPos.x + 50, (int)vPos.y - 200, strDebug.c_str(), (int)strDebug.length());

	strDebug = L"yPos : ";
	strDebug += std::to_wstring(GetPos().y);
	TextOut(_DC, (int)vPos.x + 50, (int)vPos.y - 180, strDebug.c_str(), (int)strDebug.length());

	strDebug = L"HP : ";
	strDebug += std::to_wstring(m_tInfo.m_iHP);
	TextOut(_DC, (int)vPos.x + 50, (int)vPos.y - 160, strDebug.c_str(), (int)strDebug.length());

	strDebug = L"MP : ";
	strDebug += std::to_wstring(m_tInfo.m_iMP);
	TextOut(_DC, (int)vPos.x + 50, (int)vPos.y - 140, strDebug.c_str(), (int)strDebug.length());

	strDebug = L"Heart : ";
	strDebug += std::to_wstring(m_tInfo.m_iHeart);
	TextOut(_DC, (int)vPos.x + 50, (int)vPos.y - 120, strDebug.c_str(), (int)strDebug.length());
}

void CPlayer::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::MONSTER_PROJECTILE == pObj->GetLayer() ||
		ELAYER::MONSTER == pObj->GetLayer())
	{
		Vec2 vObjPos = pObj->GetPos();

		bool bDir = false;

		if (vObjPos.x >= GetPos().x)
			bDir = true;

		int iDmg = 10;
		CMonster* pMonster = dynamic_cast<CMonster*>(pObj);
		if (nullptr != pMonster)
		{
			iDmg = pMonster->GetMonsterInfo().m_iAtk;
		}

		TakeDamage(iDmg, bDir);
	}
}

void CPlayer::OnOverlap(CCollider* _pOther)
{

}

void CPlayer::EndOverlap(CCollider* _pOther)
{
}

void CPlayer::SetWeapon(CWeapon* _pWeapon)
{
	if (nullptr != m_pWeapon)
		m_pWeapon->SetOwner(nullptr);

	m_pWeapon = _pWeapon;

	if (nullptr != m_pWeapon)
		m_pWeapon->SetOwner(this);
}

void CPlayer::Duck()
{
	m_bIsDuck = true;
	GetCollider()->SetScale(Vec2(64.f, 100.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));
}

void CPlayer::GetUp()
{
	m_bIsDuck = false;
	GetCollider()->SetScale(Vec2(64.f, 180.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -90.f));
}

bool CPlayer::Attack()
{
	if (ATTACK_COOL <= m_fAttackAcc)
	{
		m_fAttackAcc = 0.f;
		return true;
	}
	else
		return false;
}

void CPlayer::Skill()
{
	CEffect* pEffect = new CEffect;

	pEffect->GetAnimator()->LoadAnimation(L"animation\\Weapon\\BIBLE_CRASH.anim");
	pEffect->GetAnimator()->Play(L"Bible_Crash", false);

	Vec2 vPos = GetPos();

	vPos.x -= 500.f;
	//vPos.y -= 200.f;
	Instantiate(pEffect, vPos, ELAYER::EFFECT);
}

void CPlayer::UseSubWeapon()
{
	switch (m_eSubWeapon)
	{
	case ESUB_WEAPON_TYPE::DAGGER:
		UseDagger();
		break;
	case ESUB_WEAPON_TYPE::AXE:
		UseAxe();
		break;
	case ESUB_WEAPON_TYPE::WATCH:
		break;
	case ESUB_WEAPON_TYPE::HOLY_WATER:
		break;
	case ESUB_WEAPON_TYPE::BIBLE:
		UseBible();
		break;
	}
}

void CPlayer::UseDagger()
{
	if (USE_DAGGER > GetPlayerInfo().m_iHeart)
		return;

	Vec2 vPos = GetPos();

	m_tInfo.m_iHeart -= USE_DAGGER;
	CDagger* pDagger = new CDagger;
	int iDmg = (int)((float)m_tInfo.m_iStr * 1.2);
	pDagger->SetDamage(iDmg);
	pDagger->SetFaceDir(GetFaceDir());
	if (GetFaceDir())
	{
		vPos.x += 50.f;
		vPos.y -= 150.f;
	}
	else
	{
		vPos.x -= 50.f;
		vPos.y -= 150.f;
	}
	Instantiate(pDagger, vPos, ELAYER::PLAYER_PROJECTILE);
}

void CPlayer::UseAxe()
{
	if (USE_AXE > GetPlayerInfo().m_iHeart)
		return;

	Vec2 vPos = GetPos();

	m_tInfo.m_iHeart -= USE_AXE;
	CAxe* pAxe = new CAxe;
	int iDmg = (int)((float)m_tInfo.m_iStr * 2);
	pAxe->SetDamage(iDmg);
	pAxe->SetFaceDir(GetFaceDir());
	if (GetFaceDir())
	{
		vPos.x += 0.f;
		vPos.y -= 150.f;
		pAxe->GetRigidBody()->AddVelocity(Vec2(400.f, -1000.f));
		pAxe->GetAnimator()->Play(L"Axe_Right", true);
	}
	else
	{
		vPos.x -= 0.f;
		vPos.y -= 150.f;
		pAxe->GetRigidBody()->AddVelocity(Vec2(-400.f, -1000.f));
		pAxe->GetAnimator()->Play(L"Axe_Left", true);
	}
	Instantiate(pAxe, vPos, ELAYER::PLAYER_PROJECTILE);
}

void CPlayer::UseBible()
{
	if (USE_BIBLE > GetPlayerInfo().m_iHeart)
		return;

	Vec2 vPos = GetPos();

	m_tInfo.m_iHeart -= USE_BIBLE;
	CBible* pBible = new CBible;
	int iDmg = (int)((float)m_tInfo.m_iStr * 1.5);
	pBible->SetDamage(iDmg);
	
	pBible->SetCenter(this);
	Instantiate(pBible, vPos, ELAYER::PLAYER_PROJECTILE);
}

// 데미지 주는 함수
void CPlayer::TakeDamage(int _iDmg, bool _bDir)
{
	if (true == m_bIsHit)
		return;

	m_bIsHit = true;
	SetFaceDir(_bDir);

	int iDamage = _iDmg - m_tInfo.m_iCon;

	if (0 >= iDamage)
		iDamage = 1;

	m_tInfo.m_iHP -= iDamage;

	if (0 > m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = 0;
		//SetDead();
	}
	else if ((int)m_tInfo.m_iMaxHP < m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = m_tInfo.m_iMaxHP;
	}
}

int CPlayer::GetDamage()
{
	int iDmg = m_tInfo.m_iStr;

	if (nullptr != m_pWeapon)
		iDmg += m_pWeapon->GetWeaponInfo().m_iStr;

	return iDmg;
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

void CPlayer::Copy(CPlayer* _Other)
{
	SetFaceDir(_Other->GetFaceDir());
	m_tInfo = _Other->m_tInfo;
	m_bPrevFaceDir = _Other->m_bPrevFaceDir;
	m_pWeapon = _Other->m_pWeapon;
	m_eSubWeapon = _Other->m_eSubWeapon;
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