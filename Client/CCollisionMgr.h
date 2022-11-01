#pragma once

class CCollider;

//#define MAKE_COLID(left, right)	(left << 32) | right;

union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	UINT m_Matrix[(UINT)ELAYER::END];
	map<UINT_PTR, bool>	m_mapPrevInfo;	// 이전 프레임의 충돌여부

public:
	void Tick();

public:
	void LayerCheck(ELAYER _Left, ELAYER _Right);
	void Clear();

private:
	void CollisionBtwLayer(ELAYER _Left, ELAYER _Right);
	bool CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight);
};

