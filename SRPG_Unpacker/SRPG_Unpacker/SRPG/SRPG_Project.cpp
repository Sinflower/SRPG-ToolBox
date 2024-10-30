/*
 *  File: SRPG_Project.cpp
 *  Copyright (c) 2024 Sinflower
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

// Compatible up to v1.292

#include <direct.h>

#include <codecvt>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

#include "Classes/RESOURCELAYOUTDATA.h"

DWORD g_ArcVersion = 0;

SRPG_Project::SRPG_Project(const SRPG_ProjectData& projData) :
	m_resFlags(projData.resFlag),
	m_pResourceLayoutData(new RESOURCELAYOUTDATA)
{
	g_ArcVersion = projData.version;
	m_fw.InitData(projData.data);
	loadProject();
}

SRPG_Project::~SRPG_Project()
{}

void SRPG_Project::Dump(const std::wstring& outFolder) const
{
	// dump(fw);
	FileWriter fw(std::format(L"{}/{}", outFolder, PROJECT_FILE_NAME));
	dumpAsProj(fw);
	// writeResMapping();
}

nlohmann::ordered_json SRPG_Project::GetResMapping() const
{
	return getResMapping();
}

void SRPG_Project::loadProject()
{
	this_1 = m_fw.ReadDWord();
	this_2 = m_fw.ReadDWord();
	this_3 = m_fw.ReadDWord();
	this_4 = m_fw.ReadDWord();

	// Not sure if this is the correct version but I know that it's not present in this version
	if (g_ArcVersion > 0x470)
	{
		res1 = m_fw.ReadDWord();

		if (res1 == 255)
			res2 = m_fw.ReadDWord(); // Skip the next DWORD
	}

	loadMap();
	loadAnimations(); // start = this_38
	loadDatabase();   // start = this_86
	loadGameLayout(); // start = this_375

	allocAndSetCMenuOp(&m_pbEventData, SRPGClasses::EVENTDATA, m_fw);

	sub_F8EC70();
	loadStorySettings();
	loadBaseSettings(); // start = this_405

	loadResources();

	if (m_fw.IsEndOfFile())
		std::cout << "Successfully parsed the entire project file" << std::endl;
}

// ---------------------------------

void SRPG_Project::loadMap()
{
#ifdef DEBUG_PRINT
	std::cout << std::hex << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapData, SRPGClasses::MAPDATA, m_fw); // Allocate and set MAPDATA object
#ifdef DEBUG_PRINT
	std::cout << "MapData Elements: " << m_pMapData->GetElemCount() << std::endl;
	std::cout << "OFFSET-MAPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapTreeData1, SRPGClasses::MAPTREEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MAPTREEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapTreeData2, SRPGClasses::MAPTREEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MAPTREEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x4FE)
		allocAndSetCMenuOp(&m_pDayNightData, SRPGClasses::DAYNIGHTDATA, m_fw);

	if (g_ArcVersion >= 0x3F9)
		allocAndSetCMenuOp(&m_pEventData1, SRPGClasses::EVENTDATA, m_fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-EVENTDATA=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x432)
	{
		allocAndSetCMenuOp(&m_pEventData2, SRPGClasses::EVENTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-EVENTDATA=" << m_fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pUnitData1, SRPGClasses::UNITDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-UNITDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	this_21 = m_fw.ReadDWord();

	this_22 = m_fw.ReadByte(); // Yes, this is really a byte read
	this_23 = m_fw.ReadDWord();

	this_24 = m_fw.ReadByte(); // Yes, this is really a byte read

	if (g_ArcVersion >= 0x4A0)
	{
		for (CMenuOperation*& pMO : m_pJumpIDData)
			allocAndSetCMenuOp(&pMO, SRPGClasses::JUMPIDDATA, m_fw);
	}

	if (g_ArcVersion >= 0x503)
	{
		for (CMenuOperation*& pMO : m_pJumpIDData2)
			allocAndSetCMenuOp(&pMO, SRPGClasses::JUMPIDDATA, m_fw);
	}

	if (g_ArcVersion >= 0x4A4)
	{
		for (CMenuOperation*& pMO : m_pParamHeadData)
			allocAndSetCMenuOp(&pMO, SRPGClasses::PARAMHEADDATA, m_fw);
	}

	if (g_ArcVersion >= 0x4E2)
		initMemData(this_37, m_fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

void SRPG_Project::loadAnimations()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData3, SRPGClasses::ANIMEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData4, SRPGClasses::ANIMEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData1, SRPGClasses::ANIMEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData2, SRPGClasses::ANIMEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	this_42 = m_fw.ReadDWord();
	this_43 = m_fw.ReadDWord();
	this_48 = m_fw.ReadDWord();
	this_44 = m_fw.ReadDWord();
	this_45 = m_fw.ReadDWord();
	this_46 = m_fw.ReadDWord();
	this_47 = m_fw.ReadDWord();
	this_50 = m_fw.ReadDWord();
	this_51 = m_fw.ReadDWord();
	this_52 = m_fw.ReadDWord();
	this_53 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x41B)
		this_54 = m_fw.ReadDWord();

	this_56 = m_fw.ReadDWord();
	this_57 = m_fw.ReadDWord();
	this_58 = m_fw.ReadDWord();
	this_59 = m_fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal1, SRPGClasses::FRAMEORIGINAL, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal2, SRPGClasses::FRAMEORIGINAL, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal3, SRPGClasses::FRAMEORIGINAL, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion < 0x409)
	{
		this_49 = 0;
		this_63 = 0;
		this_64 = 16711680;
		this_65 = 0;
		this_66 = 0;
		this_67 = 0;
		this_68 = 0;
		this_69 = 0;
		this_70 = 0;
	}
	else
	{
		this_49 = m_fw.ReadDWord();
		this_63 = m_fw.ReadDWord();
		this_64 = m_fw.ReadDWord();
		this_65 = m_fw.ReadDWord();
		this_66 = m_fw.ReadDWord();
		this_67 = m_fw.ReadDWord();
		this_68 = m_fw.ReadDWord();
		this_69 = m_fw.ReadDWord();
		this_70 = m_fw.ReadDWord();
	}

	if (g_ArcVersion < 0x40C)
		this_71 = 1;
	else
		this_71 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x40D)
		initMemData(this_72, m_fw);

	if (g_ArcVersion >= 0x435)
		this_55 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x43F)
	{
		this_76 = m_fw.ReadDWord();
		this_77 = m_fw.ReadDWord();
		this_78 = m_fw.ReadDWord();
		this_79 = m_fw.ReadDWord();
		this_80 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x461)
		this_81 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x46A)
		this_82 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x486)
		this_83 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x48E)
		this_85 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x49B)
		this_84 = 0;
	else
	{
		this_84 = m_fw.ReadDWord();
		this_74 = m_fw.ReadDWord();
		this_75 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x4FF)
	{
		this_86 = m_fw.ReadDWord();
		this_87 = m_fw.ReadDWord();
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

// this = this_86
void SRPG_Project::loadDatabase()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pUnitData2, SRPGClasses::UNITDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-UNITDATA=" << m_fw.GetOffset() << std::endl;
#endif

	// std::cout << *m_pUnitData2 << std::endl;

	allocAndSetCMenuOp(&m_pClassData, SRPGClasses::CLASSDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSDATA=" << m_fw.GetOffset() << std::endl;
#endif

	// std::cout << *m_pClassData << std::endl;

	allocAndSetCMenuOp(&m_pWeaponData, SRPGClasses::WEAPONDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WEAPONDATA=" << m_fw.GetOffset() << std::endl;
#endif

	// std::cout << *m_pWeaponData << std::endl;

	allocAndSetCMenuOp(&m_pItemData, SRPGClasses::ITEMDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMDATA=" << m_fw.GetOffset() << std::endl;
#endif

	// std::cout << *m_pItemData << std::endl;

	allocAndSetCMenuOp(&m_pSkillData, SRPGClasses::SKILLDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SKILLDATA=" << m_fw.GetOffset() << std::endl;
#endif

	// std::cout << *m_pSkillData << std::endl;

	if (g_ArcVersion >= 0x400)
		allocAndSetCMenuOp(&m_pStateData, SRPGClasses::STATEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-STATEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pPassData1, SRPGClasses::PASSDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-PASSDATA1=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pPassData2, SRPGClasses::PASSDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-PASSDATA2=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFontData, SRPGClasses::FONTDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FONTDATA=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x455)
	{
		for (CMenuOperation*& CMO : m_pNPCData)
			allocAndSetCMenuOp(&CMO, SRPGClasses::NPCDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-NPCDATA=" << m_fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pStringData1, SRPGClasses::STRINGDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-STRINGDATA1=" << m_fw.GetOffset() << std::endl;
#endif
	}

	allocAndSetCMenuOp(&m_pScreenffect, SRPGClasses::CLASSGROUPDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSGROUPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSwitchData1, SRPGClasses::SWITCHDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SWITCHDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pScreenScroll, SRPGClasses::CLASSTYPEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CLASSTYPEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pScreenShake, SRPGClasses::MOVETYPEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MOVETYPEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pDifficultyData, SRPGClasses::DIFFICULTYDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-DIFFICULTYDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pItemGroupData1, SRPGClasses::ITEMGROUPDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMGROUPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFacialData, SRPGClasses::FACIALDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FACIALDATA=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x439)
	{
		allocAndSetCMenuOp(&m_pStringData2, SRPGClasses::STRINGDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-STRINGDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	uint32_t elems = (g_ArcVersion < 0x437) ? 3 : 4;

	for (uint32_t i = 0; i < elems; i++)
		allocAndSetCMenuOp(&m_pWeaponTypeData[i], SRPGClasses::WEAPONTYPEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WEAPONTYPEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	sub_F8E4E0();
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F8E4E0=" << m_fw.GetOffset() << std::endl;
#endif

	sub_F7DA50();
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F7DA50=" << m_fw.GetOffset() << std::endl;
#endif

	sub_F7DD10();
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-sub_F7DD10=" << m_fw.GetOffset() << std::endl;

	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
	std::cout << "==== Method END ====" << std::endl;
#endif
}

// this = this_86
void SRPG_Project::sub_F8E4E0()
{
	if (g_ArcVersion >= 0x3F4)
	{
		if (g_ArcVersion == 0x3F4)
		{
			for (uint32_t i = 0; i < 5; i++)
				allocAndSetCMenuOp(&m_pVariableData[i], SRPGClasses::VARIABLEDATA, m_fw);
		}
		else
		{
			for (CMenuOperation*& pCMO : m_pVariableData)
				allocAndSetCMenuOp(&pCMO, SRPGClasses::VARIABLEDATA, m_fw);
		}

		allocAndSetCMenuOp(&m_pStringData3, SRPGClasses::STRINGDATA, m_fw);
	}

	if (g_ArcVersion >= 0x3F7)
	{
		allocAndSetCMenuOp(&m_pStringData4, SRPGClasses::MULTICOMMANDDATA, m_fw);
		allocAndSetCMenuOp(&m_pStringData5, SRPGClasses::MULTICOMMANDDATA, m_fw);
	}

	if (g_ArcVersion >= 0x3F9)
		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, m_fw);

	if (g_ArcVersion >= 0x404)
	{
		if (g_ArcVersion < 0x41D)
			allocAndSetCMenuOp(&m_pShopLayout1, SRPGClasses::SHOPLAYOUT, m_fw);
		else
			allocAndSetCMenuOp(&m_pRaceData, SRPGClasses::RACEDATA, m_fw);
	}

	if (g_ArcVersion >= 0x418)
	{
		allocAndSetCMenuOp(&m_pFusionData, SRPGClasses::FUSIONDATA, m_fw);
		allocAndSetCMenuOp(&m_pMetamorRData, SRPGClasses::METAMORDATA, m_fw);
	}

	if (g_ArcVersion >= 0x441)
		allocAndSetCMenuOp(&m_pPassGroupData, SRPGClasses::PASSGROUPDATA, m_fw);

	if (g_ArcVersion < 0x446)
	{
		this_228 = 2;
		this_229 = 0;
	}
	else
	{
		this_228 = m_fw.ReadDWord();
		this_229 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x49F)
	{
		for (CMenuOperation*& pCMO : m_pOriginalData)
			allocAndSetCMenuOp(&pCMO, SRPGClasses::ORIGINALDATA, m_fw);

		allocAndSetCMenuOp(&m_pStringData6, SRPGClasses::STRINGDATA, m_fw);
	}
}

// this = this_142
void SRPG_Project::sub_F7DA50()
{
	initMemData(this_142, m_fw);
	initMemData(this_143, m_fw);
	initMemData(this_144, m_fw);
	initMemData(this_145, m_fw);
	initMemData(this_146, m_fw);
	initMemData(this_147, m_fw);

	this_148 = m_fw.ReadDWord();
	this_149 = m_fw.ReadDWord();
	this_150 = m_fw.ReadDWord();
	this_151 = m_fw.ReadDWord();
	this_152 = m_fw.ReadDWord();
	this_153 = m_fw.ReadDWord();
	this_154 = m_fw.ReadDWord();
	this_155 = m_fw.ReadDWord();

	this_156 = m_fw.ReadDWord();
	this_157 = m_fw.ReadDWord();
	this_158 = m_fw.ReadDWord();
	this_159 = m_fw.ReadDWord();
	this_160 = m_fw.ReadDWord();
	this_161 = m_fw.ReadDWord();
	this_162 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		this_163 = m_fw.ReadDWord();
		this_164 = m_fw.ReadDWord();
		this_165 = m_fw.ReadDWord();
		this_166 = m_fw.ReadDWord();
		this_167 = m_fw.ReadDWord();
		this_168 = m_fw.ReadDWord();
		this_169 = m_fw.ReadDWord();
		this_170 = m_fw.ReadDWord();
		this_171 = m_fw.ReadDWord();

		this_172 = 30;
		this_173 = 30;
	}
	else
	{
		this_163 = m_fw.ReadDWord();
		this_164 = m_fw.ReadDWord();
		this_165 = m_fw.ReadDWord();
		this_166 = m_fw.ReadDWord();
		this_167 = m_fw.ReadDWord();
		this_168 = m_fw.ReadDWord();
		this_169 = m_fw.ReadDWord();
		this_170 = m_fw.ReadDWord();
		this_171 = m_fw.ReadDWord();

		this_172 = m_fw.ReadDWord();
		this_173 = m_fw.ReadDWord();
	}

	this_178 = m_fw.ReadDWord();

	this_174 = m_fw.ReadDWord();
	this_175 = m_fw.ReadDWord();
	this_176 = m_fw.ReadDWord();
	this_177 = m_fw.ReadDWord();

	this_179 = m_fw.ReadDWord();
	this_180 = m_fw.ReadDWord();
	this_181 = m_fw.ReadDWord();
	this_182 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
		this_183 = 0;
	else
		this_183 = m_fw.ReadDWord();

	allocAndSetCMenuOp(&m_pItemGroupData, SRPGClasses::ITEMGROUPDATA, m_fw);
	allocAndSetCMenuOp(&m_pUnitIDData, SRPGClasses::UNITIDDATA, m_fw);
}

// this = this_186
void SRPG_Project::sub_F7DD10()
{
	// NOTE: Maybe remove all no file related member sets
	//       to allow for better write back later
	if (g_ArcVersion >= 0x3EA)
	{
		initMemData(this_186, m_fw);
		this_187 = m_fw.ReadDWord();
		this_188 = m_fw.ReadDWord();
		this_189 = m_fw.ReadDWord();
		this_190 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3EE)
	{
		this_191 = m_fw.ReadDWord();
		this_192 = m_fw.ReadDWord();
		this_193 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3EF)
		this_194 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x3F0)
		this_195 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x3F1)
	{
		this_196 = m_fw.ReadDWord();
		this_197 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x3F3)
		this_198 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x3F9)
		this_199 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x3FB)
		this_200 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x3FE)
	{
		this_201 = m_fw.ReadDWord();
		this_202 = m_fw.ReadDWord();
		this_203 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x401)
	{
		this_204 = m_fw.ReadDWord();
		this_205 = m_fw.ReadDWord();
		this_206 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x404)
		this_207 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x409)
		this_208 = 0;
	else
		this_208 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x40F)
		this_209 = 0;
	else
		this_209 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x413)
		this_210 = 1;
	else
		this_210 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x415)
		this_210 = 1;
	else
		this_211 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		this_212 = 1;
		this_213 = 0;
		this_214 = 0;
	}
	else
	{
		this_212 = m_fw.ReadDWord();
		this_213 = m_fw.ReadDWord();
		this_214 = m_fw.ReadDWord();
	}

	if (g_ArcVersion < 0x42B)
	{
		this_215 = 100;
		this_216 = 100;
	}
	else
	{
		this_215 = m_fw.ReadDWord();
		this_216 = m_fw.ReadDWord();
	}

	if (g_ArcVersion < 0x431)
	{
		this_217 = 1;
		this_218 = 1;
		this_219 = 1;
	}
	else
	{
		this_217 = m_fw.ReadDWord();
		this_218 = m_fw.ReadDWord();
		this_219 = m_fw.ReadDWord();
	}

	if (g_ArcVersion < 0x437)
		this_220 = 1;
	else
		this_220 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
		this_221 = 1;
	else
		this_221 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x441)
		this_222 = 0;
	else
		this_222 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x446)
		this_223 = 0;
	else
		this_223 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x477)
		this_224 = 0;
	else
		this_224 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x489)
		this_225 = 0;
	else
		this_225 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x4A6)
		this_231 = m_fw.ReadDWord();

	if (g_ArcVersion >= 0x4D2)
		this_230 = m_fw.ReadDWord();
}

// ---------------------------------

void SRPG_Project::loadGameLayout()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x40F)
	{
		this_375 = m_fw.ReadDWord();
		this_376 = m_fw.ReadDWord();
		this_377 = m_fw.ReadDWord();
		this_378 = m_fw.ReadDWord();
		this_379 = m_fw.ReadDWord();

		if (g_ArcVersion >= 0x45C)
		{
			this_380 = m_fw.ReadDWord();
			this_381 = m_fw.ReadDWord();
		}

		if (g_ArcVersion >= 0x4FF)
			allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, m_fw);

		allocAndSetCMenuOp(&m_pMessageLayoutData, SRPGClasses::MESSAGELAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-MESSAGELAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pShopLayout2, SRPGClasses::SHOPLAYOUT, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-SHOPLAYOUT=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (g_ArcVersion >= 0x428)
	{
		allocAndSetCMenuOp(&m_pCommandLayoutData1, SRPGClasses::COMMANDLAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pCommandLayoutData2, SRPGClasses::COMMANDLAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pCommandLayoutData3, SRPGClasses::COMMANDLAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif

		if (g_ArcVersion >= 0x43D)
		{
			allocAndSetCMenuOp(&m_pCommandLayoutData4, SRPGClasses::COMMANDLAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif
		}

		if (g_ArcVersion >= 0x441)
		{
			allocAndSetCMenuOp(&m_pCommandLayoutData5, SRPGClasses::COMMANDLAYOUTDATA, m_fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif
		}
	}

	if (g_ArcVersion >= 0x49F)
	{
		m_pResourceLayoutData->init(m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-RESOURCELAYOUTDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

void SRPG_Project::sub_F8EC70()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropAnimeData, SRPGClasses::INTEROPANIMEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPANIMEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropMediaData, SRPGClasses::INTEROPMEDIADATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPMEDIADATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropGraphicsData, SRPGClasses::INTEROPGRAPHICSDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPGRAPHICSDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropUIData, SRPGClasses::INTEROPUIDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPUIDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropTextUIData, SRPGClasses::INTEROPTEXTUIDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPTEXTUIDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropScreenData, SRPGClasses::INTEROPSCREENDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSCREENDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropStringData1, SRPGClasses::INTEROPSTRINGDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSTRINGDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropStringData2, SRPGClasses::INTEROPSTRINGDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSTRINGDATA=" << m_fw.GetOffset() << std::endl;

	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

void SRPG_Project::loadStorySettings()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pCharacterData, SRPGClasses::CHARACTERDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CHARACTERDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pWordData, SRPGClasses::WORDDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WORDDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pGalleryData, SRPGClasses::GALLERYDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-GALLERYDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSoundModeData, SRPGClasses::SOUNDMODEDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SOUNDMODEDATA=" << m_fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x428)
	{
		this_243 = m_fw.ReadDWord();
		this_244 = m_fw.ReadDWord();
		this_245 = m_fw.ReadDWord();
		this_246 = m_fw.ReadDWord();
		this_247 = m_fw.ReadDWord();
		this_248 = m_fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x48D)
		this_249 = m_fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

// this = this_405
void SRPG_Project::loadBaseSettings()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pRestShopData1, SRPGClasses::RESTSHOPDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTSHOPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pRestShopData2, SRPGClasses::RESTSHOPDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTSHOPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pQuestData, SRPGClasses::QUESTDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-QUESTDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pRestAreaData, SRPGClasses::RESTAREADATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-RESTAREADATA=" << m_fw.GetOffset() << std::endl;
#endif

	for (CMenuOperation*& pCMO : m_pEventDatas)
		allocAndSetCMenuOp(&pCMO, SRPGClasses::EVENTDATA, m_fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-EVENTDATA=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSwitchData2, SRPGClasses::SWITCHDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SWITCHDATA=" << m_fw.GetOffset() << std::endl;
#endif

	initMemData(this_416, m_fw);

	this_417 = m_fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pTestMember, SRPGClasses::TESTMEMBER, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-TESTMEMBER=" << m_fw.GetOffset() << std::endl;
#endif

	this_419 = m_fw.ReadDWord();
	this_420 = m_fw.ReadDWord();
	this_421 = m_fw.ReadDWord();
	this_422 = m_fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
		this_423 = 0;
	else
		this_423 = m_fw.ReadDWord();

	allocAndSetCMenuOp(&m_pItemGroupData2, SRPGClasses::ITEMGROUPDATA, m_fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ITEMGROUPDATA=" << m_fw.GetOffset() << std::endl;
#endif

	this_425 = m_fw.ReadDWord();
	this_426 = m_fw.ReadDWord();
	this_427 = m_fw.ReadDWord();
	this_428 = m_fw.ReadDWord();
	this_429 = m_fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

void SRPG_Project::loadResources()
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __func__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;
#endif

	// NOTE: I don't know when this was added, but I know it was not
	//       present in this version
	if (g_ArcVersion > 0x4CA)
		m_fw.ReadBytes(m_unknown.data(), static_cast<DWORD>(m_unknown.size() * sizeof(DWORD)));

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-UNKNOWN=" << m_fw.GetOffset() << std::endl;
#endif

	if (m_resFlags.HasResData)
	{
		for (CMenuOperation*& pResData : m_resData)
			allocAndSetCMenuOp(&pResData, SRPGClasses::RESDATA, m_fw);

#ifdef DEBUG_PRINT
		std::cout << "OFFSET-RESDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasUIResData)
	{
		for (CMenuOperation*& pUiRes : m_uIResData)
			allocAndSetCMenuOp(&pUiRes, SRPGClasses::UIRESDATA, m_fw);

#ifdef DEBUG_PRINT
		std::cout << "OFFSET-UIRESDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasMediaData)
	{
		for (CMenuOperation*& pMediaData : m_mediaData)
			allocAndSetCMenuOp(&pMediaData, SRPGClasses::MEDIADATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-MEDIADATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasFontData)
	{
		allocAndSetCMenuOp(&m_pInstalledFontData, SRPGClasses::INSTALLEDFONTDATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-INSTALLEDFONTDATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasVideoData)
	{
		allocAndSetCMenuOp(&m_pVideoData, SRPGClasses::VIDEODATA, m_fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-VIDEODATA=" << m_fw.GetOffset() << std::endl;
#endif
	}

	if (g_ArcVersion >= 0x475)
	{
		for (CMenuOperation*& pCID : m_classIDData)
			allocAndSetCMenuOp(&pCID, SRPGClasses::CLASSIDDATA, m_fw);
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << m_fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

// ---------------------------------

void SRPG_Project::dump(FileWriter& fw) const
{
	fw.Write(this_1);
	fw.Write(this_2);
	fw.Write(this_3);
	fw.Write(this_4);

	// Not sure if this is the correct version but I know that it's not present in this version
	if (g_ArcVersion > 0x461)
	{
		fw.Write(res1);

		if (res1 == 255)
			fw.Write(res2);
	}

	dumpMap(fw);
	dumpAnimations(fw);
	dumpDatabase(fw);
	dumpGameLayout(fw);

	m_pbEventData->dump(fw);

	dump_sub_F8EC70(fw);
	dumpStorySettings(fw);
	dumpBaseSettings(fw);

	dumpResources(fw);
}

/*
Project Layout:
0:3 Magic number
4:7 ?
8:B File version
C:1B hash / checksum / ? no idea just copy
1C:37 7 DWORDs, purpose unknown <- Fifth requires >= 1140, last requires >= 1038
38:77 some path, constant in all projects *shrug*
78:18B cmenu objects of CHECKDATA
18C:197 3 DWORDs (version dependend) <- first two requre >= 1165, last requires >= 1232
198:19B mem data <- requires >= 1232
19C:1EF unknown section from resources (size and start may change)
1F0:END data section (with part at the end swapped)
*/

void SRPG_Project::dumpAsProj(FileWriter& fw) const
{
	fw.WriteBytesVec({ 0x53, 0x52, 0x50, 0x47, 0x01, 0x00, 0x00, 0x01 });
	fw.Write(g_ArcVersion);
	fw.Write(this_1);
	fw.Write(this_2);
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(DWORD(0x0));
	fw.Write(DWORD(0x0));
	fw.Write(DWORD(0x0));
	fw.Write(DWORD(0x0));

	if (g_ArcVersion >= 1165)
		fw.Write(DWORD(0x0));

	fw.Write(DWORD(0x0));

	if (g_ArcVersion >= 1038)
		fw.Write(DWORD(0x0));

	fw.WriteBytesVec({ 0x3C, 0x00, 0x00, 0x00, 0x43, 0x00, 0x3A, 0x00, 0x5C, 0x00, 0x55, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x5C, 0x00, 0x6B, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x73, 0x00, 0x5C, 0x00, 0x4F, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x44, 0x00, 0x72, 0x00, 0x69, 0x00, 0x76, 0x00, 0x65, 0x00, 0x5C, 0x00, 0xC7, 0x30, 0xB9, 0x30, 0xAF, 0x30, 0xC8, 0x30, 0xC3, 0x30, 0xD7, 0x30, 0x00, 0x00 });
	fw.WriteBytesVec({ 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00,
					   0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10,
					   0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
					   0x01, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 });

	if (g_ArcVersion >= 1165)
	{
		fw.Write(DWORD(0x1)); // DWORD unknown purpose
		fw.Write(DWORD(0x0)); // DWORD unknown purpose
	}

	if (g_ArcVersion >= 1232)
	{
		fw.Write(DWORD(0x0)); // DWORD unknown purpose
		fw.Write(DWORD(0x0)); // Mem Data, unknown purpose
	}

	if (g_ArcVersion > 1226)
		fw.WriteBytes(m_unknown.data(), m_unknown.size() * sizeof(DWORD));

	dumpMap(fw);
	dumpAnimations(fw);
	dumpDatabase(fw);
	dumpGameLayout(fw);

	m_pbEventData->dump(fw);

	dump_sub_F8EC70(fw);
	dumpStorySettings(fw);

	// fw.WriteBytesVec({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });

	dumpResourcesProj(fw);
	dumpBaseSettings(fw);
}

// ---------------------------------

void SRPG_Project::dumpMap(FileWriter& fw) const
{
	m_pMapData->dump(fw);
	m_pMapTreeData1->dump(fw);
	m_pMapTreeData2->dump(fw);

	if (g_ArcVersion >= 0x4FE)
		m_pDayNightData->dump(fw);

	if (g_ArcVersion >= 0x3F9)
		m_pEventData1->dump(fw);

	if (g_ArcVersion >= 0x432)
	{
		m_pEventData2->dump(fw);
		m_pUnitData1->dump(fw);
	}

	fw.Write(this_21);
	fw.Write(this_22);
	fw.Write(this_23);
	fw.Write(this_24);

	if (g_ArcVersion >= 0x4A0)
	{
		for (const CMenuOperation* pMO : m_pJumpIDData)
			pMO->dump(fw);
	}

	if (g_ArcVersion >= 0x503)
	{
		for (const CMenuOperation* pMO : m_pJumpIDData2)
			pMO->dump(fw);
	}

	if (g_ArcVersion >= 0x4A4)
	{
		for (const CMenuOperation* pMO : m_pParamHeadData)
			pMO->dump(fw);
	}

	if (g_ArcVersion >= 0x4E2)
		this_37.Write(fw);
}

// ---------------------------------

void SRPG_Project::dumpAnimations(FileWriter& fw) const
{
	m_pAnimeData3->dump(fw);
	m_pAnimeData4->dump(fw);
	m_pAnimeData1->dump(fw);
	m_pAnimeData2->dump(fw);

	fw.Write(this_42);
	fw.Write(this_43);
	fw.Write(this_48);
	fw.Write(this_44);
	fw.Write(this_45);
	fw.Write(this_46);
	fw.Write(this_47);
	fw.Write(this_50);
	fw.Write(this_51);
	fw.Write(this_52);
	fw.Write(this_53);

	if (g_ArcVersion >= 0x41B)
		fw.Write(this_54);

	fw.Write(this_56);
	fw.Write(this_57);
	fw.Write(this_58);
	fw.Write(this_59);

	m_pFrameOriginal1->dump(fw);
	m_pFrameOriginal2->dump(fw);
	m_pFrameOriginal3->dump(fw);

	if (g_ArcVersion >= 0x409)
	{
		fw.Write(this_49);
		fw.Write(this_63);
		fw.Write(this_64);
		fw.Write(this_65);
		fw.Write(this_66);
		fw.Write(this_67);
		fw.Write(this_68);
		fw.Write(this_69);
		fw.Write(this_70);
	}

	if (g_ArcVersion >= 0x40C)
		fw.Write(this_71);

	if (g_ArcVersion >= 0x40D)
		this_72.Write(fw);

	if (g_ArcVersion >= 0x435)
		fw.Write(this_55);

	if (g_ArcVersion >= 0x43F)
	{
		fw.Write(this_76);
		fw.Write(this_77);
		fw.Write(this_78);
		fw.Write(this_79);
		fw.Write(this_80);
	}

	if (g_ArcVersion >= 0x461)
		fw.Write(this_81);

	if (g_ArcVersion >= 0x46A)
		fw.Write(this_82);

	if (g_ArcVersion >= 0x486)
		fw.Write(this_83);

	if (g_ArcVersion >= 0x48E)
		fw.Write(this_85);

	if (g_ArcVersion >= 0x49B)
	{
		fw.Write(this_84);
		fw.Write(this_74);
		fw.Write(this_75);
	}

	if (g_ArcVersion >= 0x4FF)
	{
		fw.Write(this_86);
		fw.Write(this_87);
	}
}

// ---------------------------------

void SRPG_Project::dumpDatabase(FileWriter& fw) const
{
	m_pUnitData2->dump(fw);
	m_pClassData->dump(fw);
	m_pWeaponData->dump(fw);
	m_pItemData->dump(fw);
	m_pSkillData->dump(fw);

	if (g_ArcVersion >= 0x400)
		m_pStateData->dump(fw);

	m_pPassData1->dump(fw);
	m_pPassData2->dump(fw);
	m_pFontData->dump(fw);

	if (g_ArcVersion >= 0x455)
	{
		for (const CMenuOperation* CMO : m_pNPCData)
			CMO->dump(fw);

		m_pStringData1->dump(fw);
	}

	m_pScreenffect->dump(fw);
	m_pSwitchData1->dump(fw);
	m_pScreenScroll->dump(fw);
	m_pScreenShake->dump(fw);
	m_pDifficultyData->dump(fw);
	m_pItemGroupData1->dump(fw);
	m_pFacialData->dump(fw);

	if (g_ArcVersion >= 0x439)
		m_pStringData2->dump(fw);

	uint32_t elems = (g_ArcVersion < 0x437) ? 3 : 4;

	for (uint32_t i = 0; i < elems; i++)
		m_pWeaponTypeData[i]->dump(fw);

	dump_sub_F8E4E0(fw);
	dump_sub_F7DA50(fw);
	dump_sub_F7DD10(fw);
}

void SRPG_Project::dump_sub_F8E4E0(FileWriter& fw) const
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
		m_pStringData4->dump(fw);
		m_pStringData5->dump(fw);
	}

	if (g_ArcVersion >= 0x3F9)
		m_pTypeIDData->dump(fw);

	if (g_ArcVersion >= 0x404)
	{
		if (g_ArcVersion < 0x41D)
			m_pShopLayout1->dump(fw);
		else
			m_pRaceData->dump(fw);
	}

	if (g_ArcVersion >= 0x418)
	{
		m_pFusionData->dump(fw);
		m_pMetamorRData->dump(fw);
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

void SRPG_Project::dump_sub_F7DA50(FileWriter& fw) const
{
	this_142.Write(fw);
	this_143.Write(fw);
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

	fw.Write(this_156);
	fw.Write(this_157);
	fw.Write(this_158);
	fw.Write(this_159);
	fw.Write(this_160);
	fw.Write(this_161);
	fw.Write(this_162);

	if (g_ArcVersion < 0x418)
	{
		fw.Write(this_163);
		fw.Write(this_164);
		fw.Write(this_165);
		fw.Write(this_166);
		fw.Write(this_167);
		fw.Write(this_168);
		fw.Write(this_169);
		fw.Write(this_170);
		fw.Write(this_171);
	}
	else
	{
		fw.Write(this_163);
		fw.Write(this_164);
		fw.Write(this_165);
		fw.Write(this_166);
		fw.Write(this_167);
		fw.Write(this_168);
		fw.Write(this_169);
		fw.Write(this_170);
		fw.Write(this_171);

		fw.Write(this_172);
		fw.Write(this_173);
	}

	fw.Write(this_178);

	fw.Write(this_174);
	fw.Write(this_175);
	fw.Write(this_176);
	fw.Write(this_177);

	fw.Write(this_179);
	fw.Write(this_180);
	fw.Write(this_181);
	fw.Write(this_182);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_183);

	m_pItemGroupData->dump(fw);
	m_pUnitIDData->dump(fw);
}

void SRPG_Project::dump_sub_F7DD10(FileWriter& fw) const
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

// ---------------------------------

void SRPG_Project::dumpGameLayout(FileWriter& fw) const
{
	if (g_ArcVersion >= 0x40F)
	{
		fw.Write(this_375);
		fw.Write(this_376);
		fw.Write(this_377);
		fw.Write(this_378);
		fw.Write(this_379);

		if (g_ArcVersion >= 0x45C)
		{
			fw.Write(this_380);
			fw.Write(this_381);
		}

		if (g_ArcVersion >= 0x4FF)
			m_pTypeIDData2->dump(fw);

		m_pMessageLayoutData->dump(fw);
		m_pShopLayout2->dump(fw);
	}

	if (g_ArcVersion >= 0x428)
	{
		m_pCommandLayoutData1->dump(fw);
		m_pCommandLayoutData2->dump(fw);
		m_pCommandLayoutData3->dump(fw);

		if (g_ArcVersion >= 0x43D)
			m_pCommandLayoutData4->dump(fw);

		if (g_ArcVersion >= 0x441)
			m_pCommandLayoutData5->dump(fw);
	}

	if (g_ArcVersion >= 0x49F)
		m_pResourceLayoutData->dump(fw);
}

// ---------------------------------

void SRPG_Project::dump_sub_F8EC70(FileWriter& fw) const
{
	m_pInteropAnimeData->dump(fw);
	m_pInteropMediaData->dump(fw);
	m_pInteropGraphicsData->dump(fw);
	m_pInteropUIData->dump(fw);
	m_pInteropTextUIData->dump(fw);
	m_pInteropScreenData->dump(fw);
	m_pInteropStringData1->dump(fw);
	m_pInteropStringData2->dump(fw);
}

// ---------------------------------

void SRPG_Project::dumpStorySettings(FileWriter& fw) const
{
	m_pCharacterData->dump(fw);
	m_pWordData->dump(fw);
	m_pGalleryData->dump(fw);
	m_pSoundModeData->dump(fw);

	if (g_ArcVersion >= 0x428)
	{
		fw.Write(this_243);
		fw.Write(this_244);
		fw.Write(this_245);
		fw.Write(this_246);
		fw.Write(this_247);
		fw.Write(this_248);
	}

	if (g_ArcVersion >= 0x48D)
		fw.Write(this_249);
}

// ---------------------------------

void SRPG_Project::dumpBaseSettings(FileWriter& fw) const
{
	m_pRestShopData1->dump(fw);
	m_pRestShopData2->dump(fw);
	m_pQuestData->dump(fw);
	m_pRestAreaData->dump(fw);

	for (const CMenuOperation* pCMO : m_pEventDatas)
		pCMO->dump(fw);

	m_pSwitchData2->dump(fw);

	this_416.Write(fw);

	fw.Write(this_417);

	m_pTestMember->dump(fw);

	fw.Write(this_419);
	fw.Write(this_420);
	fw.Write(this_421);
	fw.Write(this_422);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_423);

	m_pItemGroupData2->dump(fw);

	fw.Write(this_425);
	fw.Write(this_426);
	fw.Write(this_427);
	fw.Write(this_428);
	fw.Write(this_429);
}

// ---------------------------------

void SRPG_Project::dumpResources(FileWriter& fw) const
{
	// NOTE: I don't know when this was added, but I know it was not
	//       present in this version
	if (g_ArcVersion > 0x4C5)
		fw.WriteBytes(m_unknown.data(), m_unknown.size() * sizeof(DWORD));

	if (m_resFlags.HasResData)
	{
		for (const CMenuOperation* pResData : m_resData)
			pResData->dump(fw);
	}

	if (m_resFlags.HasUIResData)
	{
		for (const CMenuOperation* pUiRes : m_uIResData)
			pUiRes->dump(fw);
	}

	if (m_resFlags.HasMediaData)
	{
		for (const CMenuOperation* pMediaData : m_mediaData)
			pMediaData->dump(fw);
	}

	if (m_resFlags.HasFontData)
		m_pInstalledFontData->dump(fw);

	if (m_resFlags.HasVideoData)
		m_pVideoData->dump(fw);

	if (g_ArcVersion >= 0x475)
	{
		for (const CMenuOperation* pCID : m_classIDData)
			pCID->dump(fw);
	}
}

void SRPG_Project::dumpResourcesProj(FileWriter& fw) const
{
	for (const CMenuOperation* pResData : m_resData)
	{
		if (m_resFlags.HasResData)
			pResData->dump(fw);
		else
			fw.Write(DWORD(0));
	}

	for (const CMenuOperation* pMediaData : m_mediaData)
	{
		if (m_resFlags.HasMediaData)
			pMediaData->dump(fw);
		else
			fw.Write(DWORD(0));
	}

	for (const CMenuOperation* pUiRes : m_uIResData)
	{
		if (m_resFlags.HasUIResData)
			pUiRes->dump(fw);
		else
			fw.Write(DWORD(0));
	}

	if (m_resFlags.HasFontData)
		m_pInstalledFontData->dump(fw);
	else
		fw.Write(DWORD(0));

	if (m_resFlags.HasVideoData)
		m_pVideoData->dump(fw);
	else
		fw.Write(DWORD(0));

	if (g_ArcVersion >= 0x475)
	{
		for (const CMenuOperation* pCID : m_classIDData)
			pCID->dump(fw);
	}
}

static const std::vector<std::string> SECTION_NAMES = {
	"Graphics\\mapchip",
	"Graphics\\charchip",
	"Graphics\\face",
	"Graphics\\icon",
	"Graphics\\motion",
	"Graphics\\effect",
	"Graphics\\weapon",
	"Graphics\\bow",
	"Graphics\\thumbnail",
	"Graphics\\battleback",
	"Graphics\\eventback",
	"Graphics\\screenback",
	"Graphics\\worldmap",
	"Graphics\\eventstill",
	"Graphics\\charillust",
	"Graphics\\picture",
	"UI\\menuwindow",
	"UI\\textwindow",
	"UI\\title",
	"UI\\number",
	"UI\\bignumber",
	"UI\\gauge",
	"UI\\line",
	"UI\\risecursor",
	"UI\\mapcursor",
	"UI\\pagecursor",
	"UI\\selectcursor",
	"UI\\scrollcursor",
	"UI\\panel",
	"UI\\faceframe",
	"UI\\screenframe",
	"Audio\\music",
	"Audio\\sound",
	"Fonts",
	"Video"
};

nlohmann::ordered_json SRPG_Project::getResMapping() const
{
	std::size_t secIdx = 0;
	nlohmann::ordered_json j;

	if (m_resFlags.HasResData)
	{
		for (const CMenuOperation* pResData : m_resData)
		{
			const nlohmann::ordered_json data = pResData->ToJson();
			if (!data.empty())
				j[SECTION_NAMES[secIdx]] = data;
			secIdx++;
		}
	}
	else
		secIdx += m_resData.size();

	if (m_resFlags.HasUIResData)
	{
		for (const CMenuOperation* pUiRes : m_uIResData)
		{
			const nlohmann::ordered_json data = pUiRes->ToJson();
			if (!data.empty())
				j[SECTION_NAMES[secIdx]] = data;
			secIdx++;
		}
	}
	else
		secIdx += m_uIResData.size();

	if (m_resFlags.HasMediaData)
	{
		for (const CMenuOperation* pMediaData : m_mediaData)
		{
			const nlohmann::ordered_json data = pMediaData->ToJson();
			if (!data.empty())
				j[SECTION_NAMES[secIdx]] = data;
			secIdx++;
		}
	}
	else
		secIdx += m_mediaData.size();

	if (m_resFlags.HasFontData)
	{
		const nlohmann::ordered_json data = m_pInstalledFontData->ToJson();
		if (!data.empty())
			j[SECTION_NAMES[secIdx]] = data;
		secIdx++;
	}
	else
		secIdx++;

	if (m_resFlags.HasVideoData)
	{
		const nlohmann::ordered_json data = m_pVideoData->ToJson();
		if (!data.empty())
			j[SECTION_NAMES[secIdx]] = data;
		secIdx++;
	}

	nlohmann::ordered_json j2;

	// Build a new json with the correct mapping
	// Iterate over all objects in the json
	for (const auto& [key, value] : j.items())
	{
		nlohmann::ordered_json j3;
		// Iterate over the array in the object
		for (const auto& v : value)
		{
			// Get the name of the object
			std::string name = v["data"]["name"].get<std::string>();

			// Get the number of the object
			uint32_t id = v["id"].get<uint32_t>();

			// Add the object to the new json
			j3[std::to_string(id)] = name;
		}

		// Add the object to the new json
		j2[key] = j3;
	}

	return j2;
}

// ---------------------------------
