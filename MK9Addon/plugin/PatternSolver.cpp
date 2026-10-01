#include "PatternSolver.h"
#include "..\utils\Patterns.h"
#include "..\gui\log.h"
#include <chrono>

uintptr_t PatternSolver::ms_patterns[PATID_Total_Patterns];


uintptr_t PatternSolver::GetPattern(const char* szPattern, int offset)
{
    uintptr_t addr = 0;
    try {
        addr = (uintptr_t)hook::txn::get_pattern(szPattern, offset);
    }
    TXN_CATCH();

    return addr;
}

void PatternSolver::Initialize()
{
    eLog::Message(__FUNCTION__, "Starting pattern search");

    for (int i = 0; i < PATID_Total_Patterns; i++)
        ms_patterns[i] = 0;

    auto begin = std::chrono::high_resolution_clock::now();


    ms_patterns[PATID_FGGameInfo_FindGameInfo] = GetPattern("B9 ? ? ? ? E8 ? ? ? ? 33 FF 39 3D ? ? ? ? 0F 84 ? ? ? ? 83 F8 08", 1);
    ms_patterns[PATID_Kratos_RandomLadder] = GetPattern("0F 84 ? ? ? ? 8D 45 BC 68 ? ? ? ? 50 FF D7 83 C4 08", 0);
    ms_patterns[PATID_Kratos_Archive] = GetPattern("0F 85 ? ? ? ? 8B 45 D4 39 7D D8 75 05 B8", 0);
    ms_patterns[PATID_Kratos_Khameleon_Blacklist] = GetPattern("75 14 83 C7 04 83 FF 08 72 E4 A1 ? ? ? ? 8B 4C 06 08 89 4D FC", 0);
    ms_patterns[PATID_Kratos_Nekropolis_Blacklist] = GetPattern("75 02 33 F6 56 8B CF E8 ? ? ? ? 33 C9 3B F1 0F 84", 0);
    ms_patterns[PATID_Kratos_Nekropolis_Blacklist2] = GetPattern("56 FF D3 83 C4 08 85 C0 75 09 57", 0);

    ms_patterns[PATID_Nekropolis_DLC_Hook0] = GetPattern("68 ? ? ? ? 56 FF D3 83 C4 08 85 C0 75 09", 0);
    ms_patterns[PATID_Nekropolis_DLC_Hook1] = GetPattern("57 E8 ? ? ? ? 83 C4 04 83 45 C8 04 33 C9", 0);
    ms_patterns[PATID_Nekropolis_DLC_Hook2] = GetPattern("83 45 C8 04 33 C9 8B 45 B8 C7 45 ? ? ? ? ? 89 4D BC 3B C1", 0);

    ms_patterns[PATID_Nekropolis_Count_Hook0] = GetPattern("83 B8 B8 01 00 00 01", 0);
    ms_patterns[PATID_Nekropolis_Count_Hook1] = GetPattern("83 F8 01 89 87 ? ? ? ? 0F 8D ? ? ? ? C7 87", 0);
    ms_patterns[PATID_Nekropolis_Count_Hook2] = GetPattern("C7 87 B8 01 00 00 01 00 00 00 33 C0 5F", 0);
    ms_patterns[PATID_Nekropolis_Count_Hook3] = GetPattern("C7 87 B8 01 00 00 01 00 00 00 8B 89 08 02 00 00", 0);

    ms_patterns[PATID_StartAssetLoad_Hook] = GetPattern("A1 ? ? ? ? 8B 40 3C 8B 48 08 8B 50 04 6A 00 51 52 E8 ? ? ? ? 8B 0D ? ? ? ? 83 C4 0C 89 41 1C C3", 18);
    ms_patterns[PATID_StartLoadCinematic_Hook] = GetPattern("E8 ? ? ? ? C3 A1 ? ? ? ? 8B 0D ? ? ? ? 50 51 6A 00 E8 ? ? ? ? 83 C4 0C 85 C0 74 14 8B 15 ? ? ? ? 8B 4A 3C 8B 51 08 52 8B C8 E8 ? ? ? ? C3 A1 ? ? ? ? 8B 0D ? ? ? ? 50 51 6A 00 E8 ? ? ? ? 83 C4 0C 85 C0", 0);

    ms_patterns[PATID_LoadMKO] = GetPattern("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 51 53 56 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 8B 5D 08 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 89 45 F0 33 F6 89 75 FC 3B C6 74 09 8B C8 E8 ? ? ? ? 8B F0", 0);
    ms_patterns[PATID_LoadMKO_Hook0] = GetPattern("E8 ? ? ? ? 8B F0 83 C4 04 3B F3 74 12 8B 7F 24 57 E8 ? ? ? ? 83 C4 04", 0);
    ms_patterns[PATID_LoadMKO_Hook1] = GetPattern("E8 ? ? ? ? 83 C4 04 3B C3 74 06 89 B0 ? ? ? ? 8B 4D F4", 0);

    ms_patterns[PATID_StartAssetLoad] = GetPattern("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 83 EC 10 56 57 A1 ? ? ? ? 33 C5 50 8D 45 F4 64 A3 ? ? ? ? 8B 7D 0C 8B 75 08", 0);

    ms_patterns[PATID_Script_StartLoadingCinematic] = GetPattern("55 8B EC 56 57 8B 7D 08 8B F1 57 8D 4E 54 E8 ? ? ? ? 39 35 ? ? ? ? 75 0F 83 3D ? ? ? ? ? 75 06 89 3D ? ? ? ? 5F 5E 5D C2 04 00", 0);
    ms_patterns[PATID_SelectTable_List] = GetPattern("8B B9 ? ? ? ? 8B 35 ? ? ? ? 8D 49 00", 0);
    ms_patterns[PATID_SelectTable_Hook] = GetPattern("89 45 E4 83 F8 74 0F 82", 0);

    ms_patterns[PATID_LadderTable_List] = GetPattern("8B 86 ? ? ? ? 53 50 FF 15 ? ? ? ? 83 C4 08 85 C0", 0);
    ms_patterns[PATID_LadderTable_Hook] = GetPattern("83 C6 04 83 FE 68 72 E3", 0);

    auto end = std::chrono::high_resolution_clock::now();


    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    auto timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    eLog::Message(__FUNCTION__, "Checked %d patterns in %dms (%ds)", PATID_Total_Patterns, time.count(), timeSeconds.count());

}

int PatternSolver::GetNumPatternsOK()
{
    int patternNum = 0;

    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i]) patternNum++;
    return patternNum;
}

bool PatternSolver::CheckMissingPatterns()
{
    int missingPatterns = 0;
    for (int i = 0; i < PATID_Total_Patterns; i++)
    {
        if (ms_patterns[i] == 0)
        {
            missingPatterns++;
            eLog::Message(__FUNCTION__, "ERROR: Could not find %s!", GetPatternName(i));
        }
    }

    return missingPatterns > 0;
}

const char* PatternSolver::GetPatternName(int id)
{
    if (id >= PATID_Total_Patterns)
        return "UNKNOWN";

    static const char* szPatternNames[PATID_Total_Patterns] = {  
            "FGGameInfo_FindGameInfo",
            "Kratos_RandomLadder",
            "Kratos_Archive",
            "Kratos_Khameleon_Blacklist",
            "Kratos_Nekropolis_Blacklist",
            "Kratos_Nekropolis_Blacklist2",
            "Nekropolis_DLC_Hook0",
            "Nekropolis_DLC_Hook1",
            "Nekropolis_DLC_Hook2",
            "Nekropolis_Count_Hook0",
            "Nekropolis_Count_Hook1",
            "Nekropolis_Count_Hook2",
            "Nekropolis_Count_Hook3",
            "StartAssetLoad_Hook",
            "StartLoadCinematic_Hook",
            "LoadMKO",
            "LoadMKO_Hook0",
            "LoadMKO_Hook1",
            "StartAssetLoad",
            "Script_StartLoadingCinematic",
            "SelectTable_List",
            "SelectTable_Hook",
            "LadderTable_List",
            "LadderTable_Hook",
    };

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
