/*
 *  File: SRPG_Database.cpp
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

#include "SRPG_Database.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_Database::Init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pPlayerUnits, SRPGClasses::UNITDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-UNITDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pClasses, SRPGClasses::CLASSDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pWeapons, SRPGClasses::WEAPONDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WEAPONDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pItems, SRPGClasses::ITEMDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSkills, SRPGClasses::SKILLDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SKILLDATA=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x400)
		allocAndSetCMenuOp(&m_pStates, SRPGClasses::STATEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-STATEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pPassData1, SRPGClasses::PASSDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-PASSDATA1=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pPassData2, SRPGClasses::PASSDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-PASSDATA2=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFonts, SRPGClasses::FONTDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FONTDATA=" << fw.GetOffset() << std::endl;
#endif

	///////////////
	// Config Tab
	///////////////

	if (g_ArcVersion >= 0x455)
	{
		for (CMenuOperation*& CMO : m_pNPCSettings)
			allocAndSetCMenuOp(&CMO, SRPGClasses::NPCDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-NPCDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pStringData1, SRPGClasses::STRINGDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-STRINGDATA1=" << fw.GetOffset() << std::endl;
#endif
	}

	allocAndSetCMenuOp(&m_pClassGroups, SRPGClasses::CLASSGROUPDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSGROUPDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSwitchData, SRPGClasses::SWITCHDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SWITCHDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pClassTypes, SRPGClasses::CLASSTYPEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSTYPEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMoveTypeData, SRPGClasses::MOVETYPEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MOVETYPEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pDifficulties, SRPGClasses::DIFFICULTYDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-DIFFICULTYDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pItemGroupData1, SRPGClasses::ITEMGROUPDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMGROUPDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFacialData, SRPGClasses::FACIALDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FACIALDATA=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x439)
	{
		allocAndSetCMenuOp(&m_pStringData2, SRPGClasses::STRINGDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-STRINGDATA=" << fw.GetOffset() << std::endl;
#endif
	}

	uint32_t elems = (g_ArcVersion < 0x437) ? 3 : 4;

	for (uint32_t i = 0; i < elems; i++)
		allocAndSetCMenuOp(&m_pWeaponTypes[i], SRPGClasses::WEAPONTYPEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WEAPONTYPEDATA=" << fw.GetOffset() << std::endl;
#endif

	sub_F8E4E0(fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F8E4E0=" << fw.GetOffset() << std::endl;
#endif

	sub_F7DA50(fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F7DA50=" << fw.GetOffset() << std::endl;
#endif

	sub_F7DD10(fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F7DD10=" << fw.GetOffset() << std::endl;

	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_Database::Dump(FileWriter& fw) const
{
	m_pPlayerUnits->dump(fw);
	m_pClasses->dump(fw);
	m_pWeapons->dump(fw);
	m_pItems->dump(fw);
	m_pSkills->dump(fw);

	if (g_ArcVersion >= 0x400)
		m_pStates->dump(fw);

	m_pPassData1->dump(fw);
	m_pPassData2->dump(fw);
	m_pFonts->dump(fw);

	if (g_ArcVersion >= 0x455)
	{
		for (const CMenuOperation* CMO : m_pNPCSettings)
			CMO->dump(fw);

		m_pStringData1->dump(fw);
	}

	m_pClassGroups->dump(fw);
	m_pSwitchData->dump(fw);
	m_pClassTypes->dump(fw);
	m_pMoveTypeData->dump(fw);
	m_pDifficulties->dump(fw);
	m_pItemGroupData1->dump(fw);
	m_pFacialData->dump(fw);

	if (g_ArcVersion >= 0x439)
		m_pStringData2->dump(fw);

	uint32_t elems = (g_ArcVersion < 0x437) ? 3 : 4;

	for (uint32_t i = 0; i < elems; i++)
		m_pWeaponTypes[i]->dump(fw);

	dump_sub_F8E4E0(fw);
	dump_sub_F7DA50(fw);
	dump_sub_F7DD10(fw);
}

void SRPG_Database::WritePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path commonsFolder     = CommonsPath(outPath);
	const std::filesystem::path cmdStrsFolder     = CommandStringsPath(outPath);
	const std::filesystem::path weaponTypesFolder = WeaponTypesPath(outPath);
	const std::filesystem::path npcSettingsFolder = NPCSettingsPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pClasses, commonsFolder, L"classes.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pClassGroups, commonsFolder, L"classesgroups.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pClassTypes, commonsFolder, L"classtypes.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pDifficulties, commonsFolder, L"difficulties.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pFonts, commonsFolder, L"fonts.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pFusionSettings, commonsFolder, L"fusionsettings.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pItems, commonsFolder, L"items.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pPlayerUnits, commonsFolder, L"players.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pRaces, commonsFolder, L"races.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pSkills, commonsFolder, L"skills.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pStates, commonsFolder, L"states.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pTransformations, commonsFolder, L"transformations.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWeapons, commonsFolder, L"weapons.json");

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWeaponTypes[0], weaponTypesFolder, L"fighters.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWeaponTypes[1], weaponTypesFolder, L"archers.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWeaponTypes[2], weaponTypesFolder, L"mages.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWeaponTypes[3], weaponTypesFolder, L"items.json");

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pCmdStrPlaceEv, cmdStrsFolder, L"placeevents.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pCmdStrTalkEv, cmdStrsFolder, L"talkevents.json");

	for (uint32_t i = 0; i < m_pNPCSettings.size(); i++)
	{
		const std::wstring filename = std::format(L"npc{}.json", i + 1);
		CHECK_OBJ_AND_WRITE_JSON_FILE(m_pNPCSettings[i], npcSettingsFolder, filename);
	}
}

void SRPG_Database::ApplyPatches(const std::filesystem::path& patchPath)
{
	const std::filesystem::path commonsFolder     = CommonsPath(patchPath);
	const std::filesystem::path cmdStrsFolder     = CommandStringsPath(patchPath);
	const std::filesystem::path weaponTypesFolder = WeaponTypesPath(patchPath);
	const std::filesystem::path npcSettingsFolder = NPCSettingsPath(patchPath);

	CHECK_OBJ_AND_APPLY_PATCH(m_pClasses, commonsFolder, L"classes.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pClassGroups, commonsFolder, L"classesgroups.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pClassTypes, commonsFolder, L"classtypes.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pDifficulties, commonsFolder, L"difficulties.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pFonts, commonsFolder, L"fonts.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pFusionSettings, commonsFolder, L"fusionsettings.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pItems, commonsFolder, L"items.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pPlayerUnits, commonsFolder, L"players.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pRaces, commonsFolder, L"races.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pSkills, commonsFolder, L"skills.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pStates, commonsFolder, L"states.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pTransformations, commonsFolder, L"transformations.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pWeapons, commonsFolder, L"weapons.json");

	CHECK_OBJ_AND_APPLY_PATCH(m_pWeaponTypes[0], weaponTypesFolder, L"fighters.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pWeaponTypes[1], weaponTypesFolder, L"archers.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pWeaponTypes[2], weaponTypesFolder, L"mages.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pWeaponTypes[3], weaponTypesFolder, L"items.json");

	CHECK_OBJ_AND_APPLY_PATCH(m_pCmdStrPlaceEv, cmdStrsFolder, L"placeevents.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pCmdStrTalkEv, cmdStrsFolder, L"talkevents.json");

	for (uint32_t i = 0; i < m_pNPCSettings.size(); i++)
	{
		const std::wstring filename = std::format(L"npc{}.json", i + 1);
		CHECK_OBJ_AND_APPLY_PATCH(m_pNPCSettings[i], npcSettingsFolder, filename);
	}
}

void SRPG_Database::sub_F8E4E0(FileReader& fw)
{
	if (g_ArcVersion >= 0x3F4)
	{
		if (g_ArcVersion == 0x3F4)
		{
			for (uint32_t i = 0; i < 5; i++)
				allocAndSetCMenuOp(&m_pVariableData[i], SRPGClasses::VARIABLEDATA, fw);
		}
		else
		{
			for (CMenuOperation*& pCMO : m_pVariableData)
				allocAndSetCMenuOp(&pCMO, SRPGClasses::VARIABLEDATA, fw);
		}

		allocAndSetCMenuOp(&m_pStringData3, SRPGClasses::STRINGDATA, fw);
	}

	if (g_ArcVersion >= 0x3F7)
	{
		allocAndSetCMenuOp(&m_pCmdStrPlaceEv, SRPGClasses::MULTICOMMANDDATA, fw);
		allocAndSetCMenuOp(&m_pCmdStrTalkEv, SRPGClasses::MULTICOMMANDDATA, fw);
	}

	if (g_ArcVersion >= 0x3F9)
		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 0x404)
	{
		if (g_ArcVersion < 0x41D)
			allocAndSetCMenuOp(&m_pShopLayout1, SRPGClasses::SHOPLAYOUT, fw);
		else
			allocAndSetCMenuOp(&m_pRaces, SRPGClasses::RACEDATA, fw);
	}

	if (g_ArcVersion >= 0x418)
	{
		allocAndSetCMenuOp(&m_pFusionSettings, SRPGClasses::FUSIONDATA, fw);
		allocAndSetCMenuOp(&m_pTransformations, SRPGClasses::METAMORDATA, fw);
	}

	if (g_ArcVersion >= 0x441)
		allocAndSetCMenuOp(&m_pPassGroupData, SRPGClasses::PASSGROUPDATA, fw);

	if (g_ArcVersion >= 0x446)
	{
		this_228 = fw.ReadDWord();
		this_229 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x49F)
	{
		for (CMenuOperation*& pCMO : m_pOriginalData)
			allocAndSetCMenuOp(&pCMO, SRPGClasses::ORIGINALDATA, fw);

		allocAndSetCMenuOp(&m_pStringData6, SRPGClasses::STRINGDATA, fw);
	}
}

void SRPG_Database::sub_F7DA50(FileReader& fw)
{
	initMemData(m_windowTitle, fw);
	initMemData(m_gameTitle, fw);
	initMemData(this_144, fw);
	initMemData(this_145, fw);
	initMemData(this_146, fw);
	initMemData(this_147, fw);

	this_148 = fw.ReadDWord();
	this_149 = fw.ReadDWord();
	this_150 = fw.ReadDWord();
	this_151 = fw.ReadDWord();
	this_152 = fw.ReadDWord();
	this_153 = fw.ReadDWord();
	this_154 = fw.ReadDWord();
	this_155 = fw.ReadDWord();

	m_gold          = fw.ReadDWord();
	m_bonus         = fw.ReadDWord();
	m_maxSkillCount = fw.ReadDWord();
	m_maxItemCount  = fw.ReadDWord();
	m_convoyItem    = fw.ReadDWord();
	m_maxEnemyCount = fw.ReadDWord();
	m_maxLv         = fw.ReadDWord();

	m_maxHP  = fw.ReadDWord();
	m_maxStr = fw.ReadDWord();
	m_maxMag = fw.ReadDWord();
	m_maxSkl = fw.ReadDWord();
	m_maxSpd = fw.ReadDWord();
	m_maxLck = fw.ReadDWord();
	m_maxDef = fw.ReadDWord();
	m_maxRes = fw.ReadDWord();
	m_maxMov = fw.ReadDWord();

	if (g_ArcVersion >= 0x418)
	{
		m_maxWlv = fw.ReadDWord();
		m_maxBld = fw.ReadDWord();
	}

	this_178 = fw.ReadDWord();

	m_pursuitValue = fw.ReadDWord();
	m_minExp       = fw.ReadDWord();
	m_leaderExp    = fw.ReadDWord();
	m_subLeaderExp = fw.ReadDWord();

	this_179 = fw.ReadDWord();
	this_180 = fw.ReadDWord();
	this_181 = fw.ReadDWord();
	this_182 = fw.ReadDWord();

	if (g_ArcVersion >= 0x43D)
		this_183 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pItemGroupData, SRPGClasses::ITEMGROUPDATA, fw);
	allocAndSetCMenuOp(&m_pUnitIDData, SRPGClasses::UNITIDDATA, fw);
}

void SRPG_Database::sub_F7DD10(FileReader& fw)
{
	if (g_ArcVersion >= 0x3EA)
	{
		initMemData(this_186, fw);
		this_187 = fw.ReadDWord();
		this_188 = fw.ReadDWord();
		this_189 = fw.ReadDWord();
		this_190 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3EE)
	{
		this_191 = fw.ReadDWord();
		this_192 = fw.ReadDWord();
		this_193 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3EF)
		this_194 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3F0)
		this_195 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3F1)
	{
		this_196 = fw.ReadDWord();
		this_197 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3F3)
		this_198 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3F9)
		this_199 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3FB)
		this_200 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3FE)
	{
		this_201 = fw.ReadDWord();
		this_202 = fw.ReadDWord();
		this_203 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x401)
	{
		this_204 = fw.ReadDWord();
		this_205 = fw.ReadDWord();
		this_206 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x404)
		this_207 = fw.ReadDWord();

	if (g_ArcVersion >= 0x409)
		this_208 = fw.ReadDWord();

	if (g_ArcVersion >= 0x40F)
		this_209 = fw.ReadDWord();

	if (g_ArcVersion >= 0x413)
		this_210 = fw.ReadDWord();

	if (g_ArcVersion >= 0x415)
		this_211 = fw.ReadDWord();

	if (g_ArcVersion >= 0x418)
	{
		this_212 = fw.ReadDWord();
		this_213 = fw.ReadDWord();
		this_214 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x42B)
	{
		this_215 = fw.ReadDWord();
		this_216 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x431)
	{
		this_217 = fw.ReadDWord();
		this_218 = fw.ReadDWord();
		this_219 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x437)
		this_220 = fw.ReadDWord();

	if (g_ArcVersion >= 0x43D)
		this_221 = fw.ReadDWord();

	if (g_ArcVersion >= 0x441)
		this_222 = fw.ReadDWord();

	if (g_ArcVersion >= 0x446)
		this_223 = fw.ReadDWord();

	if (g_ArcVersion >= 0x477)
		this_224 = fw.ReadDWord();

	if (g_ArcVersion >= 0x489)
		this_225 = fw.ReadDWord();

	if (g_ArcVersion >= 0x4A6)
		this_231 = fw.ReadDWord();

	if (g_ArcVersion >= 0x4D2)
		this_230 = fw.ReadDWord();
}

void SRPG_Database::dump_sub_F8E4E0(FileWriter& fw) const
{
	if (g_ArcVersion >= 0x3F4)
	{
		if (g_ArcVersion == 0x3F4)
		{
			for (uint32_t i = 0; i < 5; i++)
				m_pVariableData[i]->dump(fw);
		}
		else
		{
			for (const CMenuOperation* pCMO : m_pVariableData)
				pCMO->dump(fw);
		}

		m_pStringData3->dump(fw);
	}

	if (g_ArcVersion >= 0x3F7)
	{
		m_pCmdStrPlaceEv->dump(fw);
		m_pCmdStrTalkEv->dump(fw);
	}

	if (g_ArcVersion >= 0x3F9)
		m_pTypeIDData->dump(fw);

	if (g_ArcVersion >= 0x404)
	{
		if (g_ArcVersion < 0x41D)
			m_pShopLayout1->dump(fw);
		else
			m_pRaces->dump(fw);
	}

	if (g_ArcVersion >= 0x418)
	{
		m_pFusionSettings->dump(fw);
		m_pTransformations->dump(fw);
	}

	if (g_ArcVersion >= 0x441)
		m_pPassGroupData->dump(fw);

	if (g_ArcVersion >= 0x446)
	{
		fw.Write(this_228);
		fw.Write(this_229);
	}

	if (g_ArcVersion >= 0x49F)
	{
		for (const CMenuOperation* pCMO : m_pOriginalData)
			pCMO->dump(fw);

		m_pStringData6->dump(fw);
	}
}

void SRPG_Database::dump_sub_F7DA50(FileWriter& fw) const
{
	m_windowTitle.Write(fw);
	m_gameTitle.Write(fw);
	this_144.Write(fw);
	this_145.Write(fw);
	this_146.Write(fw);
	this_147.Write(fw);

	fw.Write(this_148);
	fw.Write(this_149);
	fw.Write(this_150);
	fw.Write(this_151);
	fw.Write(this_152);
	fw.Write(this_153);
	fw.Write(this_154);
	fw.Write(this_155);

	fw.Write(m_gold);
	fw.Write(m_bonus);
	fw.Write(m_maxSkillCount);
	fw.Write(m_maxItemCount);
	fw.Write(m_convoyItem);
	fw.Write(m_maxEnemyCount);
	fw.Write(m_maxLv);

	fw.Write(m_maxHP);
	fw.Write(m_maxStr);
	fw.Write(m_maxMag);
	fw.Write(m_maxSkl);
	fw.Write(m_maxSpd);
	fw.Write(m_maxLck);
	fw.Write(m_maxDef);
	fw.Write(m_maxRes);
	fw.Write(m_maxMov);

	if (g_ArcVersion >= 0x418)
	{
		fw.Write(m_maxWlv);
		fw.Write(m_maxBld);
	}

	fw.Write(this_178);

	fw.Write(m_pursuitValue);
	fw.Write(m_minExp);
	fw.Write(m_leaderExp);
	fw.Write(m_subLeaderExp);

	fw.Write(this_179);
	fw.Write(this_180);
	fw.Write(this_181);
	fw.Write(this_182);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_183);

	m_pItemGroupData->dump(fw);
	m_pUnitIDData->dump(fw);
}

void SRPG_Database::dump_sub_F7DD10(FileWriter& fw) const
{
	if (g_ArcVersion >= 0x3EA)
	{
		this_186.Write(fw);
		fw.Write(this_187);
		fw.Write(this_188);
		fw.Write(this_189);
		fw.Write(this_190);
	}

	if (g_ArcVersion >= 0x3EE)
	{
		fw.Write(this_191);
		fw.Write(this_192);
		fw.Write(this_193);
	}

	if (g_ArcVersion >= 0x3EF)
		fw.Write(this_194);

	if (g_ArcVersion >= 0x3F0)
		fw.Write(this_195);

	if (g_ArcVersion >= 0x3F1)
	{
		fw.Write(this_196);
		fw.Write(this_197);
	}

	if (g_ArcVersion >= 0x3F3)
		fw.Write(this_198);

	if (g_ArcVersion >= 0x3F9)
		fw.Write(this_199);

	if (g_ArcVersion >= 0x3FB)
		fw.Write(this_200);

	if (g_ArcVersion >= 0x3FE)
	{
		fw.Write(this_201);
		fw.Write(this_202);
		fw.Write(this_203);
	}

	if (g_ArcVersion >= 0x401)
	{
		fw.Write(this_204);
		fw.Write(this_205);
		fw.Write(this_206);
	}

	if (g_ArcVersion >= 0x404)
		fw.Write(this_207);

	if (g_ArcVersion >= 0x409)
		fw.Write(this_208);

	if (g_ArcVersion >= 0x40F)
		fw.Write(this_209);

	if (g_ArcVersion >= 0x413)
		fw.Write(this_210);

	if (g_ArcVersion >= 0x415)
		fw.Write(this_211);

	if (g_ArcVersion >= 0x418)
	{
		fw.Write(this_212);
		fw.Write(this_213);
		fw.Write(this_214);
	}

	if (g_ArcVersion >= 0x42B)
	{
		fw.Write(this_215);
		fw.Write(this_216);
	}

	if (g_ArcVersion >= 0x431)
	{
		fw.Write(this_217);
		fw.Write(this_218);
		fw.Write(this_219);
	}

	if (g_ArcVersion >= 0x437)
		fw.Write(this_220);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_221);

	if (g_ArcVersion >= 0x441)
		fw.Write(this_222);

	if (g_ArcVersion >= 0x446)
		fw.Write(this_223);

	if (g_ArcVersion >= 0x477)
		fw.Write(this_224);

	if (g_ArcVersion >= 0x489)
		fw.Write(this_225);

	if (g_ArcVersion >= 0x4A6)
		fw.Write(this_231);

	if (g_ArcVersion >= 0x4D2)
		fw.Write(this_230);
}
