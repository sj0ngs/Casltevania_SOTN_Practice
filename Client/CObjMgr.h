#pragma once

class CObj;
class CPlayer;

class CObjMgr
{
	SINGLE(CObjMgr);

private:
	map<wstring, CObj*> m_mapObj;

public:
	CObj* FindObj(wstring _strName);
	void UpDatePlayer(CPlayer* _pPlayer);

public:
	void Init();
};

