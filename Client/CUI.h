#pragma once
#include "CObj.h"

class CTexture;

class CUI :
    public CObj
{
private:
    vector<CUI*>    m_vecChildUI;   // �ڽ� ui 
    CUI*            m_pParentUI;    // �θ� ui
    Vec2            m_vFinalPos;    // �ֻ��� �θ� ui ���� �������� �༭ ����� �ڽ��� ���� ��ġ

    CTexture*       m_pIdleTex;     // �Ϲ� �ؽ���
 
    bool            m_bMouseAfctd;  // ���콺 �Է��� �޴��� ����
    bool            m_bLbtnDown;    // �¹�ư�� ���������� ����
    bool            m_bMouseOn;     // ���콺�� �ڽſ� �ö�� �ִ��� ����
    bool            m_bCmrAfctd;    // ī�޶� ������ �޴��� ����

public:
    void SetIdleTex(CTexture* _pTex);
    CTexture* GetIdleTex() const { return m_pIdleTex; }
    void SetFinalPos(Vec2 _vPos) { m_vFinalPos = _vPos; }
    Vec2 GetFinalPos() const { return m_vFinalPos; }
    void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    bool IsCameraAffected() const { return m_bCmrAfctd; }
    bool IsMouseOn() const { return m_bMouseOn; }
    bool IsLbtnDown() const { return m_bLbtnDown; }

    CUI* GetParentUI() const { return m_pParentUI; }
    const vector<CUI*>& GetChildUI()  { return m_vecChildUI; }

    void AddChildUI(CUI* _pChildUI)
    {
        // �ڽ��� �θ�� �������ش�
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }

public:
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _Other);
    ~CUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

    void Render_ChildUI(HDC _DC);

    // UI �̺�Ʈ �Լ�
public:
    // �������̵� �� ��� �θ��Լ� ȣ���� ��
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};

private:
    void MouseOnCheck();

    friend class CUIMgr;
};

