/*
 *  File: SRPG_Animations.cpp
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

#include "SRPG_Animations.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_Animations::init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData1, SRPGClasses::ANIMEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData2, SRPGClasses::ANIMEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData3, SRPGClasses::ANIMEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pAnimeData4, SRPGClasses::ANIMEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-ANIMEDATA=" << fw.GetOffset() << std::endl;
#endif

	this_42 = fw.ReadDWord();
	this_43 = fw.ReadDWord();
	this_48 = fw.ReadDWord();
	this_44 = fw.ReadDWord();
	this_45 = fw.ReadDWord();
	this_46 = fw.ReadDWord();
	this_47 = fw.ReadDWord();
	this_50 = fw.ReadDWord();
	this_51 = fw.ReadDWord();
	this_52 = fw.ReadDWord();
	this_53 = fw.ReadDWord();

	if (g_ArcVersion >= 0x41B)
		this_54 = fw.ReadDWord();

	this_56 = fw.ReadDWord();
	this_57 = fw.ReadDWord();
	this_58 = fw.ReadDWord();
	this_59 = fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal1, SRPGClasses::FRAMEORIGINAL, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal2, SRPGClasses::FRAMEORIGINAL, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pFrameOriginal3, SRPGClasses::FRAMEORIGINAL, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-FRAMEORIGINAL=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x409)
	{
		this_49 = fw.ReadDWord();
		this_63 = fw.ReadDWord();
		this_64 = fw.ReadDWord();
		this_65 = fw.ReadDWord();
		this_66 = fw.ReadDWord();
		this_67 = fw.ReadDWord();
		this_68 = fw.ReadDWord();
		this_69 = fw.ReadDWord();
		this_70 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x40C)
		this_71 = fw.ReadDWord();

	if (g_ArcVersion >= 0x40D)
		initMemData(this_72, fw);

	if (g_ArcVersion >= 0x435)
		this_55 = fw.ReadDWord();

	if (g_ArcVersion >= 0x43F)
	{
		this_76 = fw.ReadDWord();
		this_77 = fw.ReadDWord();
		this_78 = fw.ReadDWord();
		this_79 = fw.ReadDWord();
		this_80 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x461)
		this_81 = fw.ReadDWord();

	if (g_ArcVersion >= 0x46A)
		this_82 = fw.ReadDWord();

	if (g_ArcVersion >= 0x486)
		this_83 = fw.ReadDWord();

	if (g_ArcVersion >= 0x48E)
		this_85 = fw.ReadDWord();

	if (g_ArcVersion >= 0x49B)
	{
		this_84 = fw.ReadDWord();
		this_74 = fw.ReadDWord();
		this_75 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x4FF)
	{
		this_86 = fw.ReadDWord();
		this_87 = fw.ReadDWord();
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_Animations::dump(FileWriter& fw) const
{
	m_pAnimeData1->dump(fw);
	m_pAnimeData2->dump(fw);
	m_pAnimeData3->dump(fw);
	m_pAnimeData4->dump(fw);

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

void SRPG_Animations::writePatches(const std::filesystem::path& outPath) const
{
}
