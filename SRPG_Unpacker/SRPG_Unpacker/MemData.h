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

namespace memData
{
static bool g_isUTF8 = true;

static inline std::string sjis2utf8(const std::string& sjis)
{
	std::string utf8String = "";

	LPCCH pSJIS             = sjis.c_str();
	const int32_t utf16Size = ::MultiByteToWideChar(932, MB_ERR_INVALID_CHARS, pSJIS, -1, 0, 0);
	if (utf16Size != 0)
	{
		LPWSTR pUTF16 = new WCHAR[utf16Size];
		if (::MultiByteToWideChar(932, 0, pSJIS, -1, pUTF16, utf16Size) != 0)
		{
			const int32_t utf8Size = ::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, 0, 0, 0, 0);
			if (utf8Size != 0)
			{
				LPSTR pUTF8 = new CHAR[utf8Size + 16];
				ZeroMemory(pUTF8, utf8Size + 16);
				if (::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, pUTF8, utf8Size, 0, 0) != 0)
					utf8String = std::string(pUTF8);

				delete[] pUTF8;
			}
		}

		delete[] pUTF16;
	}

	return utf8String;
}

static inline std::string utf82sjis(const std::string& utf8)
{
	std::string sjisString = "";

	LPCCH pUTF8             = utf8.c_str();
	const int32_t utf16Size = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pUTF8, -1, 0, 0);
	if (utf16Size != 0)
	{
		LPWSTR pUTF16 = new WCHAR[utf16Size];
		if (::MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, pUTF16, utf16Size) != 0)
		{
			const int32_t sjisSize = ::WideCharToMultiByte(932, 0, pUTF16, -1, 0, 0, 0, 0);
			if (sjisSize != 0)
			{
				LPSTR pSJIS = new CHAR[sjisSize + 16];
				ZeroMemory(pSJIS, sjisSize + 16);
				if (::WideCharToMultiByte(932, 0, pUTF16, -1, pSJIS, sjisSize, 0, 0) != 0)
					sjisString = std::string(pSJIS);

				delete[] pSJIS;
			}
		}

		delete[] pUTF16;
	}

	return sjisString;
}
} // namespace memData

template<typename T>
struct MemData
{
	std::vector<BYTE> data = {};
	T size                 = 0;
	uint32_t offset        = 0;
	bool readSize          = false;
	std::wstring fileName  = L"";

	MemData() = default;

	MemData(const std::wstring& fileName, const T& size) :
		fileName(fileName),
		size(size)
	{
	}

	std::string ToString() const
	{
		std::string str = "";

		if (!data.empty() && data.size() > 1)
			str = std::string(reinterpret_cast<const char*>(data.data()), data.size() - ((data.back() == 0x0) ? 1 : 0));

		if (!memData::g_isUTF8)
			str = memData::sjis2utf8(str);

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
		std::string s = str;
		if (!memData::g_isUTF8)
			s = memData::utf82sjis(str);

		size = static_cast<T>(s.size()) + 1;
		data.resize(size);
		std::copy(s.begin(), s.end(), data.begin());

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
		size = static_cast<T>(str.size() * 2) + 2;
		data.resize(size);
		std::copy(str.begin(), str.end(), reinterpret_cast<wchar_t*>(data.data()));

		data.back() = 0x0;
	}

	friend std::ostream& operator<<(std::ostream& os, MemData const& md)
	{
		os << md.toString();

		return os;
	}
};

template<typename T>
void InitMemData(MemData<T>& memData, FileReader& fw, const T& size = ~0, const bool& loadData = true)
{
	memData.offset = fw.GetOffset();

	if (size == static_cast<T>(~0))
	{
		if (sizeof(T) == 1)
			memData.size = fw.ReadUInt8();
		else if (sizeof(T) == 2)
			memData.size = fw.ReadUInt16();
		else if (sizeof(T) == 4)
			memData.size = static_cast<T>(fw.ReadUInt32());
		memData.readSize = true;
		memData.offset += sizeof(T);
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

template<typename T>
MemData<T> InitMemData(FileReader& fw, const T& size = ~0, const bool& loadData = true)
{
	MemData<T> memData;
	InitMemData(memData, fw, size, loadData);

	return memData;
}

template<typename T>
MemData<T> InitFromData(const std::string& str, const bool& readSize = true)
{
	MemData<T> memData;
	memData.fromString(str);
	memData.readSize = readSize;

	return memData;
}

template<typename T>
using MemDataVec = std::vector<MemData<T>>;