// Compatible up to v1.292

#include "MESSAGESCROLL.h"

void MESSAGESCROLL::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	initMemData(this_3, fw);
}

void MESSAGESCROLL::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	this_3.Write(fw);
}
