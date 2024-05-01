// Compatible up to v1.292

#include "RESOURCELAYOUTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void RESOURCELAYOUTDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();

	if (g_ArcVersion >= 0x4A1)
	{
		this_7 = fw.ReadDWord();
		this_8 = fw.ReadDWord();
	}
}

void RESOURCELAYOUTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);

	if (g_ArcVersion >= 0x4A1)
	{
		fw.Write(this_7);
		fw.Write(this_8);
	}
}
