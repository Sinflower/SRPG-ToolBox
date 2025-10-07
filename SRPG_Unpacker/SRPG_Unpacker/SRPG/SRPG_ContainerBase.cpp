/*
 *  File: SRPG_ContainerBase.cpp
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

#include "SRPG_ContainerBase.hpp"
#include "CMenuOperation.h"
#include "Classes/NPCDATA.h"
#include "Classes/UNITDATA.h"

void SRPG_ContainerBase::Init(FileReader& fw)
{
	std::cout << "Initializing: " << m_name << " ... " << std::flush;
	init(fw);
	std::cout << "Done" << std::endl;
}

void SRPG_ContainerBase::Dump(FileWriter& fw) const
{
	std::cout << "Dumping: " << m_name << " ... " << std::flush;
	dump(fw);
	std::cout << "Done" << std::endl;
}

void SRPG_ContainerBase::DumpProj(FileWriter& fw) const
{
	dumpProj(fw);
}

void SRPG_ContainerBase::WritePatches(const std::filesystem::path& outPath) const
{
	std::cout << "Writing patches: " << m_name << " ... " << std::flush;
	writePatches(outPath);
	std::cout << "Done" << std::endl;
}

void SRPG_ContainerBase::ApplyPatches(const std::filesystem::path& patchPath)
{
	std::cout << "Applying patches: " << m_name << " ... " << std::flush;
	applyPatches(patchPath);
	std::cout << "Done" << std::endl;
}

std::filesystem::path SRPG_ContainerBase::CommonsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, COMMONS_PATCH_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::BaseSettingsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, BASE_SETTINGS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::CommandStringsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, COMMAND_STRS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::ExtraPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, EXTRA_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::LayoutsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, LAYOUTS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::MapsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, MAPS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::NPCSettingsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, NPC_SETTINGS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::ResourceLocationPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, RESOURCE_LOC_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::TerrainPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, TERRAIN_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::WeaponTypesPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, WEAPON_TYPES_FOLDER);
}

UnitNameMap SRPG_ContainerBase::buildUnitNameMap(const CMenuOperation* pObjs, const DWORD& npcIdOffset)
{
	UnitNameMap names;
	if (pObjs)
	{
		for (const auto* pObj : *pObjs)
		{
			const UNITDATA* pUnit = dynamic_cast<const UNITDATA*>(pObj);
			const NPCDATA* pNPC   = dynamic_cast<const NPCDATA*>(pObj);

			if (pUnit)
				names[pObj->id] = pUnit->name;
			else if (pNPC)
			{
				const DWORD id = (0x10000 * npcIdOffset) + pObj->id;
				names[id]      = pNPC->name;
			}
		}
	}
	return names;
}

std::filesystem::path SRPG_ContainerBase::buildFolder(const std::filesystem::path& basePath, const std::wstring& folder)
{
	const std::filesystem::path p = basePath / folder;

	if (!std::filesystem::exists(p))
		std::filesystem::create_directories(p);

	return p;
}
