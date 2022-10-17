#pragma once

class CObj;
class CLine;

union LineCollisionID
{
	struct
	{
		UINT ObjectID;
		UINT LineID;
	};

	UINT_PTR id;
};

class CLineCollisionMgr
{
	SINGLE(CLineCollisionMgr);

private:
	WORD m_CollisionProfile;
	map<UINT_PTR, bool> m_mapPrevInfo;

public:
	void Tick();

public:
	void CollisionSet(ELAYER _eLayer);
	void clear();

private:
	void CollisionLayerToLine(ELAYER _Layer);
	bool CollisionObjToLine(CObj* _Obj, CLine* _Line);
	bool UpLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint);
	bool DownLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint);
	bool LeftLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint);
	bool RightLineCheck(CObj* _Obj, CLine* _Line, Vec2 _vMeetPoint);
};

