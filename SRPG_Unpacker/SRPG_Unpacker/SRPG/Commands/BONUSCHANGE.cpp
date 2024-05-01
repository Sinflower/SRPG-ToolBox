// Compatible up to v1.292

#include "BONUSCHANGE.h"

void BONUSCHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
}

void BONUSCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
}
