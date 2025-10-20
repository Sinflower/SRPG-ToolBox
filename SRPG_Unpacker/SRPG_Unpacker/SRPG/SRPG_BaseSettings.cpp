/*
 *  File: SRPG_BaseSettings.cpp
 *  Copyright (c) 2025 Sinflower
 *
 *  MIT License
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include "SRPG_BaseSettings.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_BaseSettings::init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pShops, SRPGClasses::RESTSHOPDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTSHOPDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pBonuses, SRPGClasses::RESTSHOPDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTSHOPDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pQuests, SRPGClasses::QUESTDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-QUESTDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pRestAreas, SRPGClasses::RESTAREADATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTAREADATA=" << fw.GetOffset() << std::endl;
#endif

	for (CMenuOperation*& pCMO : m_pEventDatas)
		allocAndSetCMenuOp(&pCMO, SRPGClasses::EVENTDATA, fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-EVENTDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSwitchData, SRPGClasses::SWITCHDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SWITCHDATA=" << fw.GetOffset() << std::endl;
#endif

	initMemData(saveFileTitle, fw);

	this_417 = fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pTestMember, SRPGClasses::TESTMEMBER, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-TESTMEMBER=" << fw.GetOffset() << std::endl;
#endif

	this_419 = fw.ReadDWord();
	this_420 = fw.ReadDWord();
	this_421 = fw.ReadDWord();
	this_422 = fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
		this_423 = 0;
	else
		this_423 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pItemGroupData, SRPGClasses::ITEMGROUPDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMGROUPDATA=" << fw.GetOffset() << std::endl;
#endif

	this_425 = fw.ReadDWord();
	this_426 = fw.ReadDWord();
	this_427 = fw.ReadDWord();
	this_428 = fw.ReadDWord();
	this_429 = fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_BaseSettings::dump(FileWriter& fw) const
{
	m_pShops->Dump(fw);
	m_pBonuses->Dump(fw);
	m_pQuests->Dump(fw);
	m_pRestAreas->Dump(fw);

	for (const CMenuOperation* pCMO : m_pEventDatas)
		pCMO->Dump(fw);

	m_pSwitchData->Dump(fw);

	saveFileTitle.Write(fw);

	fw.Write(this_417);

	m_pTestMember->Dump(fw);

	fw.Write(this_419);
	fw.Write(this_420);
	fw.Write(this_421);
	fw.Write(this_422);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_423);

	m_pItemGroupData->Dump(fw);

	fw.Write(this_425);
	fw.Write(this_426);
	fw.Write(this_427);
	fw.Write(this_428);
	fw.Write(this_429);
}

void SRPG_BaseSettings::writePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path basePath = BaseSettingsPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pShops, basePath, L"shops.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pBonuses, basePath, L"bonuses.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pQuests, basePath, L"quests.json");

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[0], basePath, L"placeevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[1], basePath, L"autoevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[2], basePath, L"talkevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[3], basePath, L"openingevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[4], basePath, L"endingevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pEventDatas[5], basePath, L"communicationevents.json");
}

void SRPG_BaseSettings::applyPatches(const std::filesystem::path& patchPath)
{
	const std::filesystem::path basePath = BaseSettingsPath(patchPath);

	CHECK_OBJ_AND_APPLY_PATCH(m_pShops, basePath, L"shops.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pBonuses, basePath, L"bonuses.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pQuests, basePath, L"quests.json");

	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[0], basePath, L"placeevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[1], basePath, L"autoevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[2], basePath, L"talkevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[3], basePath, L"openingevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[4], basePath, L"endingevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pEventDatas[5], basePath, L"communicationevents.json");
}
