// Compatible up to v1.292

#include "EVENTSKIP.h"

void EVENTSKIP::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void EVENTSKIP::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
