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

			// ���� ������ �浹
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);

			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}

			bool bDead = vecObj[j]->IsDead() || vecLine[i]->IsDead();

			if (CollisionObjToLine(vecObj[j], (CLine*)vecLine[i]))
			{
				// �������� �����־���
				if (iter->second)
				{
					// ���� �ϳ��� dead �� ���
					if (bDead)
					{
						((CLine*)vecLine[i])->EndOverlap(vecObj[j]);
					}
					else
					{
						((CLine*)vecLine[i])->OnOverlap(vecObj[j]);
					}
				}
				// �̹��� ��������
				else
				{
					// ���� �ϳ��� Dead ���¶�� �浹�� ������ �ɷ� �Ѵ�
					if (!bDead)
					{
						((CLine*)vecLine[i])->BeginOverlap(vecObj[j]);
						iter->second = true;
					}
				}
			}
			// ���� �������ִ�
			else
			{
				// ���� �� ��������
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
	// ������Ʈ�� �̵� ������ ������ ������ ������� üũ�Ѵ�
	tLine ObjLine = tLine(_Obj->GetPos(), _Obj->GetPrevPos());
	tLine Line = tLine(_Line->GetPos1(), _Line->GetPos2());

	Vec2 vMeetPoint = {};

	if (ERLTNS_TWOST::MEET != ObjLine.MeetPoint(Line, vMeetPoint))
		return false;

	bool result = false;

	// ������ Ÿ�Կ� ���� �浹üũ�� �Ѵ�
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

	// �浹 �˻縦 �� ������ ������Ʈ�� �Ʒ� ������ �����Ѵ�
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
	// y1 ���� ������ �� ũ�� ����
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// ������ ���� ���̿� ������ �־����� Ȯ��
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// �������� ������Ʈ�� ���� ��ġ�� �Ʒ���� �浹�� �������
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

	// �浹 �˻縦 �� ������ ������Ʈ�� �� ������ �����Ѵ�
	vPos.y -= vScale.y / 2.f;

	// y1 ���� ������ �� �۰� ����
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// ������ ���� ���̿� ������ �־����� Ȯ��
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// �������� ������Ʈ�� ���� ��ġ�� �Ʒ���� �浹�� �������
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

	// y1 ���� ������ �� �۰� ����
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// ������ ���� ���̿� ������ �־����� Ȯ��
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// �������� ������Ʈ�� ���� ��ġ�� �Ʒ���� �浹�� �������
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

	// y1 ���� ������ �� �۰� ����
	if (y1 > y2)
	{
		float temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// ������ ���� ���̿� ������ �־����� Ȯ��
	if (x1 <= _vMeetPoint.x && x2 >= _vMeetPoint.x &&
		y1 <= _vMeetPoint.y && y2 >= _vMeetPoint.y)
	{
		// �������� ������Ʈ�� ���� ��ġ�� �Ʒ���� �浹�� �������
		if (_vMeetPoint.y >= _Obj->GetPos().y)
			return true;
	}

	return false;
}
