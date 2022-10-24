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
	// �ڽ��� ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// �ؽ��� ���� ����
	bool bTex = m_pBackGroundTex;
	fwrite(&bTex, sizeof(bool), 1, _pFile);

	// �̹��� Ű ��
	wstring strKey = m_pBackGroundTex->GetKey();
	SaveWString(strKey, _pFile);

	// �̹��� ��� ��
	wstring strRelativePath = m_pBackGroundTex->GetPath();
	SaveWString(strRelativePath, _pFile);

	// ����׶������� ����(ī�޶� ������ �������ΰ� ����)
	fwrite(&m_bIsForeGround, sizeof(bool), 1, _pFile);
}

void CBackGround::Load(FILE* _pFile)
{
	// �ڽ��� ��ġ
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// �ؽ��� ���� ����
	bool bTex;
	fread(&bTex, sizeof(bool), 1, _pFile);

	if (bTex)
	{
		// Ű�� ��� �ҷ�����
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);

		m_pBackGroundTex = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// ����׶������� ����(ī�޶� ������ �������ΰ� ����)
	fread(&m_bIsForeGround, sizeof(bool), 1, _pFile);

}
