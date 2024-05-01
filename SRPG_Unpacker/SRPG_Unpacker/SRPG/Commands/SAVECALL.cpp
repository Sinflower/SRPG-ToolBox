// Compatible up to v1.292

#include "SAVECALL.h"

void SAVECALL::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void SAVECALL::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
