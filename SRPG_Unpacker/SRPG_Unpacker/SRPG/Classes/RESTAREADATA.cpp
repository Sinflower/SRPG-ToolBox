// Compatible up to v1.292

#include "RESTAREADATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void RESTAREADATA::init(FileReader& fw)
{
	initMemData(this_3, fw);

	this_4 = fw.ReadDWord();

	this_6  = fw.ReadDWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	if (this_10)
		this_11.init(fw);

	initMemData(this_12, fw);
}

void RESTAREADATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);

	fw.Write(this_4);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);

	if (this_10)
		this_11.dump(fw);

	this_12.Write(fw);
}
