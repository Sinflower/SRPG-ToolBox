/*
 *  File: SRPG_Project.h
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

#pragma once

// Compatible up to v1.317

#include <windows.h>

#include <filesystem>
#include <nlohmann/json.hpp>
#include <vector>

#include "../FileAccess.h"

#include "SRPG_Animations.hpp"
#include "SRPG_BaseSettings.hpp"
#include "SRPG_Database.hpp"
#include "SRPG_GameLayout.hpp"
#include "SRPG_InterOpData.hpp"
#include "SRPG_Maps.hpp"
#include "SRPG_RecollectionEvents.hpp"
#include "SRPG_Resources.hpp"
#include "SRPG_StorySettings.hpp"

struct SRPG_ProjectData
{
	DWORD version = 0;
	DWORD resFlag = 0;
	std::vector<BYTE> data;
};

class SRPG_Project
{
public:
	static inline const std::wstring PROJECT_DAT_NAME  = L"project.dat";
	static inline const std::wstring PROJECT_FILE_NAME = L"project.srpgs";

public:
	SRPG_Project(const SRPG_ProjectData& projData);

	~SRPG_Project();

	void Dump(const std::filesystem::path& outPath) const;
	void DumpProj(const std::filesystem::path& outPath) const;
	void SetupInternalResources(const nlohmann::ordered_json& json);

	nlohmann::ordered_json GetResMapping() const;

	void WritePatch(const std::filesystem::path& outPath) const;
	void ApplyPatch(const std::filesystem::path& patchPath);

private:
	void loadProject();

	void dump(FileWriter& fw) const;
	void dumpAsProj(FileWriter& fw) const;

private:
	FileReader m_fw;

	SRPG_Maps m_maps                             = {};
	SRPG_Animations m_animations                 = {};
	SRPG_Database m_database                     = {};
	SRPG_GameLayout m_gameLayout                 = {};
	SRPG_RecollectionEvents m_recollectionEvents = {};
	SRPG_InterOpData m_interOpData               = {};
	SRPG_StorySettings m_storySettings           = {};
	SRPG_BaseSettings m_baseSettings             = {};
	SRPG_Resources m_resources; // This is initialized by the constructor as it needs the resFlag

	DWORD res1 = 0;
	DWORD res2 = 0;

	DWORD this_1 = 0;
	DWORD this_2 = 0;
	DWORD this_3 = 0;
	DWORD this_4 = 0;
};
