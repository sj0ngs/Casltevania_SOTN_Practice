#include "pch.h"
#include "CComponent.h"

#include "CObj.h"

CComponent::CComponent(CObj* _pOwner)	:
	m_pOwner(_pOwner)
{
}

CComponent::~CComponent()
{
}
