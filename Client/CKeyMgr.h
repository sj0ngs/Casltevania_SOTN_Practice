#pragma once

enum class EKEY : UINT8
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	Q,
	W,
	E,
	R,

	A,
	S,
	D,
	F,

	key0,
	key1,
	key2,
	key3,
	key4,
	key5,
	key6,
	key7,
	key8,
	key9,

	END
};

enum class EKEY_STATE : UINT8
{
	TAP,
	PRESSED,
	RELEASED,
	NONE
};

struct tKeyInfo
{
	EKEY		Key;
	EKEY_STATE	State;
	bool		bPrev;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
	
private:
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vMousePos;

public:
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	void Init();
	void Tick();

public:
	EKEY_STATE GetKeyState(EKEY _Key) { return m_vecKey[(UINT)_Key].State; }
	bool IsNoEnter();
};

