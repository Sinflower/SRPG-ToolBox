// Compatible up to v1.292

#include "VIDEOPLAY.h"

void VIDEOPLAY::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();

	if (g_ArcVersion >= 1118)
		this_7 = fw.ReadDWord();
}

void VIDEOPLAY::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);

	if (g_ArcVersion >= 1118)
		fw.Write(this_7);
}
