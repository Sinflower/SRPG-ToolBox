/*
 *  File: DataBase.cpp
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

#include "DataBase.h"

#include <filesystem>
#include <format>

#include "ConfigManager.h"
#include "Crypt.h"
#include "SectionNames.h"
#include "Utils.h"

namespace fs = std::filesystem;

void DataBase::Unpack(const std::wstring &outputFolder) const
{
	const std::wstring dirPath = buildOutDir(outputFolder);

	if (!fs::exists(dirPath))
		fs::create_directories(dirPath);

	uint32_t subElemIdx = 0;

	for (const MemData<uint32_t> &data : m_data)
	{
		std::vector<uint8_t> dat(data.size, 0);
		m_pFileReader->ReadBytesVecAt(dat, data.offset, data.size);

		if (m_decrypt)
			DecryptData(dat);

		std::wstring fileName = m_name.ToWString();
		std::wstring ext      = L"";

		// Check if the file already has an extension
		if (fs::path(fileName).extension().empty())
			ext = GetFileExtension(dat);

		fileName                    = std::format(L"{}{}{}", fileName, (subElemIdx == 0 ? L"" : std::format(L"-{}", wchar_t(0x60 + subElemIdx))), ext);
		const std::wstring filePath = std::format(L"{}{}", dirPath, fileName);

		if (subElemIdx == 0)
			add2Config(fs::path(fileName));

		if (!fs::exists(fs::path(filePath).parent_path()))
			fs::create_directories(fs::path(filePath).parent_path());

		write2File(filePath, dat);
		subElemIdx++;
	}
}

void DataBase::Pack(FileWriter &fileWriter) const
{
	if (m_data.empty())
		return;

	fileWriter.Write<uint32_t>(m_name.size);
	fileWriter.WriteBytesVec(m_name.data);

	fileWriter.Write<uint32_t>(m_reserved0);
	fileWriter.Write<uint32_t>(m_reserved1);
	fileWriter.Write<uint32_t>(m_subElemCount);

	for (const MemData<uint32_t> &data : m_data)
		fileWriter.Write<uint32_t>(data.size);

	for (const MemData<uint32_t> &data : m_data)
	{
		std::vector<uint8_t> dat(data.size, 0);

		// Read the file associated with data from disk
		readFromFile(data.fileName, dat);

		if (m_decrypt)
			EncryptData(dat);

		fileWriter.WriteBytesVec(dat);
	}
}

uint32_t DataBase::Size() const
{
	uint32_t size = 0;
	size += 4;                  // Name size
	size += m_name.size;        // Name data
	size += 4;                  // Reserved 0
	size += 4;                  // Reserved 1
	size += 4;                  // Sub element count
	size += m_subElemCount * 4; // Sub element sizes

	for (const MemData<uint32_t> &data : m_data)
		size += data.size;

	return size;
}

std::wstring DataBase::buildOutDir(const std::wstring &outputFolder) const
{
	return std::format(L"{}/{}/", outputFolder, (m_idx == -1 ? L"" : s2ws(SECTION_NAMES[m_idx])));
}

void DataBase::add2Config(const fs::path &file) const
{
	if (m_idx == -1) return;

	Config.Add2Array(SECTION_NAMES[m_idx], file.filename().wstring(), { m_reserved0, m_reserved1, m_subElemCount });
}

void DataBase::write2File(const std::wstring &filePath, const std::vector<uint8_t> &data) const
{
	std::ofstream outFile(filePath, std::ofstream::binary);

	outFile.write((const char *)data.data(), data.size());
	outFile.close();
}

void DataBase::readFromFile(const std::wstring &filePath, std::vector<uint8_t> &data) const
{
	std::ifstream inFile(filePath, std::ifstream::binary);

	if (!inFile.is_open())
		throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

	inFile.seekg(0, inFile.end);
	std::size_t size = inFile.tellg();
	inFile.seekg(0, inFile.beg);

	if (data.empty())
		data.resize(size, 0);
	else if (size != data.size())
		throw std::runtime_error(std::format("File size mismatch: {} - Got: {} - Expected: {}", ws2s(filePath), size, data.size()));

	inFile.read(reinterpret_cast<char *>(data.data()), size);
	inFile.close();
}

void DataBase::loadData()
{
	InitMemData<uint32_t>(m_name, *m_pFileReader);
	m_reserved0    = m_pFileReader->ReadUInt32();
	m_reserved1    = m_pFileReader->ReadUInt32();
	m_subElemCount = m_pFileReader->ReadUInt32();

	for (uint32_t i = 0; i < m_subElemCount; i++)
		m_dataSizes.push_back(m_pFileReader->ReadUInt32());

	for (const uint32_t dataSize : m_dataSizes)
		m_data.push_back(InitMemData<uint32_t>(*m_pFileReader, dataSize, false));
}

void DataBase::buildData(const std::wstring &inputFolder)
{
	const std::wstring dirPath     = std::format(L"{}/{}", inputFolder, s2ws(SECTION_NAMES[m_idx]));
	const nlohmann::ordered_json j = Config.GetNext(SECTION_NAMES[m_idx]);

	if (j.empty()) return;

	const std::string file = j["name"].get<std::string>();
	std::wstring ext       = s2ws(fs::path(file).extension().string());

	m_name         = s2ws(fs::path(file).stem().string());
	m_reserved0    = j["elems"][0].get<uint32_t>();
	m_reserved1    = j["elems"][1].get<uint32_t>();
	m_subElemCount = j["elems"][2].get<uint32_t>();

	m_dataSizes.clear();

	for (uint32_t i = 0; i < m_subElemCount; i++)
	{
		const std::wstring name     = std::format(L"{}{}", m_name.ToWString(), (i == 0 ? L"" : std::format(L"-{}", wchar_t(0x60 + i))));
		const std::wstring basePath = std::format(L"{}/{}", dirPath, name);
		std::wstring filePath       = std::format(L"{}{}", basePath, ext);
		// If the file does not exist, try to find it with a different extension
		if (!fs::exists(filePath))
		{
			std::wcout << std::format(L"File not found: {} - Trying to find it with a different extension ...", filePath) << std::endl;

			ext = L"";
			for (const auto &entry : fs::directory_iterator(dirPath))
			{
				if (entry.path().filename().stem().wstring() == name)
				{
					std::cout << std::format("Found file: {}", ws2s(entry.path().wstring())) << std::endl;
					ext = entry.path().extension().wstring();
					break;
				}
			}

			if (ext.empty())
				throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));
			else
				filePath = std::format(L"{}{}", basePath, ext);
		}

		m_data.push_back(MemData<uint32_t>(filePath, static_cast<uint32_t>(fs::file_size(filePath))));
	}
}

// TODO: Find a way to handle this without reading the entire file, but probably not possible
//       fs::file_size() * 2 does not return the correct size for this type of file
uint32_t DataBase::getFileSizeUTF16(const std::wstring &filePath) const
{
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wifstream file(filePath, std::ios::in | std::ios::binary);

	if (file.fail())
		throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

	file.imbue(utf8_locale);
	std::wstringstream buffer;
	buffer << file.rdbuf();

	buffer.seekg(0, std::ios::end);
	std::size_t size = buffer.tellg() * 2;

	file.close();

	return static_cast<uint32_t>(size);
}