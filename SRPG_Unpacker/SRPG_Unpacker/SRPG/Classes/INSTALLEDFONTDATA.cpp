// Compatible up to v1.292

#include "INSTALLEDFONTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void INSTALLEDFONTDATA::init(FileReader& fw)
{
	this_5 = fw.ReadDWord();

	initMemData(this_3, fw);
	initMemData(this_4, fw);

	if (g_ArcVersion >= 1137)
		this_6 = fw.ReadDWord();
}

void INSTALLEDFONTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_5);

	this_3.Write(fw);
	this_4.Write(fw);

	if (g_ArcVersion >= 1137)
		fw.Write(this_6);
}

nlohmann::ordered_json INSTALLEDFONTDATA::toJson() const
{
	return { { "name", ws2s(this_3.ToWString()) } };
}
