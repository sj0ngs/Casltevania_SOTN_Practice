#pragma once
#include "CComponent.h"

//enum class EANIM_OPT
//{
//    NORMAL,
//    ALPHA_BLEND,
//    HIT
//}; 

class CObj;
class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_pCurAnim;
    bool                        m_bRepeat;

    bool                        m_bCameraAfctd;

    //EANIM_OPT                   m_eOpt;   

    //float                       m_fRatio;
    //float                       m_fDir;

public:
    bool IsCameraAffected() const { return m_bCameraAfctd; }
    void SetCameraAffected(bool _bCameraAfctd) { m_bCameraAfctd = _bCameraAfctd; }

    //void SetAnimOpt(EANIM_OPT _eOpt) { m_eOpt = _eOpt; }
    //EANIM_OPT GetAnimOpt() const { return m_eOpt; }

public:
    CLONE(CAnimator);

public:
    CAnimator(CObj* _pOwner);
    CAnimator(const CAnimator& _Other);
    ~CAnimator();

public:
    virtual void Tick() override;
    virtual void Final_Tick()   override;
    virtual void Render(HDC _hDC)   override;

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, 
                         Vec2 _vSize, int _iMaxFrmCount, float _fDuration, 
                         Vec2 _vPadding = Vec2(0.f, 0.f), Vec2 _vOffset = Vec2(0.f, 0.f));
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);
    bool IsAnimationFinish(const wstring& _strName);
    CAnimation* GetCurAnimation() { return m_pCurAnim; }

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Play(bool _bRepeat);
    void Shift(const wstring& _strName, bool _bRepeat);
    void Shift(const wstring& _strName, bool _bRepeat, int iFrame);
    void ClearAnimation();

private:
    CAnimation* GetFirstAnim();
    void SetCurAnim(CAnimation* _pAnim) { m_pCurAnim = _pAnim; }
    void SwitchRepeat() { m_bRepeat = m_bRepeat ? false : true; }

    friend class CAnimationEditor;
    friend class CEventMgr;
};

