#pragma once
#include <memory>

class eStageLoader {
public:

	static int pSelectStageList;
	static int pSelectStageSize;
	static int pLadderStageList;
	static int pLadderStageSize;

	static std::unique_ptr<const char*[]> selectList;
	static std::unique_ptr<const char*[]> ladderList;


	static void Init();

	static bool ReadFile(const char* file, int& list, int& size, std::unique_ptr<const char*[]>& out);

	static void Shutdown();
};