#pragma once
#include "CObj.h"

class CTexture;

class CSpawnPoint :
    public CObj
{
private:
    ESPAWNABLE_OBJECT m_eOption;	// 스폰시킬 오브젝트
    CTexture* m_pTexture;

public:
    void SetSpawnObjectOption(ESPAWNABLE_OBJECT _eOption) { m_eOption = _eOption; }

public:
    CSpawnPoint();
    ~CSpawnPoint();

public:
    CLONE(CSpawnPoint);

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};


