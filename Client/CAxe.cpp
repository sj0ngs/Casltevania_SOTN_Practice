#include "pch.h"
#include "CAxe.h"

#include "CRigidBody.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CAnimator.h"

CAxe::CAxe()	:
	m_pLeftTex(nullptr),
	m_pRightTex(nullptr)
{
	CreateRigidBody();
	CreateAnimator();
	
	GetCollider()->SetScale(Vec2(100.f, 100.f));
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(2000.f);
	GetRigidBody()->SetMass(1.f);
	GetRigidBody()->SetFriction(100.f);

	GetAnimator()->LoadAnimation(L"animation\\Weapon\\AXE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Weapon\\AXE_LEFT.anim");
}

CAxe::~CAxe()
{
}

void CAxe::Tick()
{
	MapOut();
}

void CAxe::Render(HDC _DC)
{
	//Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	//Vec2 vRealPos = GetPos();

	//CTexture* pTex = nullptr;
	//if (GetFaceDir())
	//	pTex = m_pRightTex;
	//else
	//	pTex = m_pLeftTex;

	//TransparentBlt(_DC,
	//	(int)(vPos.x - pTex->GetWidth() / 2.f),
	//	(int)(vPos.y - pTex->GetHeight() / 2.f),
	//	(int)(pTex->GetWidth()),
	//	(int)(pTex->GetHeight()),
	//	pTex->GetDC(),
	//	0, 0,
	//	(int)(pTex->GetWidth()),
	//	(int)(pTex->GetHeight()),
	//	RGB(255, 0, 255));
	
	//POINT point[3];
	//point[0].x = (int)vPos.x - (int)(pTex->GetWidth() / 2.f);
	//point[0].y = (int)vPos.y - (int)(pTex->GetHeight() / 2.f);
	//						   
	//point[1].x = (int)vPos.x + (int)(pTex->GetWidth() / 2.f);
	//point[1].y = (int)vPos.y - (int)(pTex->GetHeight() / 2.f);
	//						   
	//point[2].x = (int)vPos.x - (int)(pTex->GetWidth() / 2.f);
	//point[2].y = (int)vPos.y + (int)(pTex->GetHeight() / 2.f);

	//Vec2 DirVec[3];
	//Vec2 RotVec[3];5
	//
	//for (int i = 0; i < 3; i++)
	//{
	//	Vec2 vPoint = point[i];
	//	DirVec[i] = vPoint - vPos;
	//	float Dist = DirVec[i].Length();
	//	DirVec[i].Normalize();
	//	RotateVec(DirVec[i], 15.f);
	//	RotVec[i] *= Dist; 
	//	point[i].x = RotVec[i].x + vPos.x;
	//	point[i].y = RotVec[i].y + vPos.y;
	//}
	
	//int a = PlgBlt(_DC, point, pTex->GetDC(), 
	//	vPos.x - pTex->GetWidth() / 2.f, 
	//	vPos.y - pTex->GetHeight() / 2.f,
	//	pTex->GetWidth(), pTex->GetHeight(),
	//	nullptr, 0, 0);

	CObj::Render(_DC);
}

void CAxe::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);

	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::MONSTER == pObj->GetLayer())
	{
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

		if (GetFaceDir())
		{
			SetFaceDir(false);
			GetRigidBody()->AddVelocity(Vec2(-200.f, -500.f));
			GetAnimator()->Play(L"Axe_Left", true);
		}
		else
		{
			SetFaceDir(true);
			GetRigidBody()->AddVelocity(Vec2(200.f, -500.f));
			GetAnimator()->Play(L"Axe_Right", true);
		}
	}
}
