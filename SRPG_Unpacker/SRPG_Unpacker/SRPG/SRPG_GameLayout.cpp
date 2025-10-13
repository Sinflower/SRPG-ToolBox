/*
 *  File: SRPG_GameLayout.cpp
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

#include "SRPG_GameLayout.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

#include "Classes/RESOURCELAYOUTDATA.h"

SRPG_GameLayout::SRPG_GameLayout() :
	SRPG_ContainerBase("Game Layout"),
	m_pResourceLayout(new RESOURCELAYOUTDATA)
{}

void SRPG_GameLayout::init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x40F)
	{
		this_375 = fw.ReadDWord();
		this_376 = fw.ReadDWord();
		this_377 = fw.ReadDWord();
		this_378 = fw.ReadDWord();
		this_379 = fw.ReadDWord();

		if (g_ArcVersion >= 0x45C)
		{
			this_380 = fw.ReadDWord();
			this_381 = fw.ReadDWord();
		}

		if (g_ArcVersion >= 0x4FF)
			allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

		allocAndSetCMenuOp(&m_pMessageLayout, SRPGClasses::MESSAGELAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-MESSAGELAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pShopLayout, SRPGClasses::SHOPLAYOUT, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-SHOPLAYOUT=" << fw.GetOffset() << std::endl;
#endif
	}

	if (g_ArcVersion >= 0x428)
	{
		allocAndSetCMenuOp(&m_pTitleLayout, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pBattlePrepLayout, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pMapCommandsLayout, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		if (g_ArcVersion >= 0x43D)
		{
			allocAndSetCMenuOp(&m_pBaseLayout, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
		}

		if (g_ArcVersion >= 0x441)
		{
			allocAndSetCMenuOp(&m_pManageLayout, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
		}
	}

	if (g_ArcVersion >= 0x49F)
	{
		m_pResourceLayout->init(fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-RESOURCELAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_GameLayout::dump(FileWriter& fw) const
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
			m_pTypeIDData->Dump(fw);

		m_pMessageLayout->Dump(fw);
		m_pShopLayout->Dump(fw);
	}

	if (g_ArcVersion >= 0x428)
	{
		m_pTitleLayout->Dump(fw);
		m_pBattlePrepLayout->Dump(fw);
		m_pMapCommandsLayout->Dump(fw);

		if (g_ArcVersion >= 0x43D)
			m_pBaseLayout->Dump(fw);

		if (g_ArcVersion >= 0x441)
			m_pManageLayout->Dump(fw);
	}

	if (g_ArcVersion >= 0x49F)
		m_pResourceLayout->dump(fw);
}

void SRPG_GameLayout::writePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path commonsFolder = CommonsPath(outPath);
	const std::filesystem::path layoutsFolder = LayoutsPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pShopLayout, commonsFolder, L"shoplayout.json");

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pBaseLayout, layoutsFolder, L"base.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pBattlePrepLayout, layoutsFolder, L"battleprep.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pManageLayout, layoutsFolder, L"manage.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pMapCommandsLayout, layoutsFolder, L"mapcommands.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pTitleLayout, layoutsFolder, L"title.json");
}

void SRPG_GameLayout::applyPatches(const std::filesystem::path& patchPath)
{
	const std::filesystem::path commonsFolder = CommonsPath(patchPath);
	const std::filesystem::path layoutsFolder = LayoutsPath(patchPath);

	CHECK_OBJ_AND_APPLY_PATCH(m_pShopLayout, commonsFolder, L"shoplayout.json");

	CHECK_OBJ_AND_APPLY_PATCH(m_pBaseLayout, layoutsFolder, L"base.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pBattlePrepLayout, layoutsFolder, L"battleprep.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pManageLayout, layoutsFolder, L"manage.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pMapCommandsLayout, layoutsFolder, L"mapcommands.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pTitleLayout, layoutsFolder, L"title.json");
}
