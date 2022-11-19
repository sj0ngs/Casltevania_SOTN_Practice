#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iterTex, iterTexEnd = m_mapTex.end();
	for (iterTex = m_mapTex.begin(); iterTex != iterTexEnd; ++iterTex)
	{
		DYNAMIC_DELETE(iterTex->second);
	}

	map<wstring, CSound*>::iterator iterSound, iterSoundEnd = m_mapSound.end();
	for (iterSound = m_mapSound.begin(); iterSound != iterSoundEnd; ++iterSound)
	{
		DYNAMIC_DELETE(iterSound->second);
	}
}

void CResMgr::Init()
{
	// Sound 로딩
	
	// bgm
	CResMgr::GetInst()->LoadSound(L"Prayer", L"sound\\Prayer.wav");
	CResMgr::GetInst()->LoadSound(L"Dance_of_Gold", L"sound\\Dance_of_Gold.wav");
	CResMgr::GetInst()->LoadSound(L"Festival_of_Servants", L"sound\\Festival_of_Servants.wav");
	CResMgr::GetInst()->LoadSound(L"I_Am_The_Wind", L"sound\\I_Am_The_Wind.wav");
	CResMgr::GetInst()->LoadSound(L"Game_Over", L"sound\\Game_Over.wav");

	// Effect
	CResMgr::GetInst()->LoadSound(L"Select_Change", L"sound\\Select_Change.wav");
	CResMgr::GetInst()->LoadSound(L"Start", L"sound\\Start.wav");
	CResMgr::GetInst()->LoadSound(L"DOORBS", L"sound\\DOORBS.wav");
	CResMgr::GetInst()->LoadSound(L"GETMEAT", L"sound\\GETMEAT.wav");

	CResMgr::GetInst()->LoadSound(L"FIRE", L"sound\\FIRE.wav");

	CResMgr::GetInst()->LoadSound(L"CANDLE", L"sound\\CANDLE.wav");

	// Player
	CResMgr::GetInst()->LoadSound(L"ATTACK_01", L"sound\\Player\\ATTACK_01.wav");
	CResMgr::GetInst()->LoadSound(L"ATTACK_02", L"sound\\Player\\ATTACK_02.wav");
	CResMgr::GetInst()->LoadSound(L"ATTACK_03", L"sound\\Player\\ATTACK_03.wav");
	CResMgr::GetInst()->LoadSound(L"ATTACK_04", L"sound\\Player\\ATTACK_04.wav");
	CResMgr::GetInst()->LoadSound(L"ATTACK_05", L"sound\\Player\\ATTACK_05.wav");
	CResMgr::GetInst()->LoadSound(L"ATTACK_06", L"sound\\Player\\ATTACK_06.wav");
	CResMgr::GetInst()->LoadSound(L"DAM_S", L"sound\\Player\\DAM_S.wav");
	CResMgr::GetInst()->LoadSound(L"DAM_S_02", L"sound\\Player\\DAM_S_02.wav");
	CResMgr::GetInst()->LoadSound(L"DAM_S_03", L"sound\\Player\\DAM_S_03.wav");
	CResMgr::GetInst()->LoadSound(L"SLIDE", L"sound\\Player\\SLIDE.wav");
	CResMgr::GetInst()->LoadSound(L"DIE", L"sound\\Player\\DIE.wav");

	CResMgr::GetInst()->LoadSound(L"Slash", L"sound\\Player\\Slash.wav");
	CResMgr::GetInst()->LoadSound(L"Projectile", L"sound\\Player\\Projectile.wav");
	CResMgr::GetInst()->LoadSound(L"KNIFE", L"sound\\Player\\KNIFE.wav");
	CResMgr::GetInst()->LoadSound(L"ONO", L"sound\\Player\\ONO.wav");
	CResMgr::GetInst()->LoadSound(L"Landing", L"sound\\Player\\Landing.wav");
	CResMgr::GetInst()->LoadSound(L"Hit", L"sound\\Player\\Hit.wav");
	CResMgr::GetInst()->LoadSound(L"GETHEART", L"sound\\Player\\GETHEART.wav");
	CResMgr::GetInst()->LoadSound(L"GETSUB", L"sound\\Player\\GETSUB.wav");
	CResMgr::GetInst()->LoadSound(L"Double_Jump", L"sound\\Player\\Double_Jump.wav");
	CResMgr::GetInst()->LoadSound(L"THROWTEKI", L"sound\\Player\\THROWTEKI.wav");

	CResMgr::GetInst()->LoadSound(L"SKILL_1", L"sound\\Player\\SKILL_1.wav");
	CResMgr::GetInst()->LoadSound(L"SKILL_2", L"sound\\Player\\SKILL_2.wav");
	CResMgr::GetInst()->LoadSound(L"SKILL_3", L"sound\\Player\\SKILL_3.wav");

	CResMgr::GetInst()->LoadSound(L"DRACULA_FIRE", L"sound\\Player\\DRACULA_FIRE.wav");

	CResMgr::GetInst()->LoadSound(L"BOSSEYE_BEAM", L"sound\\Player\\BOSSEYE_BEAM.wav");

	// Monster
	CResMgr::GetInst()->LoadSound(L"Projectile_Explot", L"sound\\Monster\\Projectile_Explot.wav");
	CResMgr::GetInst()->LoadSound(L"Mon_Attack_01", L"sound\\Monster\\Mon_Attack_01.wav");
	CResMgr::GetInst()->LoadSound(L"Mon_Attack_02", L"sound\\Monster\\Mon_Attack_02.wav");
	CResMgr::GetInst()->LoadSound(L"Mon_Explot", L"sound\\Monster\\Mon_Explot.wav");
	CResMgr::GetInst()->LoadSound(L"Mon_Explot_Into", L"sound\\Monster\\Mon_Explot_Into.wav");
	CResMgr::GetInst()->LoadSound(L"Skeleton_Die", L"sound\\Monster\\Skeleton_Die.wav");
	CResMgr::GetInst()->LoadSound(L"DRACULA_FIRE", L"sound\\Monster\\DRACULA_FIRE.wav");
	CResMgr::GetInst()->LoadSound(L"AXE_AMOR_ATK1", L"sound\\Monster\\AXE_AMOR_ATK1.wav");
	CResMgr::GetInst()->LoadSound(L"AXE_AMOR_ATK2", L"sound\\Monster\\AXE_AMOR_ATK2.wav");
	CResMgr::GetInst()->LoadSound(L"AXE_AMOR_ATK2", L"sound\\Monster\\AXE_AMOR_DEAD.wav");
	CResMgr::GetInst()->LoadSound(L"AXE_AMOR_DEAD", L"sound\\Monster\\AXE_AMOR_DEAD.wav");

	// Slogra
	CResMgr::GetInst()->LoadSound(L"LIZ_DEAD1", L"sound\\Monster\\LIZ_DEAD1.wav");
	CResMgr::GetInst()->LoadSound(L"LIZ_DEAD2", L"sound\\Monster\\LIZ_DEAD2.wav");
	CResMgr::GetInst()->LoadSound(L"GOLEM_MOVE1", L"sound\\Monster\\GOLEM_MOVE1.wav");
	CResMgr::GetInst()->LoadSound(L"Slogra_Fire", L"sound\\Monster\\Slogra_Fire.wav");

	// Gaibon
	CResMgr::GetInst()->LoadSound(L"Gaibon_Roar", L"sound\\Monster\\Gaibon_Roar.wav");
	CResMgr::GetInst()->LoadSound(L"Gaibon_Fire_01", L"sound\\Monster\\Gaibon_Fire_01.wav");
	CResMgr::GetInst()->LoadSound(L"Gaibon_Fire_02", L"sound\\Monster\\Gaibon_Fire_02.wav");
	CResMgr::GetInst()->LoadSound(L"Gaibon_Flap", L"sound\\Monster\\Gaibon_Flap.wav");

	// 텍스쳐 모두 로딩

	// 플레이어 텍스쳐
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\Alucard\\alucard_left_1.bmp");
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"alucard_left_1_Trail", L"texture\\Alucard\\alucard_left_1.bmp");
	ColorChange(pTex);

	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\Alucard\\alucard_right_1.bmp");
	pTex = CResMgr::GetInst()->LoadTexture(L"alucard_right_1_Trail", L"texture\\Alucard\\alucard_right_1.bmp");
	ColorChange(pTex);

	CResMgr::GetInst()->LoadTexture(L"Alucrad_Death", L"texture\\Alucard\\Alucrad_Death.bmp");

	CResMgr::GetInst()->LoadTexture(L"alucard_left_2", L"texture\\Alucard\\alucard_left_2.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_right_2", L"texture\\Alucard\\alucard_right_2.bmp");

	// Sub Weapon Axe Anim
	CResMgr::GetInst()->LoadTexture(L"Axe_Left", L"texture\\Weapon\\Axe_Left.bmp");
	pTex = CResMgr::GetInst()->LoadTexture(L"Axe_Left_Trail", L"texture\\Weapon\\Axe_Left.bmp");
	ColorChange(pTex);

	CResMgr::GetInst()->LoadTexture(L"Axe_Right", L"texture\\Weapon\\Axe_Right.bmp");
	pTex = CResMgr::GetInst()->LoadTexture(L"Axe_Right_Trail", L"texture\\Weapon\\Axe_Right.bmp");
	ColorChange(pTex);

	// Sub Weapon Dagger Anim
	CResMgr::GetInst()->LoadTexture(L"Dagger_Right", L"texture\\Weapon\\Dagger_Right.bmp");
	CResMgr::GetInst()->LoadTexture(L"Dagger_Left", L"texture\\Weapon\\Dagger_Left.bmp");

	// SubWeapon
	CResMgr::GetInst()->LoadTexture(L"Drop_Axe", L"texture\\Weapon\\Drop_Axe.bmp");
	CResMgr::GetInst()->LoadTexture(L"Drop_Dagger", L"texture\\Weapon\\Drop_Dagger.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bible", L"texture\\Weapon\\Bible.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bible_Trail", L"texture\\Weapon\\Bible_Trail_2.bmp");

	// Skill
	CResMgr::GetInst()->LoadTexture(L"HellFire", L"texture\\Weapon\\HellFire.bmp");

	// Level
	CResMgr::GetInst()->LoadTexture(L"Debug_Map", L"texture\\Map\\Debug_Map.bmp");
	CResMgr::GetInst()->LoadTexture(L"Room_1", L"texture\\Map\\Room_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"BackGround", L"texture\\Map\\BackGround.bmp");
	CResMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Map\\Boss_Room.bmp");
	CResMgr::GetInst()->LoadTexture(L"Ending", L"texture\\Map\\Ending.bmp");
	CResMgr::GetInst()->LoadTexture(L"Game_Over_Screen", L"texture\\Map\\Game_Over_Screen.bmp");
	CResMgr::GetInst()->LoadTexture(L"Save_Room", L"texture\\Map\\Save_Room.bmp");
	CResMgr::GetInst()->LoadTexture(L"Save_Room_Front", L"texture\\Map\\Save_Room_Front.bmp");

	// =======
	// Monster
	// =======

	// Skeleton
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Left", L"texture\\Monster\\SKeleton\\Skeleton_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Right", L"texture\\Monster\\SKeleton\\Skeleton_Right.bmp");
	
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Death_Left", L"texture\\Monster\\SKeleton\\Skeleton_Death_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Skeleton_Death_Right", L"texture\\Monster\\SKeleton\\Skeleton_Death_Right.bmp");

	// Blood Skeleton
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Collapse_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Collapse_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Collapse_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Collapse_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Rise_Left", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Rise_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Blood_Skeleton_Rise_Right", L"texture\\Monster\\Blood_Skeleton\\Blood_Skeleton_Rise_Right.bmp");

	// Bone Scimitar
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Left", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Right", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Attack_Left", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Attack_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Bone_Scimitar_Attack_Right", L"texture\\Monster\\Bone_Scimitar\\Bone_Scimitar_Attack_Right.bmp");

	// Axe Armor
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Idle_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Idle_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Idle_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Idle_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Walk_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Walk_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Walk_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Walk_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Throw_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Throw_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Throw_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Throw_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Attack_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Attack_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Attack_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Attack_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Axe_Left", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Axe_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Axe_Right", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Axe_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_Armor_Death", L"texture\\Monster\\Axe_Armor\\Axe_Armor_Death.bmp");

	// Slogra
	CResMgr::GetInst()->LoadTexture(L"Slogra_Left", L"texture\\Monster\\Slogra\\Slogra_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Slogra_Right", L"texture\\Monster\\Slogra\\Slogra_Right.bmp");
	CResMgr::GetInst()->LoadTexture(L"Slogra_Drop", L"texture\\Monster\\Slogra\\Slogra_Drop.bmp");

	// Gaibon
	CResMgr::GetInst()->LoadTexture(L"Gaibon_Left", L"texture\\Monster\\Gaibon\\Gaibon_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Gaibon_Right", L"texture\\Monster\\Gaibon\\Gaibon_Right.bmp");

	CResMgr::GetInst()->LoadTexture(L"Large_Fire_Right", L"texture\\Monster\\Gaibon\\Large_Fire_Right.bmp");
	CResMgr::GetInst()->LoadTexture(L"Large_Fire_Left", L"texture\\Monster\\Gaibon\\Large_Fire_Left.bmp");

	CResMgr::GetInst()->LoadTexture(L"Small_Fire_Right", L"texture\\Monster\\Gaibon\\Small_Fire_Right.bmp");
	CResMgr::GetInst()->LoadTexture(L"Small_Fire_Left", L"texture\\Monster\\Gaibon\\Small_Fire_Left.bmp");

	CResMgr::GetInst()->LoadTexture(L"Item_Crash_Bible_Left", L"texture\\Weapon\\Item_Crash_Bible_Left.bmp");
	CResMgr::GetInst()->LoadTexture(L"Item_Crash_Bible_Right", L"texture\\Weapon\\Item_Crash_Bible_Right.bmp");

	// ======
	// Effect
	// ======

	// Hit
	CResMgr::GetInst()->LoadTexture(L"Hit_Effect", L"texture\\Effect\\Hit_Effect.bmp");

	// Burn 1
	CResMgr::GetInst()->LoadTexture(L"Burn_Effect_1", L"texture\\Effect\\Burn_Effect_1.bmp");

	// Burn 2
	CResMgr::GetInst()->LoadTexture(L"Burn_Effect_2", L"texture\\Effect\\Burn_Effect_2.bmp");

	// Burn 3
	CResMgr::GetInst()->LoadTexture(L"Burn_Effect_3", L"texture\\Effect\\Burn_Effect_3.bmp");

	// Drop_SubWeapon
	CResMgr::GetInst()->LoadTexture(L"Drop_Effect", L"texture\\Effect\\Drop_Effect.bmp");

	CResMgr::GetInst()->LoadTexture(L"Dust", L"texture\\Effect\\Dust.bmp");

	// Light
	CResMgr::GetInst()->LoadTexture(L"Light", L"texture\\Effect\\Light.bmp");

	// ==========
	// Map Object
	// ==========

	CResMgr::GetInst()->LoadTexture(L"Candle", L"texture\\MapObj\\Candle.bmp");
	CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\MapObj\\Button.bmp");

	// ===
	// Map
	// ===

	CResMgr::GetInst()->LoadTexture(L"Title_BackGround", L"texture\\Map\\Title_BackGround.bmp");

	CResMgr::GetInst()->LoadTexture(L"Title", L"texture\\Map\\Title.bmp");

	CResMgr::GetInst()->LoadTexture(L"Title_Anim", L"texture\\Map\\Title_Anim.bmp");

	CResMgr::GetInst()->LoadTexture(L"Title_Anim_2", L"texture\\Map\\Title_Anim_2.bmp");

	CResMgr::GetInst()->LoadTexture(L"Debug_Map", L"texture\\Map\\Debug_Map.bmp");

	CResMgr::GetInst()->LoadTexture(L"BackGround", L"texture\\Map\\BackGround.bmp");

	CResMgr::GetInst()->LoadTexture(L"Room_1", L"texture\\Map\\Room_1.bmp");

	CResMgr::GetInst()->LoadTexture(L"Room_2", L"texture\\Map\\Room_2.bmp");

	CResMgr::GetInst()->LoadTexture(L"Room_3", L"texture\\Map\\Room_3.bmp");

	CResMgr::GetInst()->LoadTexture(L"Wall", L"texture\\Map\\Wall.bmp");

	// ====
	// Item
	// ====

	CResMgr::GetInst()->LoadTexture(L"Large_Heart", L"texture\\Item\\Large_Heart.bmp");

	CResMgr::GetInst()->LoadTexture(L"Small_Heart", L"texture\\Item\\Small_Heart.bmp");

	CResMgr::GetInst()->LoadTexture(L"HP_Heart", L"texture\\Item\\HP_Heart.bmp");

	// ==
	// UI
	// ==

	CResMgr::GetInst()->LoadTexture(L"HUD", L"texture\\UI\\HUD.bmp");

	CResMgr::GetInst()->LoadTexture(L"MPBar", L"texture\\UI\\MPBar.bmp");

	CResMgr::GetInst()->LoadTexture(L"HP_Num", L"texture\\UI\\HP_Num.bmp");

	CResMgr::GetInst()->LoadTexture(L"Heart_Num", L"texture\\UI\\Heart_Num.bmp");

	CResMgr::GetInst()->LoadTexture(L"Red_Num", L"texture\\UI\\Red_Num.bmp");

	CResMgr::GetInst()->LoadTexture(L"Lemon_Num", L"texture\\UI\\Lemon_Num.bmp");

	CResMgr::GetInst()->LoadTexture(L"SubWeapon_Shine", L"texture\\UI\\SubWeapon_Shine.bmp");

	CResMgr::GetInst()->LoadTexture(L"Dagger_UI", L"texture\\UI\\Dagger_UI.bmp");

	CResMgr::GetInst()->LoadTexture(L"Axe_UI", L"texture\\UI\\Axe_UI.bmp");

	CResMgr::GetInst()->LoadTexture(L"Bible_UI", L"texture\\UI\\Bible_UI.bmp");

	CResMgr::GetInst()->LoadTexture(L"Game_Start_Select", L"texture\\UI\\Game_Start_Select.bmp");

	CResMgr::GetInst()->LoadTexture(L"Debug_Mode_Select", L"texture\\UI\\Debug_Mode_Select.bmp");

	CResMgr::GetInst()->LoadTexture(L"Select_Frame", L"texture\\UI\\Select_Frame.bmp");

	CResMgr::GetInst()->LoadTexture(L"Life_Up", L"texture\\UI\\Life_Up.bmp");
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CRes* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
		return (CTexture*)pTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTexture = new CTexture;
	pTexture->Load(strFilePath);
	pTexture->SetKey(_strKey);
	pTexture->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));
	
	return (CTexture*)pTexture;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
		return (CTexture*)pTexture;

	pTexture = new CTexture;
	pTexture->Create(_iWidth, _iHeight);
	pTexture->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, (CTexture*)pTexture));

	return pTexture;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}


CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr != pSound)
		return pSound;

	pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

void CResMgr::ColorChange(CTexture* _pTex)
{
	for (int i = 0; i < (int)_pTex->GetWidth(); i++)
	{
		for (int j = 0; j < (int)_pTex->GetHeight(); j++)
		{
			tPixel tPixel = _pTex->GetPixelColor(i, j);
			if (0 != tPixel.a)
			{
				tPixel.b *= 2;
				tPixel.r /= 2;
				tPixel.g /= 2;
				_pTex->SetPixelColor(i, j, tPixel);
			}
		}
	}
}
