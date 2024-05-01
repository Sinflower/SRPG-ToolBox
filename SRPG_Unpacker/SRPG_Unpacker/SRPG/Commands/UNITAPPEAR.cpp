// Compatible up to v1.292

#include "UNITAPPEAR.h"

void UNITAPPEAR::init(FileReader& fw)
{
	if (g_ArcVersion >= 0x461)
		data.resize(7);
	else
		data.resize(6);

	fw.ReadBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}

void UNITAPPEAR::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}
