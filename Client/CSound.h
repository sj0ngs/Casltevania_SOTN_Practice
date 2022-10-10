#pragma once
#include "CRes.h"
class CSound :
    public CRes
{
private:
    virtual int Load(const wstring& _strFilePath) override;
};

