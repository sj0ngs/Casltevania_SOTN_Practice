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
    bool                m_bStop;

public:
    CTexture* GetAltasTex() { return m_pAtlas; }
    // 프레임 데이터 넘겨주는 함수
    const tAnimFrm& GetCurFrm() const { return m_vecFrm[m_iCurFrm]; }   

public:
    CLONE(CAnimation);

public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

private:
    void Init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop,
        Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset);

    void Init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop,
        Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, int _iRow, Vec2 _vOffset);

public:
    void Tick();
    void Render(HDC _hDC);
 /*   void AlphaRender(HDC _hDC, float _fRatio);
    void HitRender(HDC _hDC);*/

public:
    bool IsFinish() { return m_bFinish; }
    void Reset() { m_bFinish = false; m_iCurFrm = 0; m_fAccTime = 0.f; }

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    int GetCurFrame() const { return m_iCurFrm; } 
    void SetCurFrame(int _CurFame);

private:
    void SwitchStop() { m_bStop = m_bStop ? false : true; }
    void PrevFrame();
    void NextFrame();
    vector<tAnimFrm>* GetAnimFrame() { return &m_vecFrm; }

    friend class CAnimator;
    friend class CAnimationEditor;
};

