// Compatible up to v1.292

#include "CONSOLELOG.h"

void CONSOLELOG::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	initMemData(this_5, fw);
	this_6 = fw.ReadDWord();
}

void CONSOLELOG::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	this_5.Write(fw);
	fw.Write(this_6);
}
