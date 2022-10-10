#pragma once
#include "CComponent.h"

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

public:
    CLONE(CAnimator);

public:
    CAnimator(CObj* _pOwner);
    CAnimator(const CAnimator& _Other);
    ~CAnimator();

public:
    virtual void Tick() override;
    virtual void Render(HDC _hDC)   override;

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, 
                         Vec2 _vSize, int _iMaxFrmCount, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);

public:
    void Play(const wstring& _strName, bool _bRepeat);
};

