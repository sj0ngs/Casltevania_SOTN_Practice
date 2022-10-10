#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CTexture.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter, iterEnd = m_mapTex.end();
	for (iter = m_mapTex.begin(); iter != iterEnd; ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CRes* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
		return (CTexture*)pTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTexture = new CTexture;
	pTexture->Load(strFilePath);
	pTexture->SetKey(_strKey);
	pTexture->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
	
	return (CTexture*)pTexture;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
		return (CTexture*)pTexture;

	pTexture = new CTexture;
	pTexture->Create(_iWidth, _iHeight);
	pTexture->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));

	return pTexture;
}
