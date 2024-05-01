// Compatible up to v1.292

#include "MESSAGETITLE.h"

void MESSAGETITLE::init(FileReader& fw)
{
	initMemData(this_3, fw);

	this_6 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
}

void MESSAGETITLE::dump(FileWriter& fw) const
{
	this_3.Write(fw);

	fw.Write(this_6);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
}
