// Compatible up to v1.292

#include "NEWSKILLDATA.h"

void NEWSKILLDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();

	if ( g_ArcVersion >= 1055 )
	{
		this_5 = fw.ReadDWord();
		this_6 = fw.ReadDWord();
	}
}

void NEWSKILLDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
}
