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
	FileHeader(const std::wstring fileName);

	~FileHeader() = default;

	void Print() const;

	void InitSections(bool verbose = false);

	void Unpack(const std::wstring &outputFolder);

	void Pack(const std::wstring &outputFile);

private:
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

	bool m_initSections = false;
	bool m_oldFormat    = false;

	GraphicSection m_gSec = {};
	UiSection m_uSec      = {};
	AudioSection m_aSec   = {};
	FontSection m_fSec    = {};
	VideoSection m_vSec   = {};
	ScriptSection m_sSec  = {};
	ProjectSection m_pSec = {};
};
