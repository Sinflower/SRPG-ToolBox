// Compatible up to v1.292

#include "EXPERIENCEPLUS.h"

void EXPERIENCEPLUS::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3F1)
	{
		this_6 = fw.ReadDWord();
		this_7 = fw.ReadDWord();
	}
}

void EXPERIENCEPLUS::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);

	if (g_ArcVersion >= 0x3F1)
	{
		fw.Write(this_6);
		fw.Write(this_7);
	}
}
