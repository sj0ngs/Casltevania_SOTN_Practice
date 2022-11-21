#include "pch.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

#include "CAnimation.h"

CAnimator::CAnimator(CObj* _pOwner)	:
	CComponent(_pOwner),
	m_pCurAnim(nullptr),
	m_bRepeat(false),
	m_bCameraAfctd(true),
	m_eOpt(EANIM_OPT::NORMAL),
	m_fRatio(0.f),
	m_fDir(0.f)
{
}

CAnimator::CAnimator(const CAnimator& _Other) :
	CComponent(nullptr),
	m_pCurAnim(nullptr),
	m_bRepeat(_Other.m_bRepeat),
	m_bCameraAfctd(_Other.m_bCameraAfctd),
	m_eOpt(EANIM_OPT::NORMAL),
	m_fRatio(0.f),
	m_fDir(0.f)
{
	map<wstring, CAnimation*>::const_iterator iter = _Other.m_mapAnim.begin();
	for (; iter != _Other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->Reset();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}
	// ���� �ִϸ��̼��� �̸��� ���� �ִϸ��̼����� ����
	if(nullptr != _Other.m_pCurAnim)
		Play(_Other.m_pCurAnim->GetName(), m_bRepeat);
}

CAnimator::~CAnimator()
{
	ClearAnimation();
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

	//m_pCurAnim->Render(_hDC);

	switch (m_eOpt)
	{
	case EANIM_OPT::NORMAL:
		m_pCurAnim->Render(_hDC);
		break;
	case EANIM_OPT::ALPHA_BLEND:
	{
		m_fRatio += DELTATIME * m_fDir * 5;

		if (1.f <= m_fRatio)
		{
			m_fDir = -1.f;
			m_fRatio = 1.f;
		}
		else if (0.0 >= m_fRatio)
		{
			m_fDir = 1.f;
			m_fRatio = 0.0f;
		}

		m_pCurAnim->AlphaRender(_hDC, m_fRatio);
	}
		break;
	}
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, 
								Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset)
{
	// �ִϸ��̼��� �ߺ��Ǽ� ��������� �ȵǹǷ� �ߺ� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	// �ִϸ��̼��� �����ڸ� �� �� �ֵ���,
	// �ڽ�(�ִϸ�����)�� �Ѱ��ش�
	pAnim = new CAnimation(this);
	// ���ڷ� �޾ƿ� ������ ���ο� �ִϸ��̼� ����
	pAnim->Init(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrmCount, _fDuration, _vPadding, _vOffset);
	// �ϼ��� �ִϸ��̼��� map �����̳ʿ� ����ش�
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, int _iMaxFrmCount, float _fDuration, int _iRow, Vec2 _vPadding, Vec2 _vOffset)
{	// �ִϸ��̼��� �ߺ��Ǽ� ��������� �ȵǹǷ� �ߺ� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	assert(!pAnim);

	// �ִϸ��̼��� �����ڸ� �� �� �ֵ���,
	// �ڽ�(�ִϸ�����)�� �Ѱ��ش�
	pAnim = new CAnimation(this);
	// ���ڷ� �޾ƿ� ������ ���ο� �ִϸ��̼� ����
	pAnim->Init(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrmCount, _fDuration, _vPadding, _iRow, _vOffset);
	// �ϼ��� �ִϸ��̼��� map �����̳ʿ� ����ش�
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

bool CAnimator::IsAnimationFinish(const wstring& _strName)
{
	// �޾ƿ� ������ �ִϸ��̼��� �����ϴ��� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return false;
	}

	return pAnim->IsFinish();
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	// �޾ƿ� ������ �ִϸ��̼��� �����ϴ��� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}

	if (m_pCurAnim == pAnim)
		return;

	// ���� �ִϸ��̼��� ã�� �ִϸ��̼����� �����Ѵ�
	m_pCurAnim = pAnim;

	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
}

void CAnimator::Play(bool _bRepeat)
{
	assert(1 == m_mapAnim.size());

	Play(m_mapAnim.begin()->first, _bRepeat);
}

void CAnimator::Shift(const wstring& _strName, bool _bRepeat)
{
	// �޾ƿ� ������ �ִϸ��̼��� �����ϴ��� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}
	
	int iCurFrame = m_pCurAnim->GetCurFrame();
	// ���� �ִϸ��̼��� ã�� �ִϸ��̼����� �����Ѵ�
	m_pCurAnim = pAnim;

	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
	m_pCurAnim->SetCurFrame(++iCurFrame);
}

void CAnimator::Shift(const wstring& _strName, bool _bRepeat, int iFrame)
{
	// �޾ƿ� ������ �ִϸ��̼��� �����ϴ��� Ȯ��
	CAnimation* pAnim = FindAnimation(_strName);
	if (nullptr == pAnim)
	{
		MessageBox(nullptr, L"�ش� Animation ����", L"Animation ��� ����", MB_OK);
		return;
	}

	if (m_pCurAnim == pAnim)
		return;

	// ���� �ִϸ��̼��� ã�� �ִϸ��̼����� �����Ѵ�
	m_pCurAnim = pAnim;

	m_pCurAnim->Reset();
	m_bRepeat = _bRepeat;
	m_pCurAnim->SetCurFrame(iFrame);
}

void CAnimator::ClearAnimation()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin(),
		iterEnd = m_mapAnim.end();

	for (; iter != iterEnd; ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
}

CAnimation* CAnimator::GetFirstAnim()
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();

	return iter->second;
}