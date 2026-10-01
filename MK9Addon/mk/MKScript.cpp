#include "MKScript.h"
#include "..\plugin\PatternSolver.h"

void MKScript::Script_StartLoadingCinematic(int a1)
{
    static uintptr_t pat = _pattern(PATID_Script_StartLoadingCinematic);
    if (pat)
        ((void(__thiscall*)(void*, int))pat)(this, a1);
}