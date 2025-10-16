/*
 *  File: SRPG_Resources.cpp
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

#include "SRPG_Resources.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

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

nlohmann::ordered_json SRPG_Resources::GetResMapping() const
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

	if (m_resFlags.HasVideoData && g_ArcVersion >= VIDEO_RESOURCE_ADD_VERSION)
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
			std::string name = v["name"].get<std::string>();

			// Get the number of the object
			uint32_t id = v["id"].get<uint32_t>();

			// Add the object to the new json
			j3[std::to_string(id)] = name;
		}

		// Add the object to the new json
		j2[key] = j3;
	}

	// Write j2 to a file for debugging
	// std::ofstream ofs("res_mapping.json");
	// ofs << j2.dump(4);
	// ofs.close();

	return j2;
}

void SRPG_Resources::InitInternalResourceData(const nlohmann::ordered_json& json)
{
	uint32_t secIdx      = 0;
	uint32_t secSubCount = 0;

	if (!m_resFlags.HasResData)
	{
		for (CMenuOperation*& pResData : m_resData)
			allocAndSetCMenuOp(&pResData, SRPGClasses::RESDATA, getJsonResSection(json, secIdx++, secSubCount));
	}

	secSubCount = secIdx;

	if (!m_resFlags.HasUIResData)
	{
		for (CMenuOperation*& pUiRes : m_uIResData)
			allocAndSetCMenuOp(&pUiRes, SRPGClasses::UIRESDATA, getJsonResSection(json, secIdx++, secSubCount));
	}

	secSubCount = secIdx;

	if (!m_resFlags.HasMediaData)
	{
		for (CMenuOperation*& pMediaData : m_mediaData)
			allocAndSetCMenuOp(&pMediaData, SRPGClasses::MEDIADATA, getJsonResSection(json, secIdx++, secSubCount));
	}

	secSubCount = secIdx;

	if (!m_resFlags.HasFontData)
		allocAndSetCMenuOp(&m_pInstalledFontData, SRPGClasses::INSTALLEDFONTDATA, getJsonResSection(json, secIdx++, secSubCount));

	secSubCount = secIdx;

	if (!m_resFlags.HasVideoData && g_ArcVersion >= VIDEO_RESOURCE_ADD_VERSION)
		allocAndSetCMenuOp(&m_pVideoData, SRPGClasses::VIDEODATA, getJsonResSection(json, secIdx++, secSubCount));
}

void SRPG_Resources::init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __func__ << " START ====" << std::endl;
	std::cout << std::hex << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	// NOTE: I don't know when this was added, but I know it was not
	//       present in this version
	if (g_ArcVersion > 0x4CA)
		fw.ReadBytes(m_unknown.data(), static_cast<DWORD>(m_unknown.size() * sizeof(DWORD)));

#ifdef DEBUG_PRINT
	std::cout << "OFFSET-UNKNOWN=" << fw.GetOffset() << std::endl;
#endif

	if (m_resFlags.HasResData)
	{
		for (CMenuOperation*& pResData : m_resData)
			allocAndSetCMenuOp(&pResData, SRPGClasses::RESDATA, fw);

#ifdef DEBUG_PRINT
		std::cout << "OFFSET-RESDATA=" << fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasUIResData)
	{
		for (CMenuOperation*& pUiRes : m_uIResData)
			allocAndSetCMenuOp(&pUiRes, SRPGClasses::UIRESDATA, fw);

#ifdef DEBUG_PRINT
		std::cout << "OFFSET-UIRESDATA=" << fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasMediaData)
	{
		for (CMenuOperation*& pMediaData : m_mediaData)
			allocAndSetCMenuOp(&pMediaData, SRPGClasses::MEDIADATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-MEDIADATA=" << fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasFontData)
	{
		allocAndSetCMenuOp(&m_pInstalledFontData, SRPGClasses::INSTALLEDFONTDATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-INSTALLEDFONTDATA=" << fw.GetOffset() << std::endl;
#endif
	}

	if (m_resFlags.HasVideoData && g_ArcVersion >= VIDEO_RESOURCE_ADD_VERSION)
	{
		allocAndSetCMenuOp(&m_pVideoData, SRPGClasses::VIDEODATA, fw);
#ifdef DEBUG_PRINT
		std::cout << "OFFSET-VIDEODATA=" << fw.GetOffset() << std::endl;
#endif
	}

	if (g_ArcVersion >= 0x475)
	{
		for (CMenuOperation*& pCID : m_classIDData)
			allocAndSetCMenuOp(&pCID, SRPGClasses::CLASSIDDATA, fw);
	}

#ifdef DEBUG_PRINT
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;

	std::cout << "==== Method END ====" << std::dec << std::endl;
#endif
}

void SRPG_Resources::dump(FileWriter& fw) const
{
	// NOTE: I don't know when this was added, but I know it was not
	//       present in this version
	if (g_ArcVersion > 0x4CA)
		fw.WriteBytes(m_unknown.data(), m_unknown.size() * sizeof(DWORD));

	if (m_resFlags.HasResData)
	{
		for (const CMenuOperation* pResData : m_resData)
			pResData->Dump(fw);
	}

	if (m_resFlags.HasUIResData)
	{
		for (const CMenuOperation* pUiRes : m_uIResData)
			pUiRes->Dump(fw);
	}

	if (m_resFlags.HasMediaData)
	{
		for (const CMenuOperation* pMediaData : m_mediaData)
			pMediaData->Dump(fw);
	}

	if (m_resFlags.HasFontData)
		m_pInstalledFontData->Dump(fw);

	if (m_resFlags.HasVideoData && g_ArcVersion >= VIDEO_RESOURCE_ADD_VERSION)
		m_pVideoData->Dump(fw);

	if (g_ArcVersion >= 0x475)
	{
		for (const CMenuOperation* pCID : m_classIDData)
			pCID->Dump(fw);
	}
}

void SRPG_Resources::dumpProj(FileWriter& fw) const
{
	for (const CMenuOperation* pResData : m_resData)
		pResData->Dump(fw);

	for (const CMenuOperation* pMediaData : m_mediaData)
		pMediaData->Dump(fw);

	for (const CMenuOperation* pUiRes : m_uIResData)
		pUiRes->Dump(fw);

	m_pInstalledFontData->Dump(fw);

	m_pVideoData->Dump(fw);

	if (g_ArcVersion >= 0x475)
	{
		for (const CMenuOperation* pCID : m_classIDData)
			pCID->Dump(fw);
	}
}

void SRPG_Resources::writePatches(const std::filesystem::path& outPath) const
{
}

nlohmann::ordered_json SRPG_Resources::getJsonResSection(const nlohmann::ordered_json& json, const uint32_t& secIdx, const uint32_t& secReduce)
{
	const std::string& secName = SECTION_NAMES[secIdx];
	if (!json.contains(secName) || !json[secName].is_array())
		return nlohmann::ordered_json();

	nlohmann::ordered_json j = json[secName];

	// Add the section index to each element in the array
	for (auto& elem : j)
		elem["section_idx"] = secIdx - secReduce;

	return j;
}
