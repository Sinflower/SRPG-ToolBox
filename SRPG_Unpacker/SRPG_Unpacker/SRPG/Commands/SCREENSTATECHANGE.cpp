// Compatible up to v1.292

#include "SCREENSTATECHANGE.h"

void SCREENSTATECHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void SCREENSTATECHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
