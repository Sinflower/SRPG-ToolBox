/*
 *  File: FileHeader.h
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

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

#include "FileAccess.h"
#include "ProjectSection.h"
#include "ScriptSection.h"
#include "Sections.h"
#include "Types.h"

class FileHeader
{
	static constexpr uint32_t HEADER_MAGIC      = 0x53544453; // SDTS
	static constexpr uint32_t DATA_START_OFFSET = 0xA8;
	static constexpr uint32_t SECTION_COUNT     = 36;

	static constexpr uint32_t DATA_START_OFFSET_OLD = 0xA4;
	static constexpr uint32_t SECTION_COUNT_OLD     = 35;

	static inline const std::wstring CONFIG_NAME = L"config.json";

	enum Sections
	{
		Graphics = 1,
		UI       = 2,
		Audio    = 4,
		Font     = 8,
		Script   = 0x10, // Might also be encrypted flag
		Video    = 0x20
	};

public:
	FileHeader() = default;
	FileHeader(const std::wstring &fileName);

	~FileHeader() = default;

	void Init(const std::wstring &fileName);

	void Print() const;

	void Unpack(const std::wstring &outputFolder);

	void Pack(const std::wstring &outputFile);

	void Reset();

	const uint32_t &GetVersion() const
	{
		return m_fileVersion;
	}

	const uint32_t &GetResourceFlags() const
	{
		return m_presentSegments;
	}

	std::vector<uint8_t> GetProjectData() const;

private:
	void initSections(bool verbose = false);

	void writeOffsets(FileWriter &fileWriter, const std::vector<uint32_t> &sizes, uint32_t &offset) const;

	void initDTS(const std::wstring &fileName);

	void initFolder(const std::wstring &inputFolder);

private:
	FileReader m_fileReader = {};

	uint32_t m_magicNumber     = 0;
	uint32_t m_encrypted       = 0;
	uint32_t m_fileVersion     = 0;
	uint32_t m_loadRuntime     = 0;
	uint32_t m_presentSegments = 0;

	uint32_t m_projectDataAddress              = 0;
	std::deque<SecInfo> m_sectionDataAddresses = {};

	bool m_sectionInitDone = false;
	bool m_oldFormat    = false;

	GraphicSection m_gSec = {};
	UiSection m_uSec      = {};
	AudioSection m_aSec   = {};
	FontSection m_fSec    = {};
	VideoSection m_vSec   = {};
	ScriptSection m_sSec  = {};
	ProjectSection m_pSec = {};
};
