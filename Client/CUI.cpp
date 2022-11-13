#include "pch.h"
#include "CUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CTexture.h"

CUI::CUI()	:
	m_pParentUI(nullptr),
	m_pIdleTex(nullptr),
	m_vFinalPos{},
	m_bMouseAfctd(false),
	m_bLbtnDown(false),
	m_bMouseOn(false),
	m_bCmrAfctd(false)
{
}

// 자식 UI나 부모 UI를 깊은 복사로 복사해와야 하므로 사용자 지정 복사 생성자 작성
CUI::CUI(const CUI& _Other)		:
	CObj(_Other),
	m_pParentUI(nullptr),
	m_pIdleTex(_Other.m_pIdleTex),
	m_vFinalPos{},
	m_bMouseAfctd(_Other.m_bMouseAfctd),
	m_bLbtnDown(false),
	m_bMouseOn(false),
	m_bCmrAfctd(_Other.m_bCmrAfctd)
{
	// 원본의 자식 UI를 복사떠서 자신의 자식 UI 벡터에 넣어준다
	for (size_t i = 0; i < _Other.m_vecChildUI.size(); i++)
	{
		// AddChildUI 함수에서 자동으로 부모를 자신으로 지정해준다
		AddChildUI(_Other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	// 자식 UI 벡터안에 모든 UI를 동적해제 해준다
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::Tick()
{
	// 위치 갱신
	// 자신이 최상위 부모 UI일수도 있으니 현재 위치를 최종 위치로 잡아준다
	m_vFinalPos = GetPos();
	// 부모가 있다면 자신이 최상위 부모UI가 아닌것이다
	if (m_pParentUI)
	{
		// 자신의 위치를 오프셋 값으로 사용한다
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	if (m_bMouseAfctd)
	{
		// 마우스 온 체크
		MouseOnCheck();
	}
		
	// 자기 자식들의 Tick도 전부 돌려준다
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Tick();
	}
}

void CUI::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);
	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC 의 기존 팬과 브러쉬를 새로 가져온것들로 대체한다
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	// 카메라에 영향을 받으면(몬스터 HP 등) 랜더 포즈로 변환
	Vec2 vPos = GetFinalPos();
	if (m_bCmrAfctd)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	Vec2 vScale = GetScale();

	Rectangle(_DC, 
		(int)vPos.x, 
		(int)vPos.y, 
		(int)(vPos.x + vScale.x),
		(int)(vPos.y + vScale.y));

	// 기존 팬과 브러쉬로 돌려놓는다
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);

	Render_ChildUI(_DC);
}

void CUI::Render_ChildUI(HDC _DC)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Render(_DC);
	}
}

void CUI::SetIdleTex(CTexture* _pTex)
{
	m_pIdleTex = _pTex;

	// 아이들 텍스쳐의 너비와 높이로 자신의 스케일을 지정한다
	if (nullptr != _pTex)
	{
		Vec2 vScale = Vec2((float)m_pIdleTex->GetWidth(), (float)m_pIdleTex->GetHeight());
		SetScale(vScale);
	}
}

// 마우스 포인터가 자신 위에 올라와 있는지 체크한다
void CUI::MouseOnCheck()
{
	Vec2 vPos = GetFinalPos();
	// 마우스에 영향을 받는다면 랜더포즈를 가져온다
	if (m_bCmrAfctd)
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;

	// 마우스가 UI의 영역안에 있다
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
		m_bMouseOn = true;
	else
		m_bMouseOn = false;
}

