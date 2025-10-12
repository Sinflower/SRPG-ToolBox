/*
 *  File: ProjectData.cpp
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

#include "ProjectData.h"

#include <filesystem>
#include <format>

#include "Crypt.h"
#include "Utils.h"

namespace fs = std::filesystem;

ProjectData::ProjectData(FileReader *pFileReader, [[maybe_unused]] const uint32_t idx) :
	DataBase(pFileReader, idx)
{
	loadData();
}

ProjectData::ProjectData(const std::wstring &inputFolder, const uint32_t &idx) :
	DataBase(idx)
{
	buildData(inputFolder);
}

void ProjectData::Pack(FileWriter &fileWriter) const
{
	if (m_data.empty())
		return;

	std::vector<uint8_t> dat;

	// Read the file associated with data from disk
	readFromFile(m_data.front().fileName, dat);

	if (m_decrypt)
		Crypt::EncryptData(dat);

	fileWriter.WriteBytesVec(dat);
}

void ProjectData::loadData()
{
	m_name = SECTION_NAME;
	m_data.push_back(InitMemData(*m_pFileReader, m_pFileReader->Remaining(), false));
}

void ProjectData::buildData(const std::wstring &inputFolder)
{
	m_name = SECTION_NAME;

	const std::wstring filePath = std::format(L"{}/{}", inputFolder, m_name.ToWString());

	if (!fs::exists(filePath))
		throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));

	m_data.push_back(MemData(filePath, static_cast<uint32_t>(fs::file_size(filePath))));
}