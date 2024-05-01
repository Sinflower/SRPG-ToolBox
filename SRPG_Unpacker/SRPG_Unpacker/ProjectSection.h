#pragma once

#include "ProjectData.h"
#include "SectionBase.h"

class ProjectSection : public SectionBase<ProjectData>
{
public:
	ProjectSection();

	void Init(FileReader *pFileReader, const uint32_t &offset);

	std::vector<uint32_t> SecSizes() const override;

protected:
	void build(const std::wstring &inputFolder) override;

	void loadSections(const uint32_t &offset);

	void writeSections(FileWriter &fileWriter) const override;
};