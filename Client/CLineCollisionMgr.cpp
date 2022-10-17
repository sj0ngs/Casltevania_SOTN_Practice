#include "pch.h"
#include "CLineCollisionMgr.h"

#include "CLevelMgr.h"
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
	// 오브젝트의 이동 직선과 라인이 교점이 생기는지 체크한다
	tLine ObjLine = tLine(_Obj->GetPos(), _Obj->GetPrevPos());
	tLine Line = tLine(_Line->GetPos1(), _Line->GetPos2());

	Vec2 vMeetPoint = {};

	if (ERLTNS_TWOST::MEET != ObjLine.MeetPoint(Line, vMeetPoint))
		return false;

	bool result = false;

	// 라인의 타입에 따라 충돌체크를 한다
	switch (_Line->GetType())
	{
	case ELINE_TYPE::UP:
		result = UpLineCheck(_Obj, _Line, vMeetPoint);
		break;
	case ELINE_TYPE::DOWN:
		result = DownLineCheck(_Obj, _Line, vMeetPoint);
		break;
	case ELINE_TYPE::LEFT:
		result = LeftLineCheck(_Obj, _Line, vMeetPoint);
		break;
	case ELINE_TYPE::RIGHT:
		result = RightLineCheck(_Obj, _Line, vMeetPoint);
		break;
	}
	return result;
}

bool CLineCollisionMgr::UpLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint)
{
	Vec2 vPos = _Obj->GetPos();
	Vec2 vScale = _Obj->GetCollider()->GetScale();

	Vec2 vDir = vPos - vScale;
	if (0 >= vDir.y)
		return false;

	// 충돌 검사를 함 지점을 오브젝트의 아래 끝으로 설정한다
	// vPos.y += vScale.y / 2.f;

	float x1 = _Line->GetPos1().x;
	float x2 = _Line->GetPos2().x;
	float y1 = _Line->GetPos1().y;
	float y2 = _Line->GetPos2().y;
	
	if (x1 > x2)
	{
		float temp = x1;
		x2 = x1;
		x1 = temp;
	}
	// y1 값이 무조건 더 크게 설정
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// 라인의 영역 사이에 교점이 있었는지 확인
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// 교점보다 오브젝트의 현재 위치가 아래라면 충돌이 생긴것임
		if (_vMeetPoint.y <= vPos.y)
			return true;
	}

	return false;
}

bool CLineCollisionMgr::DownLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint)
{
	Vec2 vPos = _Obj->GetPos();
	Vec2 vScale = _Obj->GetScale();

	Vec2 vDir = vPos - vScale;
	if (0 <= vDir.y)
		return false;

	float x1 = _Line->GetPos1().x;
	float x2 = _Line->GetPos2().x;
	float y1 = _Line->GetPos1().y;
	float y2 = _Line->GetPos2().y;

	// 충돌 검사를 함 지점을 오브젝트의 위 끝으로 설정한다
	vPos.y -= vScale.y / 2.f;

	// y1 값이 무조건 더 작게 설정
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// 라인의 영역 사이에 교점이 있었는지 확인
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// 교점보다 오브젝트의 현재 위치가 아래라면 충돌이 생긴것임
		if (_vMeetPoint.y <= _Obj->GetPos().y)
			return true;
	}

	return false;
}

bool CLineCollisionMgr::LeftLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint)
{
	float x1 = _Line->GetPos1().x;
	float x2 = _Line->GetPos2().x;
	float y1 = _Line->GetPos1().y;
	float y2 = _Line->GetPos2().y;

	// y1 값이 무조건 더 작게 설정
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// 라인의 영역 사이에 교점이 있었는지 확인
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// 교점보다 오브젝트의 현재 위치가 아래라면 충돌이 생긴것임
		if (_vMeetPoint.y >= _Obj->GetPos().y)
			return true;
	}

	return false;
}

bool CLineCollisionMgr::RightLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint)
{
	float x1 = _Line->GetPos1().x;
	float x2 = _Line->GetPos2().x;
	float y1 = _Line->GetPos1().y;
	float y2 = _Line->GetPos2().y;

	// y1 값이 무조건 더 작게 설정
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// 라인의 영역 사이에 교점이 있었는지 확인
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// 교점보다 오브젝트의 현재 위치가 아래라면 충돌이 생긴것임
		if (_vMeetPoint.y >= _Obj->GetPos().y)
			return true;
	}

	return false;
}
