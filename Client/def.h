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
#define TILE_SIZE 32	

enum class ELEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	BOSS,
	EDITOR,
	ANIMATION,
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
	FOREGROUND,
	TILE,
	MAP_OBJECT,
	MONSTER,
	EFFECT,
	ITEM,
	PLAYER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	PLATFORM,
	LINE,
	PLAYER_START,
	SPAWN_POINT,
	TRIGGER,
	OBJECT,


	UI = 15,
	END = 32
};

enum class EEVENT_TYPE
{
	CREATE_OBJECT,		// wParam  : Object Address		lParam : Layer Type
	DELETE_OBJECT,		// wParam  : Object Address
	LEVEL_CHANGE,		// wParam  : LEVEL_TYPE(Next Level Type)
	CHANGE_AI_STATE		// wParam  : AI Address			lParam : State Type
};

enum class ECAMERA_EFFECT
{
	NONE,
	FADE_OUT,
	FADE_IN
};

enum class ESPAWNABLE_OBJECT
{
	// Monster
	BONE_SCIMITAR,
	AXE_ARMOR,
	SKELETON,
	BLOOD_SKELETON,
	SPITTLE_BONE,
	GAIBON,
	SLOGRA,

	// Map Object
	CANDLE,

	NONE
};

enum class ETRIGGER_TYPE
{
	LEVEL_CHANGE,

	NONE
};

enum class EPLAYER_STATE
{
	STAND,
	DUCK,
	AIR,
	HIT,
	
	NONE
};

enum class ESUB_WEAPON_TYPE
{
	DAGGER,
	AXE,
	BIBLE,
	NONE

	//WATCH,
	//HOLY_WATER
};
