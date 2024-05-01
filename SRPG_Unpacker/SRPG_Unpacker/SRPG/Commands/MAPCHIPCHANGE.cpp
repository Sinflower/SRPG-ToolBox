// Compatible up to v1.292

#include "MAPCHIPCHANGE.h"

void MAPCHIPCHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	initMemData(this_4, fw, 16 * this_3);
}

void MAPCHIPCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	this_4.Write(fw);
}
