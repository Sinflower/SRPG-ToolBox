// Compatible up to v1.292

#include "TROPHYCHANGE.h"

void TROPHYCHANGE::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}

void TROPHYCHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}
