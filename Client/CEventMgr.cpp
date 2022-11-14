#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "CObj.h"

#include "CAI.h"
#include "CState.h"

#include "CAnimator.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::Tick()
{
	// 삭제 예정 오브젝트 삭제
	for (size_t i = 0; i < m_vecGarbage.size(); i++)
	{
		delete m_vecGarbage[i];
	}
	m_vecGarbage.clear();

	// 이벤트 처리
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		switch (m_vecEvent[i].eType)
		{
			// wParam : Object Address
			// lParam : Layer Type
		case EEVENT_TYPE::CREATE_OBJECT:
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CObj* pNewObj = (CObj*)m_vecEvent[i].wParam;
			ELAYER Layer = (ELAYER)m_vecEvent[i].lParam;

			pCurLevel->AddObj(pNewObj, Layer);
		}
		break;
		case EEVENT_TYPE::DELETE_OBJECT:
		{
			// 삭제 예정 오브젝트를 Dead 상태로 두고 Garbage에 넣어준다
			CObj* pObj = (CObj*)m_vecEvent[i].wParam;

			// 아주 낮은 확률로 같은 Tick 동시에 같은 오브젝트의 삭제를 요청 했을 때
			if (false == pObj->m_bDead)
			{
				m_vecGarbage.push_back(pObj);
				pObj->m_bDead = true;
			}
		}
		break;
		case EEVENT_TYPE::LEVEL_CHANGE:
		{
			// wParam : Next Level Type
			ELEVEL_TYPE eNextLevel = (ELEVEL_TYPE)m_vecEvent[i].wParam;

			CLevelMgr::GetInst()->ChangeLevel(eNextLevel);
		}
		break;
		case EEVENT_TYPE::CHANGE_AI_STATE:
		{
			// wParam  : AI Address			
			//lParam : State Type
			AI* pAI = (AI*)m_vecEvent[i].wParam;
			const wchar_t* pName = (const wchar_t*)m_vecEvent[i].lParam;
			pAI->ChangeState(pName);
		}
		break;
		}
	}
	m_vecEvent.clear();
}
 