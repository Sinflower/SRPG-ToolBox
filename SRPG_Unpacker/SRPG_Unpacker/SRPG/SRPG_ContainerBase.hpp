/*
 *  File: SRPG_ContainerBase.hpp
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

#pragma once

#include "../FileAccess.h"
#include "../MemData.h"
#include <filesystem>

class CMenuOperation;

#define CHECK_OBJ_AND_WRITE_JSON_FILE(_OBJ_, _OUT_PATH_, _FILE_NAME_) \
	if (_OBJ_ != nullptr)                                             \
		_OBJ_->WriteToJsonFile(_OUT_PATH_, _FILE_NAME_);

class SRPG_ContainerBase
{
protected:
	// TODO: Remove this
	static inline const std::wstring COMMONS_PATCH_FOLDER = L"commons";

	static inline const std::wstring BASE_SETTINGS_FOLDER = L"Base";
	static inline const std::wstring LAYOUTS_FOLDER       = L"CommandLayout";
	static inline const std::wstring EXTRA_FOLDER         = L"Extra";
	static inline const std::wstring WEAPON_TYPES_FOLDER  = L"WeaponTypes";

public:
	SRPG_ContainerBase() {}
	virtual ~SRPG_ContainerBase() {}
	virtual void Init(FileReader& fw)       = 0;
	virtual void Dump(FileWriter& fw) const = 0;

	// By default, DumpProj calls Dump
	virtual void DumpProj(FileWriter& fw) const
	{
		Dump(fw);
	}

	virtual void WritePatches(const std::filesystem::path& outPath) const = 0;

	static std::filesystem::path CommonsPath(const std::filesystem::path& basePath);
	static std::filesystem::path BaseSettingsPath(const std::filesystem::path& basePath);
	static std::filesystem::path LayoutsPath(const std::filesystem::path& basePath);
	static std::filesystem::path ExtraPath(const std::filesystem::path& basePath);
	static std::filesystem::path WeaponTypesPath(const std::filesystem::path& basePath);

private:
	static std::filesystem::path buildFolder(const std::filesystem::path& basePath, const std::wstring& folder);
};
