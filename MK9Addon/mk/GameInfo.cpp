#include "GameInfo.h"

uintptr_t FGGameInfo::pGameInfo = 0;

void FGGameInfo::FindGameInfo()
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_FindGameInfo);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		FGGameInfo::pGameInfo = (offset);
	}
}


PlayerInfo* FGGameInfo::GetAttackerInfo()
{
	return *(PlayerInfo**)((int)this + 0x80F4);
}

FGGameInfo* GetGameInfo()
{
	return (FGGameInfo*)FGGameInfo::pGameInfo;
}
