// Compatible up to v1.292

#include "MESSAGETEROP.h"

void MESSAGETEROP::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	if (g_ArcVersion >= 0x40F)
	{
		this_7 = fw.ReadDWord();
		this_8 = fw.ReadDWord();
		this_6 = fw.ReadDWord();
	}

	initMemData(this_3, fw);
}

void MESSAGETEROP::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);

	if (g_ArcVersion >= 0x40F)
	{
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_6);
	}

	this_3.Write(fw);
}
