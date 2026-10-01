#include "Hooks.h"
#include "..\mk\Engine.h"
#include "..\mk\GameInfo.h"
#include "..\gui\log.h"
int StartAssetLoadHook(int type, const char* name, int a3)
{
    // 6 - character cinematics
    if (type == 6 && name)
    {
        const char* alt = MKScriptEx::GetKratosFatalityPath(name);
        if (alt)
            name = alt;
    }

    return LoadSlotFileAsync(type, name, a3);
}

