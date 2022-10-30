#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CAnimator.h"

#include "CObj.h"
#include "CTexture.h"


CAnimation::CAnimation(CAnimator* _pAnimator)	:
	m_pAnimator(_pAnimator),
	m_pAtlas(nullptr),
	m_iCurFrm(0),
	m_fAccTime(0.f),
	m_bFinish(false),
	m_bStop(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, 
					Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset)
{
	SetName(_strName);	// 이름
	m_pAtlas = _pAtlas;	// 아틀라스 이미지
	
	for (int i = 0; i < _iMaxFrmCount; i++)
	{
		tAnimFrm frm = {};
		frm.vLeftTop = Vec2(_vLeftTop.x + (float)i * (_vSize.x + _vPadding.x), _vLeftTop.y + _vPadding.y);
		frm.vSize = _vSize;
		frm.fDuration = _fDuration;
		frm.vOffset = _vOffset;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Tick()
{
	if (m_bFinish || m_bStop)
		return;

	m_fAccTime += DELTATIME;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;
		m_fAccTime = 0.f;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = (int)(m_vecFrm.size() - 1);
			m_bFinish = true;
		}
	}
}

void CAnimation::Render(HDC _hDC)
{
	CObj* pOwnerObj = m_pAnimator->GetOwner();
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(pOwnerObj->GetPos());

	tAnimFrm frm = m_vecFrm[m_iCurFrm];

	float X = fabsf(frm.vSize.x);
	TransparentBlt(_hDC, 
		(int)(vPos.x - X / 2.f + frm.vOffset.x),
		(int)(vPos.y - frm.vSize.y / 2.f + frm.vOffset.y),
		(int)(X), (int)(frm.vSize.y),
		m_pAtlas->GetDC(),
		(int)(frm.vLeftTop.x), (int)(frm.vLeftTop.y),
		(int)(X), (int)(frm.vSize.y),
		RGB(255, 0, 255));
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNo = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Save 실패, Error Number = %d", iErrNo);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	fwprintf_s(pFile, L"\n");
	// 애니메이션 이름 저장
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, GetName().c_str());
	fwprintf_s(pFile, L"\n\n");
	
	// 키값 저장
	fwprintf_s(pFile, L"[ATLAS_KEY]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 상대 경로 저장
	fwprintf_s(pFile, L"[ATLAS_PATH]\n");
	fwprintf_s(pFile, m_pAtlas->GetPath().c_str());
	fwprintf_s(pFile, L"\n\n");

	// 프레임 정보 저장
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	wchar_t szNum[50] = {};
	size_t iFrmCount = m_vecFrm.size();
	_itow_s((int)iFrmCount, szNum, 50, 10);
	fwprintf_s(pFile, szNum);
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < iFrmCount; i++)
	{
		fwprintf_s(pFile, L"[%zd_FRAME]\n", i);

		// LEFT_TOP
		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		// SIZE
		fwprintf_s(pFile, L"[SIZE]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		// OFFSET
		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%.1f %.1f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		// DURATION
		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%.5f\n", m_vecFrm[i].fDuration);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNo = _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"Animation Load 실패, Error Number = %d", iErrNo);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
		return;
	}

	wstring strAtlasKey;
	wstring strAtlasPath;
	size_t iFrmCount = 0;

	while (true)
	{
		wchar_t szBuffer[256] = {};
		fwscanf_s(pFile, L"%s", szBuffer, 256);

		if (!wcscmp(szBuffer, L"[ANIMATION_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			SetName(szBuffer);
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_KEY]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasKey = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[ATLAS_PATH]"))
		{
			fwscanf_s(pFile, L"%s", szBuffer, 256);
			strAtlasPath = szBuffer;
		}
		else if (!wcscmp(szBuffer, L"[FRAME_COUNT]"))
		{
			fwscanf_s(pFile, L"%zd", &iFrmCount);

			for (size_t i = 0; i < iFrmCount; i++)
			{
				tAnimFrm frm = {};
				while (true)
				{
					wchar_t szBuffer[256] = {};
					fwscanf_s(pFile, L"%s", szBuffer, 256);

					if (!wcscmp(szBuffer, L"[LEFT_TOP]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);
					}
					else if (!wcscmp(szBuffer, L"[SIZE]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
					}
					else if (!wcscmp(szBuffer, L"[OFFSET]"))
					{
						fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
					}
					else if (!wcscmp(szBuffer, L"[DURATION]"))
					{
						fwscanf_s(pFile, L"%f", &frm.fDuration);
						break;
					}
				}
				m_vecFrm.push_back(frm);
			}
			break;
		}
	}

	// 불러온 정보로 아틀라스 텍스쳐 생성해주기
	m_pAtlas = CResMgr::GetInst()->LoadTexture(strAtlasKey, strAtlasPath);

	fclose(pFile);
}

void CAnimation::PrevFrame()
{
	--m_iCurFrm;
	if (0 > m_iCurFrm)
		m_iCurFrm = (int)m_vecFrm.size() - 1;
}

void CAnimation::NextFrame()
{
	++m_iCurFrm;
	if (m_vecFrm.size() - 1 < m_iCurFrm)
		m_iCurFrm = 0;
}

void CAnimation::SetCurFrame(int _CurFame)
{
	m_iCurFrm = _CurFame;
	if (m_vecFrm.size() - 1 < m_iCurFrm)
		m_iCurFrm = (int)m_vecFrm.size() - 1;
}
