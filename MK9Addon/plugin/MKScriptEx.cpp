#include "MKScriptEx.h"
#include "..\mk\GameInfo.h"
#include "..\mk\PlayerInfo.h"
#include "..\mk\MKScript.h"
#include <string>
#include <Shlwapi.h>

const char* MKScriptEx::GetCinemaVictimName()
{
    FGGameInfo* info = GetGameInfo();

    if (!info)
        return nullptr;

    PlayerInfo* attackerInfo = info->GetAttackerInfo();

    if (!attackerInfo)
        return nullptr;

    MKCharacter* his_obj = attackerInfo->GetHisObj();

    if (!his_obj)
        return nullptr;

    return (const char*)((int)his_obj + 0x766C);
}


const char* MKScriptEx::GetKratosFatalityPath(const char* cinemaName)
{
    static char kratosFatalityPath[MAX_PATH] = {};

#ifdef _DEBUG
    eLog::Message(__FUNCTION__, "Checking %s %p", cinemaName, cinemaName);
#endif
    char cinemaNameLower[128] = {};
    for (int i = 0; i < strlen(cinemaName); i++)
    {
        cinemaNameLower[i] = tolower(cinemaName[i]);
    }

    if (!(strstr(cinemaNameLower, "_fatality")))
        return nullptr;

    const char* victimName = GetCinemaVictimName();

    if (!victimName)
        return nullptr;

    char victimNameLower[128] = {};

    for (int i = 0; i< strlen(victimName); i++)
    {
        victimNameLower[i] = tolower(victimName[i]);
    }

    // NOTE: original scripts check only for CHAR_Kratos or CHAR_Kratos_B, this is more free
    if (!(strstr(victimNameLower, "_kratos")))
        return nullptr;

    std::string newPath = cinemaName;

    std::string newPathLower = cinemaNameLower;

    size_t pos = newPathLower.find("_fatality");

    if (pos == std::string::npos)
        return nullptr;

    newPath.insert(pos, "_Kratos");

    std::string assetPath = "Asset\\" + newPath + ".xxx";

    if (!PathFileExistsA(assetPath.c_str()))
        return nullptr;

    sprintf(kratosFatalityPath, newPath.c_str());
#ifdef _DEBUG
    eLog::Message(__FUNCTION__, "Swapping %s to %s", cinemaName, newPath.c_str());
#endif
    return kratosFatalityPath;
}

void MKScriptEx::Script_StartLoadingCinematicHook(int a1)
{
    FatalityCinemaPdata* pData = (FatalityCinemaPdata*)a1;

    if (pData)
    {
        int vTable = (int)*(int*)pData;
        MKScriptObj* classInfo = ((MKScriptObj*(__thiscall*)(FatalityCinemaPdata*))(*(int*)(vTable + 0)))(pData);

        if (classInfo->name)
        {
#ifdef _DEBUG
            eLog::Message(__FUNCTION__, "class: %s", classInfo->name);
#endif
            // sometimes somehow GamepadPdata gets passed through
            if (strcmp(classInfo->name, "FatalityCinemaPdata") == 0)
            {
                if (pData->cinemaName)
                {
                    const char* alt = GetKratosFatalityPath(pData->cinemaName);
                    if (alt)
                        pData->cinemaName = (char*)alt;
                }

            }
        }


    }

    Script_StartLoadingCinematic(a1);
}