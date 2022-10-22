#include "pch.h"
#include "CBackGround.h"

#include "CResMgr.h"

#include "CTexture.h"

CBackGround::CBackGround()	:
	m_pBackGroundTex(nullptr),
	m_bIsForeGround(false)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Tick()
{

}

void CBackGround::Render(HDC _DC)
{
	if (nullptr == m_pBackGroundTex)
		return;

	Vec2 vPos = GetPos();

	if(m_bIsForeGround)
		vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	BitBlt(_DC,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)m_pBackGroundTex->GetWidth(), (int)m_pBackGroundTex->GetHeight(),
		m_pBackGroundTex->GetDC(),
		0, 0,
		SRCCOPY);

	CObj::Render(_DC);
}
