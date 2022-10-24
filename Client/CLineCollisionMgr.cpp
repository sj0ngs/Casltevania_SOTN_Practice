#include "pch.h"
#include "CLineCollisionMgr.h"

#include "CLevelMgr.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CLine.h"

CLineCollisionMgr::CLineCollisionMgr()	:
	m_CollisionProfile(0)
{
}

CLineCollisionMgr::~CLineCollisionMgr()
{
}

void CLineCollisionMgr::Tick()
{
	for (UINT i = 0; i < (UINT)ELAYER::END; i++)
	{
		if (!(m_CollisionProfile & (1 << i)))
			continue;

		CollisionLayerToLine((ELAYER)i);
	}
}

void CLineCollisionMgr::CollisionSet(ELAYER _eLayer)
{
	m_CollisionProfile |= (1 << (UINT)_eLayer);
}

void CLineCollisionMgr::clear()
{
	m_CollisionProfile = 0;
}

void CLineCollisionMgr::CollisionLayerToLine(ELAYER _Layer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*>& vecObj = pCurLevel->GetLayer(_Layer);
	const vector<CObj*>& vecLine = pCurLevel->GetLayer(ELAYER::LINE);
	
	for (size_t i = 0; i < vecLine.size(); i++)
	{	
		for (size_t j = 0; j < vecObj.size(); j++)
		{
			LineCollisionID ID = {};
			ID.ObjectID = vecObj[j]->GetId();
			ID.LineID = vecLine[i]->GetId();

			// 이전 프레임 충돌
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecObj[j]->IsDead() || vecLine[i]->IsDead();

			if (CollisionObjToLine(vecObj[j], (CLine*)vecLine[i]))
			{
				// 이전에도 겹쳐있었다
				if (iter->second)
				{
					// 둘중 하나라도 dead 일 경우
					if (bDead)
					{
						((CLine*)vecLine[i])->EndOverlap(vecObj[j]);
					}
					else
					{
						((CLine*)vecLine[i])->OnOverlap(vecObj[j]);
					}
				}
				// 이번에 겹쳐졌다
				else
				{
					// 둘중 하나라도 Dead 상태라면 충돌이 없었던 걸로 한다
					if (!bDead)
					{
						((CLine*)vecLine[i])->BeginOverlap(vecObj[j]);
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
					((CLine*)vecLine[i])->EndOverlap(vecObj[j]);
					iter->second = false;
				}
			}
		}
	}
}

bool CLineCollisionMgr::CollisionObjToLine(CObj* _Obj, CLine* _Line)
{
	bool result = false;

	// 라인의 타입에 따라 충돌체크를 한다
	switch (_Line->GetType())
	{
	case ELINE_TYPE::UP:
		result = UpLineCheck(_Obj, _Line->GetLine());
		break;
	case ELINE_TYPE::DOWN:
		result = DownLineCheck(_Obj, _Line->GetLine());
		break;
	}
	return result;
}

bool CLineCollisionMgr::UpLineCheck(CObj* _Obj, tLine& _Line)
{
	Vec2 vPos = _Obj->GetPos();

	float x1 = _Line.v1.x;
	float x2 = _Line.v2.x;
	float y1 = _Line.v1.y;
	float y2 = _Line.v2.y;

	if (x1 > x2)
	{
		float temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if (x1 <= vPos.x && x2 >= vPos.x &&
		y1 <= vPos.y && y2 >= vPos.y)
	{
		float Y = _Line.GetPoint(vPos.x) - 1.f;
		
		if(Y <= vPos.y)
			return true;
	}
	return false;
}

bool CLineCollisionMgr::DownLineCheck(CObj* _Obj, tLine& _Line)
{
	Vec2 vPos = _Obj->GetPos();
	Vec2 vScale = _Obj->GetCollider()->GetScale();
	vPos.y -= vScale.y;

	float x1 = _Line.v1.x;
	float x2 = _Line.v2.x;
	float y1 = _Line.v1.y;
	float y2 = _Line.v2.y;

	if (x1 > x2)
	{
		float temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if (x1 < vPos.x && x2 > vPos.x &&
		y1 <= vPos.y && y2 >= vPos.y)
	{
		float Y = _Line.GetPoint(vPos.x) + 1.f;

		if (Y >= vPos.y)
			return true;
	}
	return false;
}