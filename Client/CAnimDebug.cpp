#include "pch.h"
#include "CAnimDebug.h"

#include "CCollider.h"

CAnimDebug::CAnimDebug()
{
	CreateAnimator();
	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f, 200.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, - 100.f));
}

CAnimDebug::~CAnimDebug()
{
}

void CAnimDebug::Tick()
{
	CObj::Tick();
}

void CAnimDebug::Render(HDC _DC)
{
	CObj::Render(_DC);
}

