// Compatible up to v1.292

#include "MOVEOBJECTHIDE.h"

void MOVEOBJECTHIDE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void MOVEOBJECTHIDE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
