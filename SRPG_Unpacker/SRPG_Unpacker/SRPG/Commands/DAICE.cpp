// Compatible up to v1.292

#include "DAICE.h"

void DAICE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void DAICE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
