// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "PASSGROUPDATA.h"

void PASSGROUPDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);

	if (g_ArcVersion >= 0x4F8)
		initMemData(this_4, fw);
}

void PASSGROUPDATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);

	if (g_ArcVersion >= 0x4F8)
		this_4.Write(fw);
}
