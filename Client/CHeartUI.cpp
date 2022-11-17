#include "pch.h"
#include "CHeartUI.h"

#include "CObjMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

#include "CTexture.h"

CHeartUI::CHeartUI()    :
    m_tBlend{},
    m_fRatio(1.f),
    m_fDir(1.f)
{
    m_tBlend.AlphaFormat = AC_SRC_ALPHA;
    m_tBlend.BlendFlags = 0;
    m_tBlend.BlendOp = AC_SRC_OVER;
    m_tBlend.SourceConstantAlpha = (int)(255);
}

CHeartUI::~CHeartUI()
{
}

void CHeartUI::Tick()
{
	CUI::Tick();
}

void CHeartUI::Render(HDC _DC)
{
    Vec2 vPos = GetFinalPos();

    CPlayer* pPlayer = (CPlayer*)CObjMgr::GetInst()->FindObj(L"Player");
    int iHeart = pPlayer->GetPlayerInfo().m_iHeart;
    int iWidth = 20; /*GetIdleTex()->GetWidth() / 10; *///20

    wstring strHeart = std::to_wstring(iHeart);
    int iLength = (int)strHeart.length();
    vPos.x += (float)(iLength * iWidth - iLength / 2);

    m_fRatio += DELTATIME * m_fDir * 10;

    if (1.f <= m_fRatio)
    {
        m_fDir = -1.f;
        m_fRatio = 1.f;
    }
    else if (0.7 >= m_fRatio)
    {
        m_fDir = 1.f;
        m_fRatio = 0.7f;
    }

    m_tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);

    for (int i = 0; i < iLength; i++)
    {
        int iIdx = iHeart % 10;
        AlphaBlend(_DC,
            (int)(vPos.x - i * iWidth), (int)vPos.y,
            iWidth,
            GetIdleTex()->GetHeight(),
            GetIdleTex()->GetDC(),
            iWidth * iIdx, 0,
            iWidth,
            GetIdleTex()->GetHeight(),
            m_tBlend);

        iHeart /= 10;
    }
}
