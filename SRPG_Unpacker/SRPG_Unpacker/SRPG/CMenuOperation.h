/*
 *  File: CMenuOperation.h
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

#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "../FileAccess.h"
#include "../Types.h"
#include "SRPG_Types.h"

#define SET_STRING_IF_IN_JSON(_JSON_, _NAME_, _STR_)           \
	if (_JSON_.contains(_NAME_) && _JSON_[_NAME_].is_string()) \
		_STR_ = _JSON_[_NAME_].get<std::string>();

#define SET_FN_STRING_IF_IN_JSON(_JSON_, _NAME_, _STR_)        \
	if (_JSON_.contains(_NAME_) && _JSON_[_NAME_].is_string()) \
	{                                                          \
		std::string fn   = _JSON_[_NAME_].get<std::string>();  \
		std::wstring wFn = s2ws(fn);                           \
		std::filesystem::path p(wFn);                          \
		fn    = ws2s(p.stem().wstring());                      \
		_STR_ = fn;                                            \
	}

#define SET_DWORD_IF_IN_JSON(_JSON_, _NAME_, _DWORD_)                   \
	if (_JSON_.contains(_NAME_) && _JSON_[_NAME_].is_number_unsigned()) \
		_DWORD_ = _JSON_[_NAME_].get<DWORD>();

#define APPLY_PATCH_IF_IN_JSON(_JSON_, _NAME_, _OBJ_) \
	if (_JSON_.contains(_NAME_))                      \
		_OBJ_->ApplyPatch(_JSON_[_NAME_]);

class CMenuOperation
{
public:
	CMenuOperation(SRPGClasses const& type);
	CMenuOperation(DWORD const& type);
	~CMenuOperation();

	void Init(FileReader& fw);
	void Dump(FileWriter& fw) const;
	nlohmann::ordered_json ToJson() const;
	void ToJson(nlohmann::ordered_json& json, const std::string& name) const;

	template<typename T>
	void ToJson(nlohmann::ordered_json& json, const std::string& name, const T& def) const
	{
		ToJson(json, name);
		if (!json.contains(name))
			json[name] = def;
	}

	void InitFromJson(const nlohmann::ordered_json& json);

	void WriteToJsonFile(const std::filesystem::path& outPath, const std::wstring& name) const;

	void ApplyPatch(const std::filesystem::path& path, const std::wstring& name);
	void ApplyPatch(const nlohmann::ordered_json& json);

	std::size_t GetElemCount() const;
	friend std::ostream& operator<<(std::ostream& os, CMenuOperation const& dt);
	friend std::wostream& operator<<(std::wostream& os, CMenuOperation const& dt);

	// Methods required for range-based for loops
	auto begin()
	{
		return m_data.begin();
	}

	auto end()
	{
		return m_data.end();
	}

	auto cbegin() const
	{
		return m_data.cbegin();
	}

	auto cend() const
	{
		return m_data.cend();
	}

	const auto begin() const
	{
		return m_data.begin();
	}

	const auto end() const
	{
		return m_data.end();
	}

private:
	void applyPatch(const nlohmann::ordered_json& json);

private:
	std::vector<class EDITDATA*> m_data;
	DWORD m_type = 0;
};

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const SRPGClasses& type, FileReader& fw);
void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const DWORD& type, FileReader& fw);
void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const SRPGClasses& type, const nlohmann::ordered_json& json);