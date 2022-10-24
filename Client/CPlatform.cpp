#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CRigidBody.h"

CPlatform::CPlatform()	:
	m_UpLine{},
	m_DownLine{},
	m_LeftLine{},
	m_RightLine{},
	m_vLeftTop{},
	m_vRightTop{},
	m_vLeftDown{},
	m_vRightDown{},
	m_eType(EPLATFORM_TYPE::FLOOR)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(TILE_SIZE * 5.f, TILE_SIZE));
}

CPlatform::CPlatform(const CPlatform& _Origin)	:
	CObj(_Origin),
	m_UpLine{},
	m_DownLine{},
	m_LeftLine{},
	m_RightLine{},
	m_vLeftTop{},
	m_vRightTop{},
	m_vLeftDown{},
	m_vRightDown{},
	m_eType(_Origin.m_eType)
{
}

CPlatform::~CPlatform()
{
}

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	SetPoint();

	Vec2 vObjPos = pObj->GetPos();
	Vec2 vObjPrevPos = pObj->GetPrevPos();
	
	Vec2 vDir = vObjPos - vObjPrevPos;

	if (EPLATFORM_TYPE::FLOOR == m_eType)
	{
		// 플레이어가 추락 중일 때
		if (0.f <= vDir.y)
		{
			// 윗변에 교점이 생겼다면 종료
			if (UpCheck(pObj))
				return;

			// 왼쪽에서 접근했을 때
			if (0.f < vDir.x)
			{
				LeftCheck(pObj);
				return;
			}
			// 오른쪽에서 접근했을 때
			if (0.f > vDir.x)
			{
				RightCheck(pObj);
				return;
			}
		}
		// 상승중일 때 
		else if (0.f > vDir.y)
		{
			// 아래변에 교점이 생겼다면 종료
			if (DownCheck(pObj))
				return;

			// 왼쪽에서 접근했을 때
			if (0.f < vDir.x)
			{
				LeftCheck(pObj);
				return;
			}
			// 오른쪽에서 접근했을 때
			if (0.f > vDir.x)
			{
				RightCheck(pObj);
				return;
			}
		}
		//// 벽에 부딪혔을때
		//else if (0.f == vDir.y)
		//{
		//	// 왼쪽에서 접근했을 때
		//	if (0.f < vDir.x)
		//	{
		//		LeftCheck(pObj);
		//		return;
		//	}
		//	// 오른쪽에서 접근했을 때
		//	if (0.f > vDir.x)
		//	{
		//		RightCheck(pObj);
		//		return;
		//	}
		//}
	}
	else
	{
		// 플레이어가 추락 중일 때
		if (0.f < vDir.y)
		{
			// 윗변에 교점이 생겼다면 종료
			if (UpCheck(pObj))
				return;
		}
	}
}

// 겹쳐진 만큼 계속 밀어준다
void CPlatform::OnOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	map<UINT, EPLATFORM_STATUS>::iterator iter = m_mapPlatformStatus.find(pObj->GetId());

	if (iter == m_mapPlatformStatus.end())
		return;

	Vec2 vObjPos = pObj->GetPos();

	Vec2 vDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
	Vec2 vLength = GetCollider()->GetScale() / 2.f;

	switch (iter->second)
	{
	case EPLATFORM_STATUS::UP:
	{
		if (vLength.y > vDist.y)
		{
			vObjPos.y -= (vLength.y - vDist.y);
			pObj->SetPos(vObjPos);
		}
	}
		break;
	case EPLATFORM_STATUS::LEFT:
	{
		vLength += pObj->GetCollider()->GetScale() / 2.f;
		if (vLength.x > vDist.x)
		{
			vObjPos.x -= (vLength.x - vDist.x);
			pObj->SetPos(vObjPos);
		}
	}
		break;
	case EPLATFORM_STATUS::RIGHT:
	{
		vLength += pObj->GetCollider()->GetScale() / 2.f;
		if (vLength.x > vDist.x)
		{
			vObjPos.x += (vLength.x - vDist.x);
			pObj->SetPos(vObjPos);
		}
	}
		break;
	case EPLATFORM_STATUS::DOWN:
	{
		vLength += pObj->GetCollider()->GetScale();
		if (vLength.y > vDist.y)
		{
			vObjPos.y += (vLength.y - vDist.y);
			pObj->SetPos(vObjPos);
		}
	}
		break;	
	}
}

void CPlatform::EndOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	map<UINT, EPLATFORM_STATUS>::iterator iter = m_mapPlatformStatus.find(pObj->GetId());

	if (iter == m_mapPlatformStatus.end())
		return;

	switch (iter->second)
	{
	case EPLATFORM_STATUS::UP:
	{
		Vec2 vDir = _pOther->GetOwner()->GetDir();

		if(Vec2(1.f, 0.f) == vDir)
			pObj->GetRigidBody()->OffGround();
	}
		break;
	}

	m_mapPlatformStatus.erase(iter);
}

void CPlatform::SetPoint()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetCollider()->GetScale() / 2.f;

	m_vLeftTop = Vec2(vPos.x - vScale.x, vPos.y - vScale.y);
	m_vRightTop = Vec2(vPos.x + vScale.x, vPos.y - vScale.y);
	m_vLeftDown = Vec2(vPos.x - vScale.x, vPos.y + vScale.y);
	m_vRightDown = Vec2(vPos.x + vScale.x, vPos.y + vScale.y);
}

bool CPlatform::UpCheck(CObj* _pObj)
{
	m_UpLine = tLine(m_vLeftTop, m_vRightTop);

	Vec2 vObjPos = _pObj->GetPos();
	Vec2 vObjPrevPos = _pObj->GetPrevPos();
	Vec2 vObjScale = _pObj->GetCollider()->GetScale();
	tLine tObjLine = tLine(vObjPos, vObjPrevPos);

	Vec2 vUPMeetPoint = m_UpLine.MeetPoint(tObjLine);

	if ((m_vLeftTop.x - vObjScale.x / 2.f) <= vUPMeetPoint.x
		&& (m_vRightTop.x + vObjScale.x / 2.f) >= vUPMeetPoint.x)
	{
		_pObj->GetRigidBody()->OnGround();

		// 오브젝트가 플레이어일때 따로 체크
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pObj);
		if(nullptr != pPlayer)
			pPlayer->ResetJump();

		m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::UP));
		return true;
	}
	return false;
}

bool CPlatform::DownCheck(CObj* _pObj)
{
	m_DownLine = tLine(m_vLeftDown, m_vRightDown);

	Vec2 vObjScale = _pObj->GetCollider()->GetScale();
	Vec2 vObjPos = _pObj->GetPos();
	Vec2 vObjPrevPos = _pObj->GetPrevPos();
	vObjPos.y -= vObjScale.y;
	vObjPrevPos.y -= vObjScale.y;

	// 플레이어의 이동 벡터를 연장한 직선을 만든다
	tLine tObjLine = tLine(vObjPos, vObjPrevPos);

	Vec2  vDownMeetPoint = m_DownLine.MeetPoint(tObjLine);

	if ((m_vLeftDown.x - vObjScale.x / 2) < vDownMeetPoint.x
		&& (m_vRightDown.x + vObjScale.x / 2) > vDownMeetPoint.x)
	{
		// 오브젝트가 플레이어일때 따로 체크
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pObj);
		if (nullptr != pPlayer)
			pPlayer->EndJump();

		m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::DOWN));
		return true;
	}
	return false;
}

void CPlatform::LeftCheck(CObj* _pObj)
{
	m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::LEFT));
}

void CPlatform::RightCheck(CObj* _pObj)
{
	m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::RIGHT));
}

void CPlatform::Save(FILE* _pFile)
{
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	Vec2 vScale = GetCollider()->GetScale();
	fwrite(&vScale, sizeof(Vec2), 1, _pFile);

	fwrite(&m_eType, sizeof(EPLATFORM_TYPE), 1, _pFile);
}

void CPlatform::Load(FILE* _pFile)
{
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	Vec2 vScale;
	fread(&vScale, sizeof(Vec2), 1, _pFile);
	GetCollider()->SetScale(vScale);

	fread(&m_eType, sizeof(EPLATFORM_TYPE), 1, _pFile);
}
