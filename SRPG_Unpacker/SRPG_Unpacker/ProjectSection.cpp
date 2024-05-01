#include "ProjectSection.h"

#include <format>

ProjectSection::ProjectSection() :
	SectionBase()
{
}

void ProjectSection::Init(FileReader *pFileReader, const uint32_t &offset)
{
	m_pFileReader = pFileReader;
	loadSections(offset);
}

std::vector<uint32_t> ProjectSection::SecSizes() const
{
	uint32_t size = 0;

	if (!m_data.empty())
		size = m_data.front().Size();

	return { size };
}

void ProjectSection::build(const std::wstring &inputFolder)
{
	m_data.push_back(ProjectData(inputFolder));
}

void ProjectSection::loadSections(const uint32_t &offset)
{
	if (offset != m_pFileReader->GetOffset())
		throw std::runtime_error(std::format("[ProjectSection] Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

	m_data.push_back(ProjectData(m_pFileReader));
}

void ProjectSection::writeSections(FileWriter &fileWriter) const
{
	if (m_data.empty())
		return;

	m_data.front().Pack(fileWriter);
}