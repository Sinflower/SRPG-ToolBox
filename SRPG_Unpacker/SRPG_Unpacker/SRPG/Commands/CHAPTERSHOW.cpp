// Compatible up to v1.292

#include "CHAPTERSHOW.h"

void CHAPTERSHOW::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	initMemData(this_4, fw);
	initMemData(this_5, fw);
}

void CHAPTERSHOW::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	this_4.Write(fw);
	this_5.Write(fw);
}
