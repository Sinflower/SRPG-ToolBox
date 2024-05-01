// Compatible up to v1.292

#include "DAMAGEHIT.h"

void DAMAGEHIT::init(FileReader& fw)
{
	if (g_ArcVersion < 0x488)
		data.resize(6);
	else
		data.resize(7);

	fw.ReadBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}

void DAMAGEHIT::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}
