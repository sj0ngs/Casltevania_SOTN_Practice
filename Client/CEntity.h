#pragma once

class CEntity
{
private:
	// id �� �����ϰ� ����� �ֱ� ���� ���������� �̿��ؼ� 
	// ��ü�� ���鶧���� ���� �ְ� ���� �����ش�
	static UINT g_iNextID;

private:
	// ��ü�� ���� �̸�, ����� �� �� ã�� ���ϰ� �ϱ� ���� �뵵
	wstring m_strName;

	// ��� �Ŵ����� �ƴ� ��ü�� ���� ������ id ���� ��ġ�� �ȵ�
	const UINT m_id;	

public:
	void SetName(const wstring& _Str) { m_strName = _Str; }
	const wstring& GetName() { return m_strName; }
	UINT GetId() { return m_id; }

	virtual CEntity* Clone() = 0;

public:
	CEntity();
	// ��ü�� ������ �����ΰ� �����ؼ� ���� ����� ��ü�� ���� �� �� �����Ƿ�
	// ���� �����ڸ� ���� ������༭ nextID�� ���� �����ټ� �ֵ��� �Ѵ�
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

