// Compatible up to v1.292

#include "SPRITEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SPRITEDATA::init(FileReader& fw)
{
	this_3  = fw.ReadDWord();
	this_4  = fw.ReadDWord();
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_7  = fw.ReadByte();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_13 = fw.ReadDWord();
	this_14 = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_15 = fw.ReadDWord();

	if (g_ArcVersion < 0x461)
		this_16 = 1;
	else
	{
		this_16 = fw.ReadDWord();
		initMemData(this_17, fw);
	}

	if (g_ArcVersion < 0x486)
		this_18 = 0;
	else
		this_18 = fw.ReadDWord();
}

void SPRITEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_13);
	fw.Write(this_14);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_15);

	if (g_ArcVersion >= 0x461)
	{
		fw.Write(this_16);
		this_17.Write(fw);
	}

	if (g_ArcVersion >= 0x486)
		fw.Write(this_18);
}
