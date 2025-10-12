/*
 *  File: MemData.h
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

#include <Windows.h>
#include <fstream>
#include <vector>

#include "FileAccess.h"
#include "Utils.h"

struct MemData
{
	std::vector<BYTE> data = {};
	uint32_t size          = 0;
	uint32_t offset        = 0;
	bool readSize          = false;
	std::wstring fileName  = L"";

	MemData() = default;

	MemData(const std::wstring& fileName, const uint32_t& size) :
		fileName(fileName),
		size(size)
	{
	}

	std::string ToString() const
	{
		std::wstring wstr = ToWString();
		std::string str   = fileAccessUtils::ws2s(wstr);
		return str;
	}

	std::wstring ToWString() const
	{
		std::wstring str = L"";

		if (!data.empty() && data.size() > 2)
			str = std::wstring(reinterpret_cast<const wchar_t*>(data.data()), (data.size() / 2) - ((data.back() == 0x0) ? 1 : 0));

		return str;
	}

	void FromString(const std::string& str)
	{
		const std::wstring wstr = s2ws(str);
		FromWString(wstr);
	}

	void FromWString(const std::wstring& str)
	{
		if (str.empty())
		{
			size = 0;
			data.clear();
			return;
		}

		readSize = true;
		size = static_cast<uint32_t>(str.size() * 2) + 2;
		data.resize(size);
		std::fill(data.begin(), data.end(), 0x0);
		std::copy(str.begin(), str.end(), reinterpret_cast<wchar_t*>(data.data()));
		data.back() = 0x0;
	}

	void Write(FileWriter& fw) const
	{
		if (readSize)
			fw.Write(size);

		if (size > 0)
			fw.WriteBytesVec(data);
	}

	operator std::string() const
	{
		return ToString();
	}

	void operator=(const std::string& str)
	{
		FromString(str);
	}

	void operator=(const std::wstring& str)
	{
		FromWString(str);
	}

	friend std::ostream& operator<<(std::ostream& os, MemData const& md)
	{
		os << md.ToString();

		return os;
	}
};

inline void InitMemData(MemData& memData, FileReader& fw, const uint32_t& size = ~0, const bool& loadData = true)
{
	memData.offset = fw.GetOffset();

	if (size == static_cast<uint32_t>(~0))
	{
		memData.size     = static_cast<uint32_t>(fw.ReadUInt32());
		memData.readSize = true;
		memData.offset += sizeof(uint32_t);
	}
	else
		memData.size = size;

	if (memData.size && loadData)
	{
		memData.data.resize(memData.size);
		fw.ReadBytesVec(memData.data);
	}
	else
		fw.Skip(memData.size);
}

inline MemData InitMemData(FileReader& fw, const uint32_t& size = ~0, const bool& loadData = true)
{
	MemData memData;
	InitMemData(memData, fw, size, loadData);

	return memData;
}

inline MemData InitFromData(const std::string& str, const bool& readSize = true)
{
	MemData memData;
	memData.FromString(str);
	memData.readSize = readSize;

	return memData;
}

using MemDataVec = std::vector<MemData>;