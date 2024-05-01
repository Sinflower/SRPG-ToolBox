// Compatible up to v1.292

#include "BACKGROUNDCHANGE.h"

void BACKGROUNDCHANGE::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 28);

	if (g_ArcVersion >= 0x4E1)
	{
		this_11 = fw.ReadDWord();
		if (this_11 == 2 || this_11 == 3)
		{
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
			this_15 = fw.ReadDWord();
		}
	}

	if (g_ArcVersion >= 0x4ED)
	{
		if (this_11)
			this_16 = fw.ReadDWord();
	}
}

void BACKGROUNDCHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 28);

	if (g_ArcVersion >= 0x4E1)
	{
		fw.Write(this_11);
		if (this_11 == 2 || this_11 == 3)
		{
			fw.Write(this_12);
			fw.Write(this_13);
			fw.Write(this_14);
			fw.Write(this_15);
		}
	}

	if (g_ArcVersion >= 0x4ED)
	{
		if (this_11)
			fw.Write(this_16);
	}
}
