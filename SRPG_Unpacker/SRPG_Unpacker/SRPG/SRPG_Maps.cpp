/*
 *  File: SRPG_Maps.cpp
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

#include "SRPG_Maps.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

#include "Classes/MAPDATA.h"

namespace fs = std::filesystem;

void SRPG_Maps::Init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << std::hex << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapData, SRPGClasses::MAPDATA, fw); // Allocate and set MAPDATA object
#ifdef DEBUG_PRINT
	std::cout << "MapData Elements: " << m_pMapData->GetElemCount() << std::endl;
	std::cout << "OFFSET-MAPDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapTreeData1, SRPGClasses::MAPTREEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MAPTREEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pMapTreeData2, SRPGClasses::MAPTREEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-MAPTREEDATA=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x4FE)
		allocAndSetCMenuOp(&m_pDayNightData, SRPGClasses::DAYNIGHTDATA, fw);

	if (g_ArcVersion >= 0x3F9)
		allocAndSetCMenuOp(&m_pMapCommonEvents, SRPGClasses::EVENTDATA, fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-EVENTDATA=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x432)
	{
		allocAndSetCMenuOp(&m_pBookmarkEvents, SRPGClasses::EVENTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-EVENTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pUnitData1, SRPGClasses::UNITDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-UNITDATA=" << fw.GetOffset() << std::endl;
#endif
	}

	this_21 = fw.ReadDWord();

	this_22 = fw.ReadByte(); // Yes, this is really a byte read
	this_23 = fw.ReadDWord();

	this_24 = fw.ReadByte(); // Yes, this is really a byte read

	if (g_ArcVersion >= 0x4A0)
	{
		for (CMenuOperation*& pMO : m_pJumpIDData)
			allocAndSetCMenuOp(&pMO, SRPGClasses::JUMPIDDATA, fw);
	}

	if (g_ArcVersion >= 0x503)
	{
		for (CMenuOperation*& pMO : m_pJumpIDData2)
			allocAndSetCMenuOp(&pMO, SRPGClasses::JUMPIDDATA, fw);
	}

	if (g_ArcVersion >= 0x4A4)
	{
		for (CMenuOperation*& pMO : m_pParamHeadData)
			allocAndSetCMenuOp(&pMO, SRPGClasses::PARAMHEADDATA, fw);
	}

	if (g_ArcVersion >= 0x4E2)
		initMemData(this_37, fw);

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_Maps::Dump(FileWriter& fw) const
{
	m_pMapData->dump(fw);
	m_pMapTreeData1->dump(fw);
	m_pMapTreeData2->dump(fw);

	if (g_ArcVersion >= 0x4FE)
		m_pDayNightData->dump(fw);

	if (g_ArcVersion >= 0x3F9)
		m_pMapCommonEvents->dump(fw);

	if (g_ArcVersion >= 0x432)
	{
		m_pBookmarkEvents->dump(fw);
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

void SRPG_Maps::WritePatches(const fs::path& outPath) const
{
	const fs::path mapFolder = outPath / MAPS_PATCH_FOLDER;

	// Create the maps folder if it doesn't exist
	if (!fs::exists(mapFolder))
		fs::create_directories(mapFolder);

	// Write each map to its own file
	for (const EDITDATA* pObj : *m_pMapData)
	{
		const MAPDATA* pMap  = static_cast<const MAPDATA*>(pObj);
		std::wstring fN      = std::format(L"map_{}_{}.json", pObj->id, SanitizeFileName(pMap->mapName.ToWString()));
		const fs::path fPath = mapFolder / fN;

		nlohmann::ordered_json json = pObj->ToJson();

		// Write the json to file
		std::ofstream ofs(fPath);
		ofs << json.dump(4);
		ofs.close();
	}
}
