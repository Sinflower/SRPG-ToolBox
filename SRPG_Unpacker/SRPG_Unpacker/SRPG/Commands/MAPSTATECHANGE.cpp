// Compatible up to v1.292

#include "MAPSTATECHANGE.h"

void MAPSTATECHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	if (g_ArcVersion < 1165)
	{
		if (g_ArcVersion < 1074)
		{
			if (g_ArcVersion < 1017)
			{
				if (g_ArcVersion < 1004)
					this_4.resize(5);
				else
					this_4.resize(6);
			}
			else
				this_4.resize(7);
		}
		else
			this_4.resize(8);
	}
	else
		this_4.resize(9);

	fw.ReadBytes(this_4.data(), static_cast<DWORD>(this_4.size() * sizeof(DWORD)));
}

void MAPSTATECHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.WriteBytes(this_4.data(), static_cast<DWORD>(this_4.size() * sizeof(DWORD)));
}
