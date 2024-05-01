// Compatible up to v1.292

#include "WAITACTION.h"

void WAITACTION::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void WAITACTION::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
