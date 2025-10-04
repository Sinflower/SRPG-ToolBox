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

std::filesystem::path SRPG_ContainerBase::CommonsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, COMMONS_PATCH_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::BaseSettingsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, BASE_SETTINGS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::LayoutsPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, LAYOUTS_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::ExtraPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, EXTRA_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::WeaponTypesPath(const std::filesystem::path& basePath)
{
	return buildFolder(basePath, WEAPON_TYPES_FOLDER);
}

std::filesystem::path SRPG_ContainerBase::buildFolder(const std::filesystem::path& basePath, const std::wstring& folder)
{
	const std::filesystem::path p = basePath / folder;

	if (!std::filesystem::exists(p))
		std::filesystem::create_directories(p);

	return p;
}
