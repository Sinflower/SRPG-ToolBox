// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "MOVEPATTERN.h"

void MOVEPATTERN::init(FileReader& fw)
{
	this_1 = fw.ReadDWord();
	this_2 = fw.ReadDWord();
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();

	if (g_ArcVersion >= 0x3F1)
		this_5 = fw.ReadDWord();
}

void MOVEPATTERN::dump(FileWriter& fw) const
{
	fw.Write(this_1);
	fw.Write(this_2);
	fw.Write(this_3);
	fw.Write(this_4);

	if (g_ArcVersion >= 0x3F1)
		fw.Write(this_5);
}
