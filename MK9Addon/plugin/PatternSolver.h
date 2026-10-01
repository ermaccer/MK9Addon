#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_FGGameInfo_FindGameInfo,
	PATID_Kratos_RandomLadder,
	PATID_Kratos_Archive,
	PATID_Kratos_Khameleon_Blacklist,
	PATID_Kratos_Nekropolis_Blacklist,
	PATID_Kratos_Nekropolis_Blacklist2,

	PATID_Nekropolis_DLC_Hook0,
	PATID_Nekropolis_DLC_Hook1,
	PATID_Nekropolis_DLC_Hook2,

	PATID_Nekropolis_Count_Hook0,
	PATID_Nekropolis_Count_Hook1,
	PATID_Nekropolis_Count_Hook2,
	PATID_Nekropolis_Count_Hook3,

	PATID_StartAssetLoad_Hook,
	PATID_StartLoadCinematic_Hook,

	PATID_LoadMKO,
	PATID_LoadMKO_Hook0,
	PATID_LoadMKO_Hook1,
	
	PATID_StartAssetLoad,

	PATID_Script_StartLoadingCinematic,

	PATID_SelectTable_List,
	PATID_SelectTable_Hook,

	PATID_LadderTable_List,
	PATID_LadderTable_Hook,

	PATID_Total_Patterns
};


class PatternSolver {
public:
	static uintptr_t ms_patterns[PATID_Total_Patterns];

	static uintptr_t GetPattern(const char* szPattern, int offset);

	static void			Initialize();
	static int			GetNumPatternsOK();
	static bool			CheckMissingPatterns();
	static const char*	GetPatternName(int id);

};


uintptr_t _pattern(EPatternID id);