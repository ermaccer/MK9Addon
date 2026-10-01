#pragma once

struct FatalityCinemaPdata {
    int field0;
    int field4;
    int field8;
    char* postLoad;
    char* postPlay;
    char* ended;
    char* postActivated;
    int   myObj;
    char  pad[32];
    int   field40;       
    const char* cinemaName;
    int   _pad[4];
};

struct MKScriptObj {
    const char* name;
    int size;
    void* base;
};

class MKScript {
public:

	void Script_StartLoadingCinematic(int a1);
};


