// Compatible up to v1.292

#include "VARIABLECONDITIONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void VARIABLECONDITIONDATA::init(FileReader& fw)
{
	this_3  = fw.ReadDWord();
	this_4  = fw.ReadDWord();
	this_5  = fw.ReadQWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadQWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadQWord();
	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();

	if (g_ArcVersion >= 0x4D5)
		this_16 = fw.ReadDWord();
}

void VARIABLECONDITIONDATA::dump([[maybe_unused]] FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_14);
	fw.Write(this_15);

	if (g_ArcVersion >= 0x4D5)
	fw.Write(this_16);
}