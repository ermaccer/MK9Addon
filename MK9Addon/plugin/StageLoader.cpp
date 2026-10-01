#include "StageLoader.h"
#include <iostream>
#include "..\gui\log.h"


int eStageLoader::pSelectStageList = 0;
int eStageLoader::pSelectStageSize = 0;
int eStageLoader::pLadderStageList = 0;
int eStageLoader::pLadderStageSize = 0;

std::unique_ptr<const char*[]> eStageLoader::selectList;
std::unique_ptr<const char*[]> eStageLoader::ladderList;

void eStageLoader::Init()
{
	pSelectStageList = 0;
	pSelectStageSize = 0;
	pLadderStageList = 0;
	pLadderStageSize = 0;

	bool select = ReadFile("data\\selectStageList.cfg", pSelectStageList, pSelectStageSize, selectList);
	bool ladder = ReadFile("data\\ladderStageList.cfg", pLadderStageList, pLadderStageSize, ladderList);

	if (!select || !ladder)
		eLog::Message(__FUNCTION__, "Could not load stage list file, functionality will be disabled for missing files.");
}


bool eStageLoader::ReadFile(const char* file, int& list, int& size, std::unique_ptr<const char* []>& out)
{
	FILE* pFile = fopen(file, "rb");

	if (!pFile)
	{
		eLog::Message(__FUNCTION__, "Failed! Tried to open: %s", file);
		return false;
	}

	if (pFile)
	{
		eLog::Message(__FUNCTION__, "Success! Reading: %s", file);

		int numLines = 0;

		char szLine[2048];
		while (fgets(szLine, sizeof(szLine), pFile))
		{
			// check if comment or empty line
			if (szLine[0] == ';' || szLine[0] == '#' || szLine[0] == '\n')
				continue;

			numLines++;
		}

		fseek(pFile, 0, SEEK_SET);

		out = std::make_unique<const char*[]>(numLines);

		numLines = 0;

		while (fgets(szLine, sizeof(szLine), pFile))
		{
			// check if comment or empty line
			if (szLine[0] == ';' || szLine[0] == '#' || szLine[0] == '\n')
				continue;

			char szName[256] = {};
			if (sscanf(szLine, "%s", szName) == 1)
			{
				int strLen = strlen(szName);
				const char* str = (const char*)calloc(strLen + 1, 1);

				if (!str)
				{
					eLog::Message(__FUNCTION__, "Failed to allocate string for %s\n", szName);
					fclose(pFile);
					return false;
				}

				strcpy_s((char*)str, strLen + 1, szName);
				out[numLines++] = str;
			}
		}


		if (numLines < 1)
		{
			eLog::Message(__FUNCTION__, "At least 1 entry is required!");
			fclose(pFile);
			return false;
		}


		list = (int)&out[0];
		size = numLines;
		eLog::Message(__FUNCTION__, "Read %d entries", size);
		fclose(pFile);
	}

	return true;
}

void eStageLoader::Shutdown()
{
	if (pLadderStageSize > 0)
	{
		for (int i = 0; i < pLadderStageSize; i++)
			free((void*)ladderList[i]);
	}

	if (pSelectStageSize > 0)
	{
		for (int i = 0; i < pSelectStageSize; i++)
			free((void*)selectList[i]);
	}

	pSelectStageList = 0;
	pSelectStageSize = 0;
	pLadderStageList = 0;
	pLadderStageSize = 0;

}
