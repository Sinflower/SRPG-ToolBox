// Compatible up to v1.292

#include "UNITSTATECHANGE.h"

void UNITSTATECHANGE::init(FileReader& fw)
{
	if (g_ArcVersion >= 0x432)
		data.resize(11);
	else if (g_ArcVersion >= 0x400)
		data.resize(10);
	else
		data.resize(9);

	fw.ReadBytes(data.data(), static_cast<DWORD>(data.size() * 4));
}

void UNITSTATECHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), static_cast<DWORD>(data.size() * 4));
}
