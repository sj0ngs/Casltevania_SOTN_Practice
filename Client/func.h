#pragma once

class CObj;
bool IsValid(CObj*& _pTarget);
void Instantiate(CObj* _pNewObj, Vec2 _vPos, ELAYER _Layer);
void ChangeLevel(ELEVEL_TYPE _eNextLevel);

void Saturate(float& _f);

void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);

void RotateVec(Vec2& _Origin, float _Degree);

