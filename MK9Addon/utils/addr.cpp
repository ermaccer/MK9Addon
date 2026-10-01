#include "..\pch.h"
#include "addr.h"

int GetEntryPoint()
{
	static int addr = reinterpret_cast<int>(GetModuleHandle(nullptr));
	return addr;
}

int _addr(int addr)
{
	static int ImageBase = 0x400000;
	return GetEntryPoint() - ImageBase + addr;
}
