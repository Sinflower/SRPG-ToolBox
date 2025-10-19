/*
 *  File: DataBase.h
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

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "MemData.h"
#include "Types.h"

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

	std::vector<uint8_t> GetData(const std::size_t &idx) const;

protected:
	std::vector<uint8_t> getData(const MemData &data) const;

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

	MemData m_name          = {};
	uint32_t m_reserved0    = 0;
	uint32_t m_reserved1    = 0;
	uint32_t m_subElemCount = 0;

	std::vector<uint32_t> m_dataSizes = {};
	MemDataVec m_data                 = {};
};
