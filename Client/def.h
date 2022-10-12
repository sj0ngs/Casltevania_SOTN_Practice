#pragma once

// 싱글톤 클래스를 생성한다
#define SINGLE(type) public:\
					static type* GetInst()\
					{\
						static type Inst;\
						return &Inst;\
					}\
					private:\
						type();\
						~type();

#define DYNAMIC_DELETE(p) if(nullptr != p) delete p;

// DeltaTime을 가져온다
#define DELTATIME CTimeMgr::GetInst()->GetDeltaTime()

#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type)	virtual type* Clone() { assert(nullptr); return nullptr; }

#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define IS_TAP(key) CKeyMgr::GetInst()->GetKeyState(key) == EKEY_STATE::TAP
#define IS_PRESSED(key) CKeyMgr::GetInst()->GetKeyState(key) == EKEY_STATE::PRESSED
#define IS_RELEASED(key) CKeyMgr::GetInst()->GetKeyState(key) == EKEY_STATE::RELEASED
#define IS_NONE(key) CKeyMgr::GetInst()->GetKeyState(key) == EKEY_STATE::NONE

#define PI 3.14f
#define TILE_SIZE 64	

enum class ELEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	EDITOR,
	END
};

enum class EPEN_TYPE
{
	GREEN,
	RED,
	BLUE,

	END
};

enum class ELAYER
{
	BACKGROUND,
	TILE,
	DEFAULT,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	FORCE,
	PLATFORM,

	END = 16
};

enum class EEVENT_TYPE
{
	CREATE_OBJECT,	// wParam  : Object Address		lParam : Layer Type
	DELETE_OBJECT,	// wParam  : Object Address
	LEVEL_CHANGE	// wParam  : LEVEL_TYPE(Next Level Type)
};

enum class ECAMERA_EFFECT
{
	NONE,
	FADE_OUT,
	FADE_IN
};
