#pragma once
#include "DataBase.h"

class ScriptData : public DataBase
{
public:
	ScriptData(FileReader *pFileReader, const uint32_t idx = -1);

	ScriptData(const std::wstring &inputFolder, const uint32_t &idx);

	void Pack(FileWriter &fileWriter) const override;

	uint32_t Size() const override;

protected:
	std::wstring buildOutDir(const std::wstring &outputFolder) const override;

	void add2Config(const std::filesystem::path &file) const override;

	void write2File(const std::wstring &filePath, const std::vector<uint8_t> &data) const override;

	void readFromFile(const std::wstring &filePath, std::vector<uint8_t> &data) const override;

	void loadData() override;

	void buildData(const std::wstring &inputFolder) override;

private:
	bool isPlugin() const;

	std::wstring getFolderName() const;
};
