// Compatible up to v1.292

#include "CHOICEDATA.h"
#include "../CMenuOperation.h"
#include "../Commands/SWITCHACTION.h"
#include "EDITDATA.h"

void CHOICEDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);
	this_4 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion < 0x432)
	{
		if (g_ArcVersion < 0x404)
			res = fw.ReadQWord(); // Skip the next 8 byte

		this_9.this_2 = new SWITCHACTION();
		this_9.this_2->init(fw);
	}
	else
	{
		this_8 = fw.ReadDWord();
		if (this_8)
			this_9.init(fw);
	}
}

void CHOICEDATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);
	fw.Write(this_4);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion < 0x432)
	{
		if (g_ArcVersion < 0x404)
			fw.Write(res);

		this_9.this_2->dump(fw);
	}
	else
	{
		fw.Write(this_8);
		if (this_8)
			this_9.dump(fw);
	}
}
