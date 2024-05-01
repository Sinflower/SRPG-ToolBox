#include "SectionData.h"

SectionData::SectionData(FileReader *pFileReader, const uint32_t &idx) :
	DataBase(pFileReader, idx)
{
	loadData();
}

SectionData::SectionData(const std::wstring &inputFolder, const uint32_t &idx) :
	DataBase(idx)
{
	buildData(inputFolder);
}
