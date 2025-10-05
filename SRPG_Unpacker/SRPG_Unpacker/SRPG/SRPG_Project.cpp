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

#include <iostream>

#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

namespace fs = std::filesystem;

DWORD g_ArcVersion = 0;

SRPG_Project::SRPG_Project(const SRPG_ProjectData& projData) :
	m_resources(projData.resFlag)
{
	g_ArcVersion = projData.version;
	m_fw.InitData(projData.data);
	loadProject();
}

SRPG_Project::~SRPG_Project()
{}

void SRPG_Project::Dump(const std::wstring& outFolder) const
{
	FileWriter fw(std::format(L"{}/{}", outFolder, PROJECT_FILE_NAME));
	dump(fw);
	// dumpAsProj(fw);
	//  writeResMapping();
}

nlohmann::ordered_json SRPG_Project::GetResMapping() const
{
	return m_resources.GetResMapping();
}

void SRPG_Project::WritePatch(const fs::path& outPath) const
{
	m_maps.WritePatches(outPath);
	m_database.WritePatches(outPath);
	m_gameLayout.WritePatches(outPath);
	m_recollectionEvents.WritePatches(outPath);
	m_storySettings.WritePatches(outPath);
	m_baseSettings.WritePatches(outPath);

	std::filesystem::path commonsPath = SRPG_ContainerBase::CommonsPath(outPath);
	nlohmann::ordered_json j;
	j["windowTitle"]   = m_database.GetWindowTitle();
	j["gameTitle"]     = m_database.GetGameTitle();
	j["saveFileTitle"] = m_baseSettings.GetSaveFileTitle();
	WriteJsonToFile(j, commonsPath, L"titles.json");
}

void SRPG_Project::ApplyPatch(const std::filesystem::path& patchPath)
{
	m_maps.ApplyPatches(patchPath);
	m_database.ApplyPatches(patchPath);
	m_gameLayout.ApplyPatches(patchPath);
	m_recollectionEvents.ApplyPatches(patchPath);
	m_storySettings.ApplyPatches(patchPath);
	m_baseSettings.ApplyPatches(patchPath);

	std::filesystem::path commonsPath = SRPG_ContainerBase::CommonsPath(patchPath);

	nlohmann::ordered_json j = ReadJsonFromFile(commonsPath, L"titles.json");

	CALL_STR_SET_FUNC_IF_IN_JSON(j, "windowTitle", m_database.SetWindowTitle);
	CALL_STR_SET_FUNC_IF_IN_JSON(j, "gameTitle", m_database.SetGameTitle);
	CALL_STR_SET_FUNC_IF_IN_JSON(j, "saveFileTitle", m_baseSettings.SetSaveFileTitle);
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

	m_maps.Init(m_fw);
	m_animations.Init(m_fw);
	m_database.Init(m_fw);
	m_gameLayout.Init(m_fw);

	m_recollectionEvents.Init(m_fw);

	m_interOpData.Init(m_fw);
	m_storySettings.Init(m_fw);
	m_baseSettings.Init(m_fw);

	m_resources.Init(m_fw);

	if (m_fw.IsEndOfFile())
		std::cout << "Successfully parsed the entire project file" << std::endl;
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

	m_maps.Dump(fw);
	m_animations.Dump(fw);
	m_database.Dump(fw);
	m_gameLayout.Dump(fw);

	m_recollectionEvents.Dump(fw);

	m_interOpData.Dump(fw);
	m_storySettings.Dump(fw);
	m_baseSettings.Dump(fw);
	m_resources.Dump(fw);
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
		fw.WriteArr(m_resources.GetUnknown());

	m_maps.Dump(fw);
	m_animations.Dump(fw);
	m_database.Dump(fw);
	m_gameLayout.Dump(fw);

	m_recollectionEvents.Dump(fw);

	m_interOpData.Dump(fw);
	m_storySettings.Dump(fw);

	m_resources.DumpProj(fw);
	m_baseSettings.Dump(fw);
}
