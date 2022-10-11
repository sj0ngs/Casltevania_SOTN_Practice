#include "pch.h"
#include "CTile.h"

#include "CCamera.h"
#include "CResMgr.h"

#include "CTexture.h"

CTile::CTile()	:
	m_pAtlas(nullptr),
	m_iImgIdx(-1)
{
}

CTile::~CTile()
{
}

void CTile::Tick()
{
}

void CTile::Render(HDC _DC)
{
	if (-1 == m_iImgIdx || nullptr == m_pAtlas)
		return;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	int iMaxCol = m_pAtlas->GetWidth() / TILE_SIZE;

	int iCurCol = m_iImgIdx / iMaxCol;
	int iCurRow = m_iImgIdx % iMaxCol;

	BitBlt(_DC,
		(int)vPos.x, (int)vPos.y,
		TILE_SIZE, TILE_SIZE,
		m_pAtlas->GetDC(),
		iCurRow * TILE_SIZE,
		iCurCol * TILE_SIZE,
		SRCCOPY);

	//Rectangle(_DC, 
	//	(int)vPos.x, 
	//	(int)vPos.y, 
	//	(int)(vPos.x + TILE_SIZE), 
	//	(int)(vPos.y + TILE_SIZE));
}

void CTile::Save(FILE* _pFile)
{
	// 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 아틀라스 이미지 정보
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값 저장
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// 경로 저장
		wstring strRelativePath = m_pAtlas->GetPath();
		SaveWString(strRelativePath, _pFile);
	}

	// 이미지 인덱스 정보
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	// 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 아틀라스 이미지 정보
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값, 경로 불러오기
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);

		// 불러온 정보로 텍스처 로딩
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// 이미지 인덱스 정보
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::SetImgIdx(int _iImgIdx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->GetWidth() / TILE_SIZE;
	int iRow = m_pAtlas->GetHeight() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	assert(iImgMaxCount > _iImgIdx);

	m_iImgIdx = _iImgIdx;
}

void CTile::AddImgIdx()
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->GetWidth() / TILE_SIZE;
	int iRow = m_pAtlas->GetHeight() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	++m_iImgIdx;

	if (iImgMaxCount <= m_iImgIdx)
		m_iImgIdx = 0;
}
