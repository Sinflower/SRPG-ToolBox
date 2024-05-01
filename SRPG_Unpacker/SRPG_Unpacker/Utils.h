/*
 *  File: Utils.h
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
#include <codecvt>
#include <string>
#include <vector>

static inline std::wstring s2ws(const std::string &str)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
}

static inline std::string ws2s(const std::wstring &wstr)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

static inline uint32_t SumVector(const std::vector<uint32_t> &vec)
{
	uint32_t sum = 0;
	for (auto &v : vec)
		sum += v;

	return sum;
}

struct FileExt
{
	FileExt(const std::vector<uint8_t> &header, const uint32_t &offset, const std::wstring &ext) :
		header(header),
		offset(offset),
		ext(ext)
	{
	}

	FileExt(const std::vector<uint8_t> &header, const std::wstring &ext) :
		header(header),
		offset(0),
		ext(ext)
	{
	}

	std::vector<uint8_t> header;
	uint32_t offset;
	std::wstring ext;
};

static inline const std::vector<FileExt> FILE_HEADERS = {
	{ { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a }, L".png" },
	{ { 0x4F, 0x67, 0x67, 0x53 }, L".ogg" },
	{ { 0xFF, 0xD8, 0xFF, 0xE0 }, L".jpg" },
	{ { 0xFF, 0xD8, 0xFF, 0xE1 }, L".jpg" },
	{ { 0x38, 0x42, 0x50, 0x53 }, L".psd" },
	{ { 0x49, 0x44, 0x33 }, L".mp3" },
	{ { 0xFF, 0xFB }, L".mp3" },
	{ { 0xFF, 0xF3 }, L".mp3" },
	{ { 0xFF, 0xF2 }, L".mp3" },
	{ { 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D }, 4, L".mp4" },
	{ { 0x00, 0x01, 0x00, 0x00, 0x00 }, L".ttf" },
	{ { 0x4F, 0x54, 0x54, 0x4F }, L".otf" },
	{ { 0x57, 0x41, 0x56, 0x45 }, 8, L".wav" }
};

static inline std::wstring GetFileExtension(const std::vector<uint8_t> &data)
{
	for (const FileExt &header : FILE_HEADERS)
	{
		if (std::equal(header.header.begin(), header.header.end(), data.begin() + header.offset))
			return header.ext;
	}

	return L".txt";
}

static inline std::vector<std::wstring> SplitString(const std::wstring &str, const wchar_t &delim)
{
	std::vector<std::wstring> tokens;
	std::wistringstream ss(str);
	std::wstring token;

	while (std::getline(ss, token, delim))
		tokens.push_back(token);

	return tokens;
}

static inline std::wstring JoinString(const std::vector<std::wstring> &strs, const wchar_t &delim)
{
	std::wstring result;
	for (const std::wstring& str : strs)
		result += str + delim;

	return result;
}
