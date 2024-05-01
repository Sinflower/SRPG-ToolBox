// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "FONTDATA.h"

void FONTDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	this_9 = fw.ReadDWord();

	if (g_ArcVersion < 0x487)
		this_10 = 0;
	else
		this_10 = fw.ReadDWord();

	initMemData(this_3, fw);
	initMemData(this_4, fw);
}

void FONTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_9);

	if (g_ArcVersion >= 0x487)
		fw.Write(this_10);

	this_3.Write(fw);
	this_4.Write(fw);

}
