#pragma once
#include "DataBase.h"

class MaterialData : public DataBase
{
public:
	MaterialData(FileReader *pFileReader, const uint32_t idx = -1);

	MaterialData(const std::wstring &inputFolder, const uint32_t &idx);

	void Pack(FileWriter &fileWriter) const override;

	uint32_t Size() const override;

protected:
	void add2Config(const std::filesystem::path &file) const override;

	void loadData() override;

	void buildData(const std::wstring &inputFolder) override;
};