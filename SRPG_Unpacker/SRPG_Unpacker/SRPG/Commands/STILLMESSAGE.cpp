// Compatible up to v1.292

#include "STILLMESSAGE.h"

void STILLMESSAGE::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	if (g_ArcVersion >= 1039)
		this_6 = fw.ReadDWord();

	initMemData(this_3, fw);
}

void STILLMESSAGE::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);

	if (g_ArcVersion >= 1039)
		fw.Write(this_6);

	this_3.Write(fw);
}
