#include "PlayerInfo.h"

MKCharacter* PlayerInfo::GetHisObj()
{
    return ((MKCharacter*(__thiscall*)(PlayerInfo*, int))(*(int*)(*(int*)(int)this + 64)))(this, 1);
}
