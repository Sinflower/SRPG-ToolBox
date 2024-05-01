// Compatible up to v1.292

#include "SYSTEMSETTINGS.h"
#include "../CMenuOperation.h"

void SYSTEMSETTINGS::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	if (g_ArcVersion < 1123)
		this_4.resize(6);
	else
		this_4.resize(7);

	fw.ReadBytes(this_4.data(), static_cast<DWORD>(this_4.size() * sizeof(DWORD)));
}

void SYSTEMSETTINGS::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.WriteBytes(this_4.data(), this_4.size() * sizeof(DWORD));
}
