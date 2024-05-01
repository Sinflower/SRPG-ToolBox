// Compatible up to v1.292

#include "VIDEODATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void VIDEODATA::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	initMemData(this_3, fw);
}

void VIDEODATA::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);

	this_3.Write(fw);
}

nlohmann::ordered_json VIDEODATA::toJson() const
{
	return { { "name", ws2s(this_3.ToWString()) } };
}
