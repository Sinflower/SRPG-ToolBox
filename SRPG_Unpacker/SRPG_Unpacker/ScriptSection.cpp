/*
 *  File: ScriptSection.cpp
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

#include "ScriptSection.h"

#include "SectionNames.h"

ScriptSection::ScriptSection() :
	SectionBase()
{
}

void ScriptSection::Init(FileReader *pFileReader, const bool &present, const bool &matPresent, std::deque<SecInfo> &secInfos)
{
	m_matPresent = matPresent;
	Config.Add(MAT_PRESENT, m_matPresent);
	// Call the base class Init
	SectionBase::Init(pFileReader, present, secInfos);
}

std::vector<uint32_t> ScriptSection::SecSizes() const
{
	uint32_t size = 0;

	size += 4; // Element count

	for (const ScriptData &data : m_data)
		size += data.Size();

	if (m_matPresent)
	{
		size += 4; // Material count

		for (const MaterialData &data : m_matData)
			size += data.Size();
	}

	return { size };
}

void ScriptSection::build(const std::wstring &inputFolder)
{
	for (const auto &[secIdx, cnt] : m_secElemCnt)
	{
		for (uint32_t i = 0; i < cnt; i++)
			m_data.push_back(ScriptData(inputFolder, secIdx));
	}

	m_matPresent = Config.Get<bool>(MAT_PRESENT);

	SecMap matSecElemCnt = Config.Get<SecMap>(MAT_SEC_NAME);
	if (matSecElemCnt.empty())
		return;

	const uint32_t matSecIdx = static_cast<uint32_t>(SECTION_NAMES.size() - 1);
	const uint32_t matCnt    = matSecElemCnt[matSecIdx];

	for (uint32_t i = 0; i < matCnt; i++)
		m_matData.push_back(MaterialData(inputFolder, matSecIdx));
}

void ScriptSection::loadSections(std::deque<SecInfo> &secInfos)
{
	SecInfo secInfo = secInfos.front();
	secInfos.pop_front();

	const uint32_t &offset = secInfo.second;

	if (offset != m_pFileReader->GetOffset())
		throw std::runtime_error(std::format("[ScriptSection] Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

	uint32_t startOffset  = m_pFileReader->GetOffset();
	uint32_t elementCount = m_pFileReader->ReadUInt32();

	m_secElemCnt[secInfo.first] = elementCount;

	for (uint32_t elem = 0; elem < elementCount; elem++)
		m_data.push_back(ScriptData(m_pFileReader, secInfo.first));

	if (m_matPresent)
		loadMaterials();
}

void ScriptSection::unpack(const std::wstring &outputFolder) const
{
	for (const ScriptData &data : m_data)
		data.Unpack(outputFolder);

	for (const MaterialData &data : m_matData)
		data.Unpack(outputFolder);

	if (!m_matData.empty())
	{
		SecMap matSecElemCnt;
		matSecElemCnt[static_cast<uint32_t>(SECTION_NAMES.size() - 1)] = static_cast<uint32_t>(m_matData.size());
		Config.Add(MAT_SEC_NAME, matSecElemCnt);
	}
}

void ScriptSection::writeSections(FileWriter &fileWriter) const
{
	for (const auto &[secIdx, cnt] : m_secElemCnt)
	{
		fileWriter.Write<uint32_t>(cnt);

		for (const ScriptData &data : m_data)
			data.Pack(fileWriter);
	}

	if (m_matPresent)
		writeMaterials(fileWriter);
}

void ScriptSection::loadMaterials()
{
	uint32_t matCount = m_pFileReader->ReadUInt32();

	if (matCount != 0x0)
	{
		for (uint32_t elem = 0; elem < matCount; elem++)
			m_matData.push_back(MaterialData(m_pFileReader, static_cast<uint32_t>(SECTION_NAMES.size() - 1)));
	}
}

void ScriptSection::writeMaterials(FileWriter &fileWriter) const
{
	fileWriter.Write<uint32_t>(static_cast<uint32_t>(m_matData.size()));

	for (const MaterialData &data : m_matData)
		data.Pack(fileWriter);
}