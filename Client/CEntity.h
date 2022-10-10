#pragma once

class CEntity
{
private:
	// id 를 고유하게 만들어 주기 위해 정적변수를 이용해서 
	// 객체를 만들때마다 값을 넣고 증가 시켜준다
	static UINT g_iNextID;

private:
	// 객체가 가질 이름, 디버그 할 때 찾기 편하게 하기 위한 용도
	wstring m_strName;

	// 모든 매니저가 아닌 객체가 가질 고유한 id 절대 겹치면 안됨
	const UINT m_id;	

public:
	void SetName(const wstring& _Str) { m_strName = _Str; }
	const wstring& GetName() { return m_strName; }
	UINT GetId() { return m_id; }

	virtual CEntity* Clone() = 0;

public:
	CEntity();
	// 객체를 원본을 만들어두고 복사해서 실제 사용할 객체를 생성 할 수 있으므로
	// 복사 생성자를 따로 만들어줘서 nextID를 증가 시켜줄수 있도록 한다
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

