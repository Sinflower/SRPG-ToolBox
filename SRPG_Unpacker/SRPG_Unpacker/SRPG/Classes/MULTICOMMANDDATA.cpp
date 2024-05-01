// Compatible up to v1.292

#include "MULTICOMMANDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void MULTICOMMANDDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);
	if (g_ArcVersion >= 0x505)
		this_4 = fw.ReadDWord();
}

void MULTICOMMANDDATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);
	if (g_ArcVersion >= 0x505)
		fw.Write(this_4);
}
