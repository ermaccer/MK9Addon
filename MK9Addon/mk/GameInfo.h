#pragma once
#include "..\utils.h"
#include "PlayerInfo.h"

enum PLAYER_NUM
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
};

class FGGameInfo {
public:
	static void FindGameInfo();
	static uintptr_t pGameInfo;

	PlayerInfo* GetAttackerInfo();


};

FGGameInfo* GetGameInfo();
