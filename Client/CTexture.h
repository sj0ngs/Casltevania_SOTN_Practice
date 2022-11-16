#pragma once
#include "CRes.h"

struct tPixel
{
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;

    tPixel(BYTE _r, BYTE _g, BYTE _b)
        : r(_r), g(_g), b(_b), a(0)
    {
    }
};

class CTexture :
    public CRes
{
private:
    HBITMAP m_hBit;
    HDC m_hDC;
    
    BITMAP m_tBitMapInfo;

    void* m_pBit;

public:
    UINT GetWidth() const { return m_tBitMapInfo.bmWidth; }
    UINT GetHeight() const { return m_tBitMapInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }
    HBITMAP GetBit() { return m_hBit; }

    void Resize(UINT _iWidth, UINT _iHeight);

public:
    CTexture();
    ~CTexture();

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    void Create(UINT _iWidth, UINT _iHeight);

    void SetPixelColor(int _x, int _y, tPixel _pixel);
    tPixel GetPixelColor(int _x, int _y);
};

