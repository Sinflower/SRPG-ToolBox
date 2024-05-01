// Compatible up to v1.292

#include "ITEMDURABILITYCHANGE.h"

void ITEMDURABILITYCHANGE::init(FileReader& fw)
{
	if (g_ArcVersion >= 1078)
		this_3 = fw.ReadDWord();

	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion >= 1071)
		this_8 = fw.ReadDWord();
}

void ITEMDURABILITYCHANGE::dump(FileWriter& fw) const
{
	if (g_ArcVersion >= 1078)
		fw.Write(this_3);

	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion >= 1071)
		fw.Write(this_8);
}
