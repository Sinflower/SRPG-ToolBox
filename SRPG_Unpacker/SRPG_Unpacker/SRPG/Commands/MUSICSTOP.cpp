// Compatible up to v1.292

#include "MUSICSTOP.h"

void MUSICSTOP::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void MUSICSTOP::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
