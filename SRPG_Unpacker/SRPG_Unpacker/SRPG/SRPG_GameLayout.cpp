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
	m_pResourceLayoutData(new RESOURCELAYOUTDATA)
{}

void SRPG_GameLayout::Init(FileReader& fw)
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
			allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

		allocAndSetCMenuOp(&m_pMessageLayoutData, SRPGClasses::MESSAGELAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-MESSAGELAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pShopLayout2, SRPGClasses::SHOPLAYOUT, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-SHOPLAYOUT=" << fw.GetOffset() << std::endl;
#endif
	}

	if (g_ArcVersion >= 0x428)
	{
		allocAndSetCMenuOp(&m_pCommandLayoutData1, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pCommandLayoutData2, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		allocAndSetCMenuOp(&m_pCommandLayoutData3, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif

		if (g_ArcVersion >= 0x43D)
		{
			allocAndSetCMenuOp(&m_pCommandLayoutData4, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
		}

		if (g_ArcVersion >= 0x441)
		{
			allocAndSetCMenuOp(&m_pCommandLayoutData5, SRPGClasses::COMMANDLAYOUTDATA, fw);
#ifdef DEBUG_PRINT
			std::cout << "OFFSET-COMMANDLAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
		}
	}

	if (g_ArcVersion >= 0x49F)
	{
		m_pResourceLayoutData->init(fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-RESOURCELAYOUTDATA=" << fw.GetOffset() << std::endl;
#endif
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_GameLayout::Dump(FileWriter& fw) const
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

void SRPG_GameLayout::WritePatches(const std::filesystem::path& outPath) const
{
}
