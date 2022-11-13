#include "pch.h"
#include "CHP.h"

#include "CObjMgr.h"
#include "CResMgr.h"

#include "CPlayer.h"

#include "CTexture.h"

CHP::CHP()  :
    m_iLength(0)
{
}

CHP::~CHP()
{
}

void CHP::Tick()
{
    CUI::Tick();
}

void CHP::Render(HDC _DC)
{
    Vec2 vPos = GetFinalPos();

    CPlayer* pPlayer = (CPlayer*)CObjMgr::GetInst()->FindObj(L"Player");
    int HP = pPlayer->GetPlayerInfo().m_iHP;

    int iWidth = GetIdleTex()->GetWidth() / 10;
    Vec2 vOffsetPos = Vec2((float)iWidth, 0.f);

    wstring strHP = std::to_wstring(HP);
    m_iLength = (int)strHP.length();

    switch (m_iLength)
    {
    case 1:    // 1의 자리만 존재
    {
        m_arrPos[0] = vPos;
    }
    break;
    case 2:     // 10의 자리까지 존재
    {
        m_arrPos[0] = vPos + vOffsetPos / 2.f;
        m_arrPos[1] = vPos - vOffsetPos / 2.f;
    }
    break;
    case 3:     // 100의 자리까지 존재
    {
        m_arrPos[0] = vPos + vOffsetPos;
        m_arrPos[1] = vPos;
        m_arrPos[2] = vPos - vOffsetPos;
    }
    break;
    case 4:     // 1000의 자리까지 존재
    {
        m_arrPos[0] = vPos + vOffsetPos * 1.5f;
        m_arrPos[1] = vPos + vOffsetPos / 2.f;
        m_arrPos[2] = vPos - vOffsetPos / 2.f;
        m_arrPos[3] = vPos - vOffsetPos * 1.5f;
    }
    break;
    }

    for (int i = 0; i < m_iLength; i++)
    {
        int iIdx = HP % 10;
        TransparentBlt(_DC,
            (int)m_arrPos[i].x, (int)m_arrPos[i].y,
            iWidth,
            GetIdleTex()->GetHeight(),
            GetIdleTex()->GetDC(),
            iWidth * iIdx, 0,
            iWidth,
            GetIdleTex()->GetHeight(),
            RGB(255, 0, 255));

        HP /=10;
    }
}
