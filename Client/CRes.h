#pragma once
#include "CEntity.h"
class CRes :
    public CEntity
{
private:
    wstring m_strKey;           // 이름
    wstring m_strRelativePath;  // 경로

public:
    const wstring GetKey() { return m_strKey; }
    const wstring GetPath() { return m_strRelativePath; }

private:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }


public:
    CLONE_DEACTIVATE(CRes);

public:
    CRes();
    virtual ~CRes();

protected:
    virtual int Load(const wstring& _strFilePath) = 0;

    friend class CResMgr;
};

