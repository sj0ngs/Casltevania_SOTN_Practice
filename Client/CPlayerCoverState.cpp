#include "pch.h"
#include "CPlayerCoverState.h"

CPlayerCoverState::CPlayerCoverState()	:
	m_pCover(nullptr)
{
}

CPlayerCoverState::~CPlayerCoverState()
{
}

void CPlayerCoverState::Enter()
{
}

void CPlayerCoverState::Exit()
{
	if (nullptr != m_pCover && !m_pCover->IsDead())
		m_pCover->SetDead();
}
