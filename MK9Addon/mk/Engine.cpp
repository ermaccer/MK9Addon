#include "Engine.h"
#include "..\plugin\PatternSolver.h"

int LoadSlotFileAsync(int type, const char* name, int a3)
{
    static uintptr_t pat = _pattern(PATID_StartAssetLoad);
    if (pat)
        return ((int(__cdecl*)(int, const char*, int))pat)(type, name, a3);

    return 0;
}
