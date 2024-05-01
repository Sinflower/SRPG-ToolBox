// Compatible up to v1.292

#include "UNITCAPACITYCHANGE.h"

void UNITCAPACITYCHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	if (g_ArcVersion < 1048)
	{
		if (g_ArcVersion < 1036)
			this_6.resize(9);
		else
			this_6.resize(20);
	}
	else
		this_6.resize(22);

	fw.ReadBytes(this_6.data(), static_cast<DWORD>(this_6.size() * sizeof(DWORD)));

	if (g_ArcVersion < 1048)
		this_32.resize(9);
	else
		this_32.resize(22);

	fw.ReadBytes(this_32.data(), static_cast<DWORD>(this_32.size() * sizeof(DWORD)));

	if (g_ArcVersion >= 1048)
	{
		this_50 = fw.ReadDWord();
		this_51 = fw.ReadDWord();
	}
}

void UNITCAPACITYCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);

	fw.WriteBytes(this_6.data(), static_cast<DWORD>(this_6.size() * sizeof(DWORD)));

	fw.WriteBytes(this_32.data(), static_cast<DWORD>(this_32.size() * sizeof(DWORD)));

	if (g_ArcVersion >= 1048)
	{
		fw.Write(this_50);
		fw.Write(this_51);
	}
}
