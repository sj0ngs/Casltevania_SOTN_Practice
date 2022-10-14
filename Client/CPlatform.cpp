#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"

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
	m_vRightDown{}
{
	CreateCollider();

	GetCollider()->SetScale(Vec2(1000.f, 100.f));
}

CPlatform::~CPlatform()
{
}

void CPlatform::BeginOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());

	if (nullptr == pPlayer)
		return;

	SetPoint();

	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vPlayerPrevPos = pPlayer->GetPrevPos();
	
	Vec2 vDir = vPlayerPos - vPlayerPrevPos;

	// 플레이어가 추락 중일 때
	if (0.f < vDir.y)
	{
		// 윗변에 교점이 생겼다면 종료
		if (UpCheck(pPlayer))
			return;

		// 왼쪽에서 접근했을 때
		if (0.f < vDir.x)
		{
			LeftCheck(pPlayer);
			return;
		}
		// 오른쪽에서 접근했을 때
		if (0.f > vDir.x)
		{
			RightCheck(pPlayer);
			return;
		}
	}
	// 상승중일 때 
	else if(0.f > vDir.y)
	{
		// 아래변에 교점이 생겼다면 종료
		if (DownCheck(pPlayer))
			return;

		// 왼쪽에서 접근했을 때
		if (0.f < vDir.x)
		{
			LeftCheck(pPlayer);
			return;
		}
		// 오른쪽에서 접근했을 때
		if (0.f > vDir.x)
		{
			RightCheck(pPlayer);
			return;
		}
	}
	// 벽에 부딪혔을때
	else if(0.f == vDir.y)
	{
		// 왼쪽에서 접근했을 때
		if (0.f < vDir.x)
		{
			LeftCheck(pPlayer);
			return;
		}
		// 오른쪽에서 접근했을 때
		if (0.f > vDir.x)
		{
			RightCheck(pPlayer);
			return;
		}
	}

	//if (0.f < fDir)
	//{
	//	pPlayer->GetRigidBody()->SetGround(true);

	//	float fDist = GetPos().y - vPlayerPos.y;
	//	float fLength = (GetCollider()->GetScale().y + pPlayer->GetCollider()->GetScale().y) / 2.f;

	//	if (fLength > fDist)
	//	{
	//		vPlayerPos.y -= (fLength - fDist);
	//		pPlayer->SetPos(vPlayerPos);
	//	}
	//}
}

void CPlatform::OnOverlap(CCollider* _pOther)
{
}

void CPlatform::EndOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());

	if (nullptr == pPlayer)
		return;

	map<UINT, EPLATFORM_STATUS>::iterator iter = m_mapPlatformStatus.find(pPlayer->GetId());

	if (iter == m_mapPlatformStatus.end())
		return;

	switch (iter->second)
	{
	case EPLATFORM_STATUS::UP:
	{
		pPlayer->GetRigidBody()->OffGround();
	}
		break;
	case EPLATFORM_STATUS::LEFT:
	{
		int iMoveState = pPlayer->GetMoveState();
		iMoveState ^= RIGHT_BLOCK;
		pPlayer->SetMoveState(iMoveState);
	}
		break;
	case EPLATFORM_STATUS::RIGHT:
	{
		int iMoveState = pPlayer->GetMoveState();
		iMoveState ^= LEFT_BLOCK;
		pPlayer->SetMoveState(iMoveState);
	}
		break;
	case EPLATFORM_STATUS::DOWN:
	{
		int iMoveState = pPlayer->GetMoveState();
		iMoveState ^= UP_BLOCK;
		pPlayer->SetMoveState(iMoveState);
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

bool CPlatform::UpCheck(CPlayer* _pPlayer)
{
	m_UpLine = tLine(m_vLeftTop, m_vRightTop);

	Vec2 vPlayerPos = _pPlayer->GetPos();
	Vec2 vPlayerPrevPos = _pPlayer->GetPrevPos();
	Vec2 vPlayerScale = _pPlayer->GetCollider()->GetScale();
	vPlayerPos.y += vPlayerScale.y / 2.f;
	vPlayerPrevPos.y += vPlayerScale.y / 2.f;

	tLine tPlayerLine = tLine(vPlayerPos, vPlayerPrevPos);

	Vec2 vUPMeetPoint = m_UpLine.MeetPoint(tPlayerLine);

	if ((m_vLeftTop.x - vPlayerScale.x / 2.f) <= vUPMeetPoint.x
		&& (m_vRightTop.x + vPlayerScale.x / 2.f) >= vUPMeetPoint.x)
	{
		_pPlayer->GetRigidBody()->OnGround();
		_pPlayer->ResetJump();
		m_mapPlatformStatus.insert(make_pair(_pPlayer->GetId(), EPLATFORM_STATUS::UP));

		float fDist = fabsf(GetPos().y - vPlayerPos.y);
		float fLength = GetCollider()->GetScale().y / 2.f;

		if (fLength > fDist)
		{
			vPlayerPos.y -= vPlayerScale.y / 2.f;
			vPlayerPos.y -= (fLength - fDist);
			_pPlayer->SetPos(vPlayerPos);
		}
		return true;
	}

	return false;
}

bool CPlatform::DownCheck(CPlayer* _pPlayer)
{
	m_DownLine = tLine(m_vLeftDown, m_vRightDown);

	Vec2 vPlayerScale = _pPlayer->GetCollider()->GetScale();
	Vec2 vPlayerPos = _pPlayer->GetPos();
	Vec2 vPlayerPrevPos = _pPlayer->GetPrevPos();
	vPlayerPos.y -= vPlayerScale.y / 2.f;
	vPlayerPrevPos.y -= vPlayerScale.y / 2.f;

	// 플레이어의 이동 벡터를 연장한 직선을 만든다
	tLine tPlayerLine = tLine(vPlayerPos, vPlayerPrevPos);

	Vec2  vDownMeetPoint = m_DownLine.MeetPoint(tPlayerLine);

	if ((m_vLeftDown.x - vPlayerScale.x / 2) <= vDownMeetPoint.x
		&& (m_vRightDown.x + vPlayerScale.x / 2) >= vDownMeetPoint.x)
	{
		float fDist = fabsf(GetPos().y - vPlayerPos.y);
		float fLength = GetCollider()->GetScale().y / 2.f;

		int iMoveState = _pPlayer->GetMoveState();
		iMoveState |= UP_BLOCK;
		_pPlayer->SetMoveState(iMoveState);

		m_mapPlatformStatus.insert(make_pair(_pPlayer->GetId(), EPLATFORM_STATUS::DOWN));

		if (fLength > fDist)
		{
			vPlayerPos.y += vPlayerScale.y / 2.f;
			vPlayerPos.y += (fLength - fDist);
			_pPlayer->SetPos(vPlayerPos);
		}
		return true;
	}
	return false;
}

void CPlatform::LeftCheck(CPlayer* _pPlayer)
{
	Vec2 vPlayerScale = _pPlayer->GetCollider()->GetScale();
	Vec2 vPlayerPos = _pPlayer->GetPos();

	float fDist = fabsf(GetPos().x - vPlayerPos.x);
	float fLength = (GetCollider()->GetScale().x + vPlayerScale.x) / 2.f;

	int iMoveState = _pPlayer->GetMoveState();
	iMoveState |= RIGHT_BLOCK;
	_pPlayer->SetMoveState(iMoveState);
	
	m_mapPlatformStatus.insert(make_pair(_pPlayer->GetId(), EPLATFORM_STATUS::LEFT));

	if (fLength > fDist)
	{
		vPlayerPos.x -= (fLength - fDist);
		_pPlayer->SetPos(vPlayerPos);
	}
}

void CPlatform::RightCheck(CPlayer* _pPlayer)
{
	Vec2 vPlayerScale = _pPlayer->GetCollider()->GetScale();
	Vec2 vPlayerPos = _pPlayer->GetPos();

	float fDist = fabsf(GetPos().x - vPlayerPos.x);
	float fLength = (GetCollider()->GetScale().x + vPlayerScale.x) / 2.f;

	int iMoveState = _pPlayer->GetMoveState();
	iMoveState |= LEFT_BLOCK;
	_pPlayer->SetMoveState(iMoveState);

	m_mapPlatformStatus.insert(make_pair(_pPlayer->GetId(), EPLATFORM_STATUS::RIGHT));

	if (fLength > fDist)
	{
		vPlayerPos.x += (fLength - fDist);
		_pPlayer->SetPos(vPlayerPos);
	}
}
