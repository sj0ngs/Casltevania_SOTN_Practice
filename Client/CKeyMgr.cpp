#include "pch.h"
#include "CEngine.h"
#include "CKeyMgr.h"

int g_arrVK[(UINT)EKEY::END] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LMENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_TAB,

	VK_LBUTTON,
	VK_RBUTTON,

	'Q',
	'W',
	'E',
	'R',

	'A',
	'S',
	'D',
	'F',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9'
};

CKeyMgr::CKeyMgr()	:
	m_vMousePos{}
{
	
}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)EKEY::END; i++)
	{
		m_vecKey.push_back(tKeyInfo{ (EKEY)i, EKEY_STATE::NONE, false });
	}
}

void CKeyMgr::Tick()
{
	if (GetFocus())
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			// 키 입력이 있을 때
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].Key]) & 0x8000)
			{
				// 전에 입력이 없었을 때
				if (!m_vecKey[i].bPrev)
				{
					m_vecKey[i].State = EKEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				// 전에 입력이 있었을 때
				else
					m_vecKey[i].State = EKEY_STATE::PRESSED;
			}
			// 키 입력이 없을 때
			else
			{
				// 전에 입력이 있었을 때
				if (m_vecKey[i].bPrev)
				{
					m_vecKey[i].State = EKEY_STATE::RELEASED;
					m_vecKey[i].bPrev = false;
				}
				// 전에 입력이 없었을 때
				else
					m_vecKey[i].State = EKEY_STATE::NONE;
			}
		}

		// Mouse 위치 갱신
		POINT ptMousPos = {};
		GetCursorPos(&ptMousPos);
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousPos);

		m_vMousePos = ptMousPos;
	}
	else
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			if (m_vecKey[i].State == EKEY_STATE::TAP || m_vecKey[i].State == EKEY_STATE::PRESSED)
			{
				m_vecKey[i].State = EKEY_STATE::RELEASED;
				m_vecKey[i].bPrev = false;
			}
			else
				m_vecKey[i].State = EKEY_STATE::NONE;
		}
	}
}

bool CKeyMgr::IsNoEnter()
{
	for (size_t i = 0; i < m_vecKey.size(); i++)
	{
		if (EKEY_STATE::NONE != m_vecKey[i].State)
			return false;
	}

	return true;
}
