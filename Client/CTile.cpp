#include "pch.h"
#include "CTile.h"

#include "CCamera.h"
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

void CTile::SetImgIdx(int _iImgIdx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->GetWidth() / TILE_SIZE;
	int iRow = m_pAtlas->GetHeight() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	assert(iImgMaxCount > _iImgIdx);

	m_iImgIdx = _iImgIdx;
}