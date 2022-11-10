#include "pch.h"
#include "CSlograStandBy.h"

#include "CSlogra.h"

CSlograStandBy::CSlograStandBy()
{
}

CSlograStandBy::~CSlograStandBy()
{
}

void CSlograStandBy::Final_Tick()
{
}

void CSlograStandBy::Enter()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	pSlogra->Idle();
}

void CSlograStandBy::Exit()
{
}
