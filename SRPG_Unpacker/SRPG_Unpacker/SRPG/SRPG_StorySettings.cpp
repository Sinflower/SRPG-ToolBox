/*
 *  File: SRPG_StorySettings.cpp
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

#include "SRPG_StorySettings.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_StorySettings::Init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pCharacterData, SRPGClasses::CHARACTERDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-CHARACTERDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pWordData, SRPGClasses::WORDDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-WORDDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pGalleryData, SRPGClasses::GALLERYDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-GALLERYDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pSoundModeData, SRPGClasses::SOUNDMODEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-SOUNDMODEDATA=" << fw.GetOffset() << std::endl;
#endif

	if (g_ArcVersion >= 0x428)
	{
		this_243 = fw.ReadDWord();
		this_244 = fw.ReadDWord();
		this_245 = fw.ReadDWord();
		this_246 = fw.ReadDWord();
		this_247 = fw.ReadDWord();
		this_248 = fw.ReadDWord();
	}

	if (g_ArcVersion >= 0x48D)
		this_249 = fw.ReadDWord();

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_StorySettings::Dump(FileWriter& fw) const
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

void SRPG_StorySettings::WritePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path extraFolder = ExtraPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pCharacterData, extraFolder, L"characters.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pGalleryData, extraFolder, L"gallery.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pWordData, extraFolder, L"glossary.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pSoundModeData, extraFolder, L"soundroom.json");
}
