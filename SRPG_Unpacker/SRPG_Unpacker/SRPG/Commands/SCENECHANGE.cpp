// Compatible up to v1.292

#include "SCENECHANGE.h"

void SCENECHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void SCENECHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
