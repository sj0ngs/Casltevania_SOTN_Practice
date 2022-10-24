#include "pch.h"
#include "CBackGround.h"

#include "CResMgr.h"

#include "CTexture.h"

CBackGround::CBackGround()	:
	m_pBackGroundTex(nullptr),
	m_bIsForeGround(false)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Tick()
{

}

void CBackGround::Render(HDC _DC)
{
	if (nullptr == m_pBackGroundTex)
		return;

	Vec2 vPos = GetPos();

	if(m_bIsForeGround)
		vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	BitBlt(_DC,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)m_pBackGroundTex->GetWidth(), (int)m_pBackGroundTex->GetHeight(),
		m_pBackGroundTex->GetDC(),
		0, 0,
		SRCCOPY);

	CObj::Render(_DC);
}

void CBackGround::Save(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 텍스쳐 존재 여부
	bool bTex = m_pBackGroundTex;
	fwrite(&bTex, sizeof(bool), 1, _pFile);

	// 이미지 키 값
	wstring strKey = m_pBackGroundTex->GetKey();
	SaveWString(strKey, _pFile);

	// 이미지 경로 값
	wstring strRelativePath = m_pBackGroundTex->GetPath();
	SaveWString(strRelativePath, _pFile);

	// 포어그라운드인지 여부(카메라에 영향을 받을것인가 여부)
	fwrite(&m_bIsForeGround, sizeof(bool), 1, _pFile);
}

void CBackGround::Load(FILE* _pFile)
{
	// 자신의 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 텍스쳐 존재 여부
	bool bTex;
	fread(&bTex, sizeof(bool), 1, _pFile);

	if (bTex)
	{
		// 키값 경로 불러오기
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);

		m_pBackGroundTex = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// 포어그라운드인지 여부(카메라에 영향을 받을것인가 여부)
	fread(&m_bIsForeGround, sizeof(bool), 1, _pFile);

}
