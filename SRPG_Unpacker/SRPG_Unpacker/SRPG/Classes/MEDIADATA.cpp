#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "MEDIADATA.h"

void MEDIADATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();

	initMemData(this_7, fw);
}

void MEDIADATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);

	this_7.Write(fw);
}

nlohmann::ordered_json MEDIADATA::toJson() const
{
	return { { "name", ws2s(this_7.ToWString()) } };
}
