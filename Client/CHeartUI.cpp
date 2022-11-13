#include "pch.h"
#include "CHeartUI.h"

#include "CObjMgr.h"
#include "CResMgr.h"

#include "CPlayer.h"

#include "CTexture.h"

CHeartUI::CHeartUI()	:
	m_iLength(0)
{
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

    int iWidth = GetIdleTex()->GetWidth() / 10;

    wstring strHeart = std::to_wstring(iHeart);

    m_iLength = (int)strHeart.length();
    
    vector<int> vecHeart;

    for (int i = 0; i < m_iLength; i++)
    {
        vecHeart.push_back(iHeart % 10);
        iHeart /= 10;
    }

    for (int i = 0; i < m_iLength; i++)
    {
        TransparentBlt(_DC,
            (int)(vPos.x + i * iWidth), (int)vPos.y,
            iWidth,
            GetIdleTex()->GetHeight(),
            GetIdleTex()->GetDC(),
            iWidth * vecHeart[m_iLength - 1 - i], 0,
            iWidth,
            GetIdleTex()->GetHeight(),
            RGB(255, 0, 255));
    }
}
