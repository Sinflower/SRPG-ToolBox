#pragma once
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "MemData.h"

class DataBase
{
public:
	DataBase(FileReader *pFileReader, const uint32_t &idx = -1) :
		m_pFileReader(pFileReader),
		m_idx(idx)
	{
	}

	DataBase(const uint32_t &idx) :
		m_idx(idx)
	{
	}

	virtual ~DataBase() = default;

	void Unpack(const std::wstring &outputFolder) const;

	virtual void Pack(FileWriter &fileWriter) const;

	virtual uint32_t Size() const;

protected:
	virtual std::wstring buildOutDir(const std::wstring &outputFolder) const;

	virtual void add2Config(const std::filesystem::path &file) const;

	virtual void write2File(const std::wstring &filePath, const std::vector<uint8_t> &data) const;

	virtual void readFromFile(const std::wstring &filePath, std::vector<uint8_t> &data) const;

	virtual void loadData();

	virtual void buildData(const std::wstring &inputFolder);

	uint32_t getFileSizeUTF16(const std::wstring &filePath) const;

protected:
	FileReader *m_pFileReader = nullptr;
	uint32_t m_idx            = 0;
	bool m_decrypt            = true;

	MemData<uint32_t> m_name = {};
	uint32_t m_reserved0     = 0;
	uint32_t m_reserved1     = 0;
	uint32_t m_subElemCount  = 0;

	std::vector<uint32_t> m_dataSizes = {};
	MemDataVec<uint32_t> m_data       = {};
};
