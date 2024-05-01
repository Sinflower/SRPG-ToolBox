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
		EncryptData(dat);

	fileWriter.WriteBytesVec(dat);
}

void ProjectData::loadData()
{
	m_name = SECTION_NAME;
	m_data.push_back(InitMemData<uint32_t>(*m_pFileReader, m_pFileReader->Remaining(), false));
}

void ProjectData::buildData(const std::wstring &inputFolder)
{
	m_name = SECTION_NAME;

	const std::wstring filePath = std::format(L"{}/{}", inputFolder, m_name.ToWString());

	if (!fs::exists(filePath))
		throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));

	m_data.push_back(MemData<uint32_t>(filePath, static_cast<uint32_t>(fs::file_size(filePath))));
}