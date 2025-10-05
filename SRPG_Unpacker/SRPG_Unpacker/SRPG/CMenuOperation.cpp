/*
 *  File: CMenuOperation.cpp
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

#include "CMenuOperation.h"
#include "Classes/EDITDATA.h"
#include "Functions.h"

CMenuOperation::CMenuOperation(SRPGClasses const& type) :
	m_type(static_cast<uint32_t>(type))
{
}

CMenuOperation::CMenuOperation(DWORD const& type) :
	m_type(type)
{
}

CMenuOperation::~CMenuOperation()
{
	for (EDITDATA*& p : m_data)
		delete (p);
}

std::size_t CMenuOperation::GetElemCount() const
{
	return m_data.size();
}

void CMenuOperation::init(FileReader& fw)
{
	DWORD objCnt = fw.ReadDWord();

	for (DWORD i = 0; i < objCnt; i++)
	{
		// v9 points to the class object
		EDITDATA* pObj = createSRPGClass(m_type);
		pObj->id       = fw.ReadDWord();
		pObj->init(fw);

		m_data.push_back(pObj);
	}
}

void CMenuOperation::dump(FileWriter& fw) const
{
	fw.Write(static_cast<DWORD>(m_data.size()));

	for (const EDITDATA* p : m_data)
	{
		fw.Write(p->id);
		p->dump(fw);
	}
}

nlohmann::ordered_json CMenuOperation::ToJson() const
{
	nlohmann::ordered_json j;

	for (const EDITDATA* p : m_data)
	{
		const nlohmann::ordered_json data = p->ToJson();
		if (!data.empty())
			j.push_back(data);
	}

	return j;
}

void CMenuOperation::ToJson(nlohmann::ordered_json& json, const std::string& name) const
{
	nlohmann::ordered_json j = ToJson();
	if (!j.is_null() && !j.empty())
		json[name] = j;
}

void CMenuOperation::WriteToJsonFile(const std::filesystem::path& outPath, const std::wstring& name) const
{
	nlohmann::ordered_json j = ToJson();
	if (j.is_null() || j.empty())
		j = nlohmann::ordered_json::array();

	WriteJsonToFile(j, outPath, name);
}

void CMenuOperation::ApplyPatch(const std::filesystem::path& path, const std::wstring& name)
{
	nlohmann::ordered_json j = ReadJsonFromFile(path, name);
	if (j.is_null() || j.empty())
		return;

	applyPatch(j);
}

void CMenuOperation::ApplyPatch(const nlohmann::ordered_json& json)
{
	applyPatch(json);
}

void CMenuOperation::applyPatch(const nlohmann::ordered_json& json)
{
	if (json.is_array() && !json.empty() && !json[0].contains("id"))
	{
		// Make sure the array and data have the same size
		if (json.size() != m_data.size())
			throw std::runtime_error("CMenuOperation::applyPatch: JSON array size does not match data size");

		for (std::size_t i = 0; i < json.size(); i++)
			m_data[i]->ApplyPatch(json[i]);

		return;
	}

	for (const nlohmann::ordered_json& j : json)
	{
		if (!j.contains("id"))
			continue;
		const DWORD id = j["id"].get<DWORD>();

		auto it = std::find_if(m_data.begin(), m_data.end(), [id](const EDITDATA* p) { return p->id == id; });

		if (it != m_data.end())
			(*it)->ApplyPatch(j);
	}
}

std::ostream& operator<<(std::ostream& os, CMenuOperation const& dt)
{
	os << "CMenuOperation: " << dt.m_type << std::endl;
	for (const EDITDATA* p : dt.m_data)
		os << *p << std::endl;

	return os;
}

std::wostream& operator<<(std::wostream& os, CMenuOperation const& dt)
{
	os << L"CMenuOperation: " << dt.m_type << std::endl;
	for (const EDITDATA* p : dt.m_data)
		os << *p << std::endl;

	return os;
}

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const SRPGClasses& type, FileReader& fw)
{
	if (*ppCMenuOperation == nullptr)
		*ppCMenuOperation = new CMenuOperation(type);
	(*ppCMenuOperation)->init(fw);
}

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const DWORD& type, FileReader& fw)
{
	if (*ppCMenuOperation == nullptr)
		*ppCMenuOperation = new CMenuOperation(type);
	(*ppCMenuOperation)->init(fw);
}
