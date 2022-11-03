#pragma once

class CTexture;

struct tCamEffect
{
	ECAMERA_EFFECT m_eCurEffect;
	float m_fAccTime;
	float m_fMaxTime;
};

// Camera Shake ±¸Çö

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2				m_vLook;
	Vec2				m_vDiff;
	CTexture*			m_pBlindText;
	list<tCamEffect>	m_CamEffectList;
	float				m_fRatio;
	float				m_fCameraSpeed;
	bool				m_iCameraMove;
	
	POINT				m_ptResolution;
	UINT				m_iLevelWidth;
	UINT				m_iLevelHeight;

	// Camera Shake 
	bool				m_bShakeOn;
	float				m_fShakeSpeed;
	float				m_fShakeAccTime; 
	float				m_fShakeMaxTime;
	float				m_fShakeRange;
	int					m_fShakeDir;
	Vec2				m_vShakeOffset;		

public:
	void SetLook(Vec2 _vLook) { m_vLook = _vLook; }
	Vec2 GetLook()	const { return m_vLook; }

	void SetCameraMove(bool _bMove) { m_iCameraMove = _bMove; }

	void SetMapSize(POINT _ptResoltion, UINT _iLevelWidth, UINT _iLevelHeight);

public:
	void Tick();
	void Render(HDC _hDC);

public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

private:
	void CameraEffect();
	void CameraShake();

public:
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);
	void CameraShake(float _fTerm, float _fRange, float _fSpeed = 1000.f);

	void TracePlayer(Vec2 _vPos);
};

