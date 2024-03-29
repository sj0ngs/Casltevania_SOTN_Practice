#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "CAI.h"
#include "CState.h"

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

void CPlatform::Render(HDC _DC)
{
	if (CObj::GetDebug())
	{
		CObj::Render(_DC);

		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		switch (m_eType)
		{
		case EPLATFORM_TYPE::FLOOR:
			TextOut(_DC, (int)vPos.x, (int)vPos.y, L"Floor", lstrlen(L"Floor"));
			break;
		case EPLATFORM_TYPE::PLATFORM:
			TextOut(_DC, (int)vPos.x, (int)vPos.y, L"Platform", lstrlen(L"Platform"));
			break;
		}
	}
}

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	//if (pObj->GetLayer() == ELAYER::MONSTER)
	//{
	//	CMonster* pMon = (CMonster*)pObj;

	//	if (!pMon->GetRigidBody()->IsGravity())
	//		return;
	//}

	SetPoint();

	Vec2 vObjPos = pObj->GetPos();
	Vec2 vObjPrevPos = pObj->GetPrevPos();
	
	Vec2 vDir = vObjPos - vObjPrevPos;

	if (EPLATFORM_TYPE::FLOOR == m_eType)
	{
		// 플레이어가 추락 중일 때
		if (0.f < vDir.y)
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
			PushObj(pObj);
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
			PushObj(pObj);
		}
		// 벽에 부딪혔을때
		else if (0.f == vDir.y)
		{
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
			PushObj(pObj);
		}
	}
	else
	{
		// 플레이어가 추락 중일 때
		if (0.f < vDir.y)
		{
			// 윗변에 교점이 생겼다면 종료
			if (UpCheck(pObj))
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

				if (pPlayer)
				{
					pPlayer->SetGoDown(true);
				}
				return;
			}
		}
	}
}

void CPlatform::OnOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	map<UINT, EPLATFORM_STATUS>::iterator iter = m_mapPlatformStatus.find(pObj->GetId());

	if (iter == m_mapPlatformStatus.end())
		return;

	if (EPLATFORM_STATUS::UP != iter->second && EPLATFORM_STATUS::DOWN != iter->second)
	{
		PushObj(pObj);
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

		Vec2 vDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
		Vec2 vLength = GetCollider()->GetScale() / 2.f;

		if (vLength.y > vDist.y)
		{
			vObjPos.y -= (vLength.y - vDist.y);
			_pObj->SetPos(vObjPos);
		}

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
		{
			if (pPlayer->IsHit())
			{
				Vec2 vVelocity = pPlayer->GetRigidBody()->GetVelocity();
				vVelocity.y = 0.f;
				pPlayer->GetRigidBody()->SetVelocity(vVelocity);
			}
			else
				pPlayer->GetAI()->GetCurState()->ChangeState(L"Fall");
		}

		Vec2 vDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
		Vec2 vLength = GetCollider()->GetScale() / 2.f;

		vLength += _pObj->GetCollider()->GetScale();
		if (vLength.y > vDist.y)
		{
			vObjPos.y += (vLength.y - vDist.y);
			_pObj->SetPos(vObjPos);
		}

		m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::DOWN));
		return true;
	}
	return false;
}

void CPlatform::LeftCheck(CObj* _pObj)
{
	Vec2 vObjPos = _pObj->GetPos();

	Vec2 vDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
	Vec2 vLength = GetCollider()->GetScale() / 2.f;

	vLength += _pObj->GetCollider()->GetScale() / 2.f;
	if (vLength.x > vDist.x)
	{
		vObjPos.x -= (vLength.x - vDist.x + 1.f);
		_pObj->SetPos(vObjPos);
	}

	m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::LEFT));
}

void CPlatform::RightCheck(CObj* _pObj)
{
	Vec2 vObjPos = _pObj->GetPos();

	Vec2 vDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
	Vec2 vLength = GetCollider()->GetScale() / 2.f;

	vLength += _pObj->GetCollider()->GetScale() / 2.f;
	if (vLength.x > vDist.x)
	{
		vObjPos.x += (vLength.x - vDist.x + 1.f);
		_pObj->SetPos(vObjPos);
	}

	m_mapPlatformStatus.insert(make_pair(_pObj->GetId(), EPLATFORM_STATUS::RIGHT));
}

void CPlatform::PushObj(CObj* _pObj)
{
	if (L"Gaibon" == _pObj->GetName())
		int a = 0;

	Vec2 vPos = _pObj->GetPos();
	Vec2 vObjPos = _pObj->GetCollider()->GetFinalPos();
	vObjPos.y += _pObj->GetCollider()->GetScale().y / 2.f;
	Vec2 vDist = Vec2(GetPos().x - vObjPos.x, GetPos().y - vObjPos.y);
	Vec2 vabDist = Vec2(fabsf(GetPos().x - vObjPos.x), fabsf(GetPos().y - vObjPos.y));
	Vec2 vLength = GetCollider()->GetScale() / 2.f;

	vLength += _pObj->GetCollider()->GetScale() / 2.f;
	
	if (0 < vDist.x)
	{
		if (vLength.x > vabDist.x)
		{
			vObjPos.x -= (vLength.x - vabDist.x);
			vObjPos.y = vPos.y;
			_pObj->SetPos(vObjPos);
		}
	}
	else if (0 > vDist.x)
	{
		if (vLength.x > vabDist.x)
		{
			vObjPos.x += (vLength.x - vabDist.x);
			vObjPos.y = vPos.y;
			_pObj->SetPos(vObjPos);
		}
	}
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
