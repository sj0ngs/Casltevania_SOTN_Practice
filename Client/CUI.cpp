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

// �ڽ� UI�� �θ� UI�� ���� ����� �����ؿ;� �ϹǷ� ����� ���� ���� ������ �ۼ�
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
	// ������ �ڽ� UI�� ���綰�� �ڽ��� �ڽ� UI ���Ϳ� �־��ش�
	for (size_t i = 0; i < _Other.m_vecChildUI.size(); i++)
	{
		// AddChildUI �Լ����� �ڵ����� �θ� �ڽ����� �������ش�
		AddChildUI(_Other.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	// �ڽ� UI ���;ȿ� ��� UI�� �������� ���ش�
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		delete m_vecChildUI[i];
	}
}

void CUI::Tick()
{
	// ��ġ ����
	// �ڽ��� �ֻ��� �θ� UI�ϼ��� ������ ���� ��ġ�� ���� ��ġ�� ����ش�
	m_vFinalPos = GetPos();
	// �θ� �ִٸ� �ڽ��� �ֻ��� �θ�UI�� �ƴѰ��̴�
	if (m_pParentUI)
	{
		// �ڽ��� ��ġ�� ������ ������ ����Ѵ�
		m_vFinalPos += m_pParentUI->GetFinalPos();
	}

	if (m_bMouseAfctd)
	{
		// ���콺 �� üũ
		MouseOnCheck();
	}
		
	// �ڱ� �ڽĵ��� Tick�� ���� �����ش�
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Tick();
	}
}

void CUI::Render(HDC _DC)
{
	HPEN hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::GREEN);
	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	// ī�޶� ������ ������(���� HP ��) ���� ����� ��ȯ
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

	// ���� �Ұ� �귯���� �������´�
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

	// ���̵� �ؽ����� �ʺ�� ���̷� �ڽ��� �������� �����Ѵ�
	if (nullptr != _pTex)
	{
		Vec2 vScale = Vec2((float)m_pIdleTex->GetWidth(), (float)m_pIdleTex->GetHeight());
		SetScale(vScale);
	}
}

// ���콺 �����Ͱ� �ڽ� ���� �ö�� �ִ��� üũ�Ѵ�
void CUI::MouseOnCheck()
{
	Vec2 vPos = GetFinalPos();
	// ���콺�� ������ �޴´ٸ� ������� �����´�
	if (m_bCmrAfctd)
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	Vec2 vScale = GetScale();
	Vec2 vMousePos = MOUSE_POS;

	// ���콺�� UI�� �����ȿ� �ִ�
	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
		m_bMouseOn = true;
	else
		m_bMouseOn = false;
}

