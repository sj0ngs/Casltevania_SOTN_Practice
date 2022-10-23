#include "pch.h"
#include "CTile.h"

#include "CEngine.h"
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
	//if (-1 == m_iImgIdx || nullptr == m_pAtlas)
	//	return;

	//int iMaxCol = m_pAtlas->GetWidth() / TILE_SIZE;

	//int iCurCol = m_iImgIdx / iMaxCol;
	//int iCurRow = m_iImgIdx % iMaxCol;

	//BitBlt(_DC,
	//	(int)vPos.x, (int)vPos.y,
	//	TILE_SIZE, TILE_SIZE,
	//	m_pAtlas->GetDC(),
	//	iCurRow * TILE_SIZE,
	//	iCurCol * TILE_SIZE,
	//	SRCCOPY);

		// �浹ü�� �׸���
	HPEN hPen = nullptr;

	hPen = CEngine::GetInst()->GetPen(EPEN_TYPE::BLUE);

	HPEN hPrevPen = (HPEN)SelectObject(_DC, hPen);

	// DC �� ���� �Ұ� �귯���� ���� �����°͵�� ��ü�Ѵ�
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_DC, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Rectangle(_DC,
		(int)vPos.x,
		(int)vPos.y,
		(int)(vPos.x + TILE_SIZE),
		(int)(vPos.y + TILE_SIZE));

	// ���� �Ұ� �귯���� �������´�
	SelectObject(_DC, hPrevPen);
	SelectObject(_DC, hPrevBrush);

}

void CTile::Save(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű�� ����
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// ��� ����
		wstring strRelativePath = m_pAtlas->GetPath();
		SaveWString(strRelativePath, _pFile);
	}

	// �̹��� �ε��� ����
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű��, ��� �ҷ�����
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);

		// �ҷ��� ������ �ؽ�ó �ε�
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// �̹��� �ε��� ����
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
