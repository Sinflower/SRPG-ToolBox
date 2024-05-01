// Compatible up to v1.292

#include "VARIABLEACTION.h"

void VARIABLEACTION::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion < 0x418 && this_5 == 4)
	{
		//if (this_7 > 9)
		//	this_7 += 2;
	}

	if (g_ArcVersion >= 0x4D5)
		this_8 = fw.ReadDWord();
}

void VARIABLEACTION::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion >= 0x4D5)
		fw.Write(this_8);
}
