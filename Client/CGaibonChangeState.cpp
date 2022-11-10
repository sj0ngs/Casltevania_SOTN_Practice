#include "pch.h"
#include "CGaibonChangeState.h"

#include "CGaibon.h"
#include "CAnimator.h"

CGaibonChangeState::CGaibonChangeState()
{
}

CGaibonChangeState::~CGaibonChangeState()
{
}

void CGaibonChangeState::Final_Tick()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	if (pGaibon->GetAnimator()->GetCurAnimation()->IsFinish())
	{
		ChangeState(L"GaibonMove");
	}

	Dead();
}

void CGaibonChangeState::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->Change();
}

void CGaibonChangeState::Exit()
{
}
