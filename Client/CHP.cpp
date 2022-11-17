#include "pch.h"
#include "CHP.h"

#include "CObjMgr.h"
#include "CResMgr.h"

#include "CPlayer.h"

#include "CTexture.h"

CHP::CHP()
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

    int iWidth = 32; //32

    wstring strHP = std::to_wstring(HP);
    int iLength = (int)strHP.length();

    vPos.x += iLength * iWidth / 2.f - iWidth / 2.f;

    for (int i = 0; i < iLength; i++)
    {
        int iIdx = HP % 10;
        TransparentBlt(_DC,
            (int)(vPos.x - iWidth * i), (int)(vPos.y),
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
