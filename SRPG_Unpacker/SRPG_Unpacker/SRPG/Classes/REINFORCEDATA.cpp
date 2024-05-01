// Compatible up to v1.292

#include "REINFORCEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void REINFORCEDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion < 0x446)
		this_8 = 0;
	else
		this_8 = fw.ReadDWord();

	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	if (this_10)
		this_11.init(fw);
}

void REINFORCEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion >= 0x446)
		fw.Write(this_8);

	fw.Write(this_9);
	fw.Write(this_10);

	if (this_10)
		this_11.dump(fw);
}
