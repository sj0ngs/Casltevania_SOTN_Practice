#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator(CObj* _pOwner)	:
	CComponent(_pOwner),
	m_pCurAnim(nullptr),
	m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Other) :
	CComponent(nullptr),
	m_pCurAnim(nullptr),
	m_bRepeat(_Other.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _Other.m_mapAnim.begin();
	for (; iter != _Other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->Reset();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}
	// 현재 애니메이션을 이름이 같은 애니메이션으로 지정
	if(nullptr != _Other.m_pCurAnim)
		Play(_Other.m_pCurAnim->GetName(), m_bRepeat);
}

CAnimator::~CAnimator()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin(),
		iterEnd = m_mapAnim.end();

	for (; iter != iterEnd; ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
}

void CAnimator::Tick()
{
}

void CAnimator::Final_Tick()
{
	if (nullptr == m_pCurAnim)
		return;

	if (m_pCurAnim->IsFinish() && m_bRepeat)
	{
		m_pCurAnim->Reset();
	}
	m_pCurAnim->Tick();
}

void CAnimator::Render(HDC _hDC)
{
	if (nullptr == m_pCurAnim)
		return;

	m_pCurAnim->Render(_hDC);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, 
								Vec2 _vSize, int _iMaxFrmCount, float _fDuration)
{
	// 애니메이션은 중복되서 만들어지면 안되므로 중복 확인
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	// 애니메이션이 소유자를 알 수 있도록,
	// 자신(애니메이터)를 넘겨준다
	pAnim = new CAnimation(this);
	// 인자로 받아온 값으로 새로운 애니메이션 생성
	pAnim->Init(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrmCount, _fDuration);
	// 완성된 애니메이션을 map 컨테이너에 담아준다
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

CAnimation* CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation(this);

	pAnim->Load(_strRelativePath);

	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));

	return pAnim;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	// 받아온 정보의 애니메이션이 존재하는지 확인
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"해당 Animation 없음", L"Animation 재생 오류", MB_OK);
		return;
	}

	// 현재 애니메이션을 찾은 애니메이션으로 지정한다
	m_pCurAnim = pAnim;

	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
}
