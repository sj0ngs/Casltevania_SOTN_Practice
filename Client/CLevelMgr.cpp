#include "pch.h"
#include "CLevelMgr.h"

#include "CKeyMgr.h"

#include "CLevel.h"
#include "CTitle.h"
#include "CStartLevel.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CBossLevel.h"
#include "CEndingLevel.h"
#include "CGameOverLevel.h"
#include "CSave_Level.h"
#include "CRewardLevel.h"

#include "CEditorLevel.h"
#include "CAnimationEditor.h"

#include "CObj.h"

CLevelMgr::CLevelMgr()	:
	m_arrLevel{},
	m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()	// 동적 할당된 레벨들을 전부 해제해준다
{
	for (int i = 0; i < (int)ELEVEL_TYPE::END; i++)
	{
		DYNAMIC_DELETE(m_arrLevel[i]);
	}
}

void CLevelMgr::Init()
{
	m_arrLevel[(UINT)ELEVEL_TYPE::TITLE] = new CTitle;
	m_arrLevel[(UINT)ELEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::STAGE_01] = new CStage01;
	m_arrLevel[(UINT)ELEVEL_TYPE::STAGE_02] = new CStage02;
	m_arrLevel[(UINT)ELEVEL_TYPE::STAGE_03] = new CStage03;
	m_arrLevel[(UINT)ELEVEL_TYPE::BOSS] = new CBossLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::SAVE] = new CSave_Level;
	m_arrLevel[(UINT)ELEVEL_TYPE::REWARD] = new CRewardLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::ENDING] = new CEndingLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::GAME_OVER] = new CGameOverLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::EDITOR] = new CEditorLevel;
	m_arrLevel[(UINT)ELEVEL_TYPE::ANIMATION] = new CAnimationEditor;

	ChangeLevel(ELEVEL_TYPE::TITLE);
}

void CLevelMgr::Tick()
{
	if (IS_TAP(EKEY::key9))
	{
		CObj::SwitchDebug();
	}

	m_pCurLevel->Tick();
	m_pCurLevel->Final_Tick();
}

void CLevelMgr::Render(HDC _DC)
{
	m_pCurLevel->Render(_DC);
}

void CLevelMgr::ChangeLevel(ELEVEL_TYPE _eNext)
{
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	if(nullptr != m_pCurLevel)
		m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];
	m_pCurLevel->Enter();
}

CLevel* CLevelMgr::GetLevel(ELEVEL_TYPE _eType)
{
	if (0 <= (UINT)_eType && ELEVEL_TYPE::END > _eType)
		return m_arrLevel[(UINT)_eType];
	else
	{
		assert(false);
		return nullptr;
	}
}

