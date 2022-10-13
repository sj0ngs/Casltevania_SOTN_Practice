#pragma once
#include "CEntity.h"

class CTexture;
class CAnimator;

class CAnimation :
    public CEntity
{
private:
    CAnimator*          m_pAnimator;
    vector<tAnimFrm>    m_vecFrm;
    CTexture*           m_pAtlas;
    int                 m_iCurFrm;
    float               m_fAccTime;
    bool                m_bFinish;

public:
    CLONE(CAnimation);

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

private:
    void Init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop,
        Vec2 _vSize, int _iMaxFrmCount, float _fDuration);

public:
    void Tick();
    void Render(HDC _hDC);

public:
    bool IsFinish() { return m_bFinish; }
    void Reset() { m_bFinish = false; m_iCurFrm = 0; m_fAccTime = 0.f; }

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    friend class CAnimator;
};

