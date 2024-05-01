#pragma once
#include "DataBase.h"

class ProjectData : public DataBase
{
	inline static const std::wstring SECTION_NAME = L"project.dat";

public:
	ProjectData(FileReader *pFileReader, [[maybe_unused]] const uint32_t idx = -1);

	ProjectData(const std::wstring &inputFolder, const uint32_t &idx = -1);

	void Pack(FileWriter &fileWriter) const override;

protected:
	void loadData() override;

	void buildData(const std::wstring &inputFolder) override;
};