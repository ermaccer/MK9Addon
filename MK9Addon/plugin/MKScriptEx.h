#pragma once
#include "..\mk\MKScript.h"



class MKScriptEx : public MKScript {
public:
	static const char* GetCinemaVictimName();
	static const char* GetKratosFatalityPath(const char* cinemaName);
	void Script_StartLoadingCinematicHook(int a1);
};