#pragma once
#include "DataBase.h"

class SectionData : public DataBase
{
public:
	SectionData(FileReader *pFileReader, const uint32_t &idx);

	SectionData(const std::wstring &inputFolder, const uint32_t &idx);
};
