// Compatible up to v1.292

#include "IMAGEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void IMAGEDATA::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();

	initMemData(this_3, fw);
}

void IMAGEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	this_3.Write(fw);
}

nlohmann::ordered_json IMAGEDATA::toJson() const
{
	// Return the image name as a JSON object
	return { { "name", ws2s(this_3.ToWString()) } };
}
