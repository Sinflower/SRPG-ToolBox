// Compatible up to v1.292

#include "INFOWINDOW.h"

void INFOWINDOW::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	initMemData(this_4, fw);
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
}

void INFOWINDOW::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	this_4.Write(fw);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
}
