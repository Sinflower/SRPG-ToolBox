// Compatible up to v1.292

#include "MUSICPLAY.h"

void MUSICPLAY::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
}

void MUSICPLAY::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
}
