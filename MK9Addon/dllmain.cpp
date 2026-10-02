// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/addr.h"
#include "mk/GameInfo.h"
#include "plugin/Hooks.h"
#include "plugin/StageLoader.h"

#include <Commctrl.h>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")

#include <Shlwapi.h>



int MKOCheckForRawFirst(char* mkoName)
{
    if (!mkoName)
        return false;

    static char path[MAX_PATH];

    sprintf(path, "MKScript\\%s", mkoName);

#ifdef _DEBUG
    eLog::Message(__FUNCTION__, "Testing %s - %d\n", mkoName, PathFileExistsA(path));
#endif // DEBUG

    return PathFileExistsA(path);
}


int loadmko_jmp_continue = 0;

// lto'd function
void __declspec(naked) LoadMKO_Hook()
{
    __asm {
        pushad
        push    [esp + 36]
        call MKOCheckForRawFirst
        add  esp, 4
        test eax, eax
        popad
        jnz  pickRaw
        jmp  loadmko_jmp_continue

        pickRaw :
        xor edi, edi
        jmp  loadmko_jmp_continue
    }
}


int nekropolis_jmp_continue = 0;
int nekropolis_jmp_fail = 0;

void __declspec(naked) NekropolisDLCCheck_Hook()
{
    static const char* nameSkarlet = "CHAR_Skarlet";
    static const char* nameKratos = "CHAR_Kratos";

    __asm {
        mov  eax, nameSkarlet
        push eax
        push esi
        call ebx
        add  esp, 8
        test eax, eax
        je   strcmp_0

        mov  eax, nameKratos
        push eax
        push esi
        call ebx
        add  esp, 8
        test eax, eax
        je   strcmp_0

        jmp  nekropolis_jmp_fail

        strcmp_0 :
        jmp  nekropolis_jmp_continue
    }
}


int select_jmp_continue = 0;
int select_amount = 0;


void __declspec(naked) SelectListAmount_Hook()
{
    __asm {
        mov  [ebp - 28], eax
        cmp  eax, select_amount
        jmp  select_jmp_continue
    }
}

int ladder_jmp_continue = 0;
int ladder_amount = 0;


void __declspec(naked) LadderListAmount_Hook()
{
    __asm {
        add    esi, 4
        cmp  esi, ladder_amount
        jmp  ladder_jmp_continue
    }
}

bool IsKratosAvailable()
{
    return PathFileExistsA("Asset\\CHAR_Kratos.xxx");
}

// gameinfo+34d4+c
void OnInitializeHook()
{
    FGGameInfo::FindGameInfo();
    eStageLoader::Init();

    // allow kratos to be used in generated random ladder
    Memory::VP::Nop(_pattern(PATID_Kratos_RandomLadder), 6);
    // allow packages with "kratos" to load
    Memory::VP::Nop(_pattern(PATID_Kratos_Archive), 6);
    // remove Kratos and Khameleon blacklist
    Memory::VP::Nop(_pattern(PATID_Kratos_Khameleon_Blacklist), 2);

    // only do these if kratos available as otherwise nekropolis will be corrupted
    if (IsKratosAvailable())
    {
        // remove kratos blacklist from nekropolis
        Memory::VP::Nop(_pattern(PATID_Kratos_Nekropolis_Blacklist) + 2, 2);
        // nekropolis kratos content
        Memory::VP::Nop(_pattern(PATID_Kratos_Nekropolis_Blacklist2), 10);

        nekropolis_jmp_continue = _pattern(PATID_Nekropolis_DLC_Hook1);
        nekropolis_jmp_fail = _pattern(PATID_Nekropolis_DLC_Hook2);
        Memory::VP::InjectHook(_pattern(PATID_Nekropolis_DLC_Hook0), NekropolisDLCCheck_Hook, Memory::HookType::Jump);

        // remove kenshi hard caps, move to kratos (0)
        Memory::VP::Patch<char>(_pattern(PATID_Nekropolis_Count_Hook0) + 6, 0);
        Memory::VP::Patch<char>(_pattern(PATID_Nekropolis_Count_Hook1) + 2, 0);
        Memory::VP::Patch<int>(_pattern(PATID_Nekropolis_Count_Hook2) + 6, 0);
        Memory::VP::Patch<int>(_pattern(PATID_Nekropolis_Count_Hook3) + 6, 0);
    }

    // kratos fatality replacement
    Memory::VP::InjectHook(_pattern(PATID_StartAssetLoad_Hook), StartAssetLoadHook, Memory::HookType::Call);
    Memory::VP::InjectHook(_pattern(PATID_StartLoadCinematic_Hook), &MKScriptEx::Script_StartLoadingCinematicHook,  Memory::HookType::Call);

    // prefer loading MKOs from MKScript first
    loadmko_jmp_continue = _pattern(PATID_LoadMKO);
    Memory::VP::InjectHook(_pattern(PATID_LoadMKO_Hook0), LoadMKO_Hook, Memory::HookType::Call);
    Memory::VP::InjectHook(_pattern(PATID_LoadMKO_Hook1), LoadMKO_Hook, Memory::HookType::Call);

    // compares changed beacuse theyre one byte

    if (eStageLoader::pSelectStageSize > 0)
    {
        select_amount = sizeof(int) * eStageLoader::pSelectStageSize;
        select_jmp_continue = _pattern(PATID_SelectTable_Hook) + 6;
        Memory::VP::Patch<int>(_pattern(PATID_SelectTable_List) + 2, eStageLoader::pSelectStageList);
        Memory::VP::InjectHook(_pattern(PATID_SelectTable_Hook), SelectListAmount_Hook, Memory::HookType::Jump);
    }

    if (eStageLoader::pLadderStageSize > 0)
    {
        ladder_amount = sizeof(int) * eStageLoader::pLadderStageSize;
        ladder_jmp_continue = _pattern(PATID_LadderTable_Hook) + 6;

        Memory::VP::Patch<int>(_pattern(PATID_LadderTable_List) + 2, eStageLoader::pLadderStageList);
        Memory::VP::InjectHook(_pattern(PATID_LadderTable_Hook), LadderListAmount_Hook, Memory::HookType::Jump);
    }
}

bool ValidateGameVersion()
{
    PatternSolver::Initialize();

    if (PatternSolver::CheckMissingPatterns())
    {
        int nButtonPressed = 0;
        TASKDIALOGCONFIG config;
        ZeroMemory(&config, sizeof(TASKDIALOGCONFIG));

        const TASKDIALOG_BUTTON buttons[] = {
            { IDOK, L"Launch anyway\nThe game might crash or have missing features!" },
            { IDNO, L"Exit" }
        };
        config.cbSize = sizeof(config);

        config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_CAN_BE_MINIMIZED | TDF_USE_COMMAND_LINKS;
        config.pszMainIcon = TD_WARNING_ICON;

        config.pszWindowTitle = L"Warning";
        config.pszMainInstruction = L"MK9Addon";
        config.pszContent = L"Could not start MK9Addon!\n\n"
            L"One or more code patterns could not be found, this might indicate"
            L" that game version is not supported or the plugin has not been updated.\n\n"
            L"MK9Addon officially is only tested with latest Steam version.\n"
            L"Check log for more details.\n";


        config.pButtons = buttons;
        config.cButtons = ARRAYSIZE(buttons);

        if (SUCCEEDED(TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)))
        {
            switch (nButtonPressed)
            {
            case IDOK:
                return true;
                break;
            case IDNO:
                exit(0);
                break;
            default:
                break;
            }
        }
    }

    return true;
}

extern "C"
{
    __declspec(dllexport) void InitializeASI()
    {
        eLog::Initialize();

        if (ValidateGameVersion())
        {
            OnInitializeHook();
        }

    }
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
        eStageLoader::Shutdown();
        break;
    }
    return TRUE;
}
