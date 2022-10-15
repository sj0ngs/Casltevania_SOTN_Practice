#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"

#include "CCollider.h"
#include "CLevel.h"
#include "CObj.h"

CCollisionMgr::CCollisionMgr()	:
	m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Tick()
{
	for (UINT iRow = 0; iRow < (UINT)ELAYER::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)ELAYER::END; iCol++)
		{
			if (!(m_Matrix[iRow] & (1 << iCol)))
				continue;

			CollisionBtwLayer((ELAYER)iRow, (ELAYER)iCol);
		}
	}
}

void CCollisionMgr::LayerCheck(ELAYER _Left, ELAYER _Right)
{
	UINT iRow = (UINT)_Left;
	UINT iCol = (UINT)_Right;

	if (iRow > iCol)
	{
		int iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_Matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::Clear()
{
	for (int i = 0; i < (UINT)ELAYER::END; i++)
	{
		m_Matrix[i] = 0;
	}
}

void CCollisionMgr::CollisionBtwLayer(ELAYER _Left, ELAYER _Right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	
	const std::vector<CObj*>& vecLeft = pCurLevel->GetLayer(_Left);
	const std::vector<CObj*>& vecRight = pCurLevel->GetLayer(_Right);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		size_t j = 0;
		if (_Left == _Right)	// 동일한 레이어인 경우 이중 검사를 피하기 위한 예외 처리
		{
			j = i;
		}

		for (; j < vecRight.size(); j++)
		{
			// 충돌체가 없거나 자기 자신을 출동 비교할 때 예외 처리
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;

			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->GetCollider()->GetId();
			ID.RightID = vecRight[j]->GetCollider()->GetId();

			// 이전 프레임 충돌
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			// 지금 겹쳐있다
			if (CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// 이전에도 겹쳐있었다
				if (iter->second)
				{
					// 둘중 하나라도 dead 일 경우
					if (bDead)
					{
						vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					}
					else
					{
						vecLeft[i]->GetCollider()->OnOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnOverlap(vecLeft[i]->GetCollider());
					}
				}
				// 이번에 겹쳐졌다
				else
				{
					// 둘중 하나라도 Dead 상태라면 충돌이 없었던 걸로 한다
					if (!bDead)
					{
						vecLeft[i]->GetCollider()->BeginOverlap(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->BeginOverlap(vecLeft[i]->GetCollider());
						iter->second = true;
					}
				}
			}
			// 지금 떨어져있다
			else
			{
				// 지금 막 떨어졌다
				if (iter->second)
				{
					vecLeft[i]->GetCollider()->EndOverlap(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->EndOverlap(vecLeft[i]->GetCollider());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();
	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vRightScale = _pRight->GetScale();

	if (fabsf(vLeftPos.x - vRightPos.x) > fabsf((vLeftScale.x + vRightScale.x) / 2))
		return false;

	if (fabsf(vLeftPos.y - vRightPos.y) > fabsf((vLeftScale.y + vRightScale.y) / 2))
		return false;

	return true;
}