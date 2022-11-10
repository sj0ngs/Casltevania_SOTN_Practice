#include "pch.h"
#include "CLevelChangeTrigger.h"

#include "CLevelMgr.h"
#include "CObjMgr.h"

#include "CLevel.h"

#include "CCollider.h"

CLevelChangeTrigger::CLevelChangeTrigger()	:
	m_eLevelChangeType(ELEVEL_TYPE::END),
	m_iStartPointIdx(0)
{
	SetTriggerType(ETRIGGER_TYPE::LEVEL_CHANGE);
}

CLevelChangeTrigger::~CLevelChangeTrigger()
{
}

void CLevelChangeTrigger::Render(HDC _DC)
{
	CTrigger::Render(_DC);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	wstring strName = L"LevelChange";
	TextOut(_DC, (int)vPos.x, (int)vPos.y - 30, strName.c_str(), (int)strName.length());

	switch (m_eLevelChangeType)
	{
	case ELEVEL_TYPE::START:
		strName = L"Start";
		break;
	case ELEVEL_TYPE::STAGE_01:
		strName = L"Stage 01";
		break;
	case ELEVEL_TYPE::STAGE_02:
		strName = L"Stage 02";
		break;
	case ELEVEL_TYPE::STAGE_03:
		strName = L"Stage 03";
		break;
	case ELEVEL_TYPE::BOSS:
		strName = L"Boss";
		break;
	case ELEVEL_TYPE::EDITOR:
		strName = L"Editor";
		break;
	case ELEVEL_TYPE::END:
		strName = L"Error";
		break;
	}
	TextOut(_DC, (int)vPos.x, (int)vPos.y - 15, strName.c_str(), (int)strName.length());

	strName = std::to_wstring(m_iStartPointIdx);
	TextOut(_DC, (int)vPos.x, (int)vPos.y, strName.c_str(), (int)strName.length());
}

void CLevelChangeTrigger::BeginOverlap(CCollider* _pOther)
{
	ChangeLevel(m_eLevelChangeType);

	CLevel* pLevel = CLevelMgr::GetInst()->GetLevel(m_eLevelChangeType);
	pLevel->SetStartPointIdx(m_iStartPointIdx);
	
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = pCurLevel->GetPlayer();
	CObjMgr::GetInst()->UpDatePlayer(pPlayer);
}

void CLevelChangeTrigger::OnOverlap(CCollider* _pOther)
{
}

void CLevelChangeTrigger::EndOverlap(CCollider* _pOther)
{
}

void CLevelChangeTrigger::Save(FILE* _pFile)
{
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	Vec2 vScale = GetCollider()->GetScale();
	fwrite(&vScale, sizeof(Vec2), 1, _pFile);

	fwrite(&m_eLevelChangeType, sizeof(ELEVEL_TYPE), 1, _pFile);

	fwrite(&m_iStartPointIdx, sizeof(UINT), 1, _pFile);
}

void CLevelChangeTrigger::Load(FILE* _pFile)
{
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	Vec2 vScale;
	fread(&vScale, sizeof(Vec2), 1, _pFile);
	GetCollider()->SetScale(vScale);

	fread(&m_eLevelChangeType, sizeof(ELEVEL_TYPE), 1, _pFile);

	fread(&m_iStartPointIdx, sizeof(UINT), 1, _pFile);
}

