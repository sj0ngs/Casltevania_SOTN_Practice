#include "pch.h"
#include "CDamage.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

CDamage::CDamage() :
    m_iDmg(0),
    m_pTex(nullptr),
    m_eType(EDMG_TYPE::NONE),
    m_iWidth(0),
    m_faccTime(0.f),
    m_tBlend{}
{
    m_tBlend.AlphaFormat = AC_SRC_ALPHA;
    m_tBlend.BlendFlags = 0;
    m_tBlend.BlendOp = AC_SRC_OVER;
    m_tBlend.SourceConstantAlpha = (int)(255);
}

CDamage::~CDamage()
{
}

void CDamage::SetDmgType(EDMG_TYPE _eType)
{
    m_eType = _eType;

    switch (m_eType)
    {
    case EDMG_TYPE::PLAYER:
        m_pTex = CResMgr::GetInst()->FindTexture(L"Red_Num");
        break;
    case EDMG_TYPE::MONSTER:
        m_pTex = CResMgr::GetInst()->FindTexture(L"Lemon_Num");
        break;
    }

    m_iWidth = 32;
}

void CDamage::Tick()
{
    Vec2 vPos = GetPos();

    vPos.y -= 15.f * DELTATIME;

    m_faccTime += DELTATIME;

    if (2.f <= m_faccTime)
    {
        SetDead();
    }

    SetPos(vPos);
}

void CDamage::Render(HDC _DC)
{
    Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

    int iDmg = m_iDmg;

    float _fRatio = 1.1f - m_faccTime / 2.f;

    m_tBlend.SourceConstantAlpha = (int)(255 * _fRatio);

    for (int i = 0; iDmg > 0; i++)
    {
        int iIdx = iDmg % 10;

        AlphaBlend(_DC,
            (int)(vPos.x - i * 16), (int)vPos.y,
            m_iWidth, m_pTex->GetHeight(),
            m_pTex->GetDC(),
            m_iWidth * iIdx, 0,
            m_iWidth, m_pTex->GetHeight(),
            m_tBlend);

        iDmg /= 10;
    }
}
