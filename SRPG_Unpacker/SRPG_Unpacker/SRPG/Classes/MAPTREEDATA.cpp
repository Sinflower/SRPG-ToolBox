// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "MAPTREEDATA.h"

void MAPTREEDATA::init(FileReader& fw)
{
	this_5 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	fw.ReadBytes(this_8.data(), 384);

	initMemData(this_3, fw);
}

void MAPTREEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_5);
	fw.Write(this_4);
	fw.Write(this_6);
	fw.Write(this_7);

	fw.WriteBytes(this_8.data(), 384);

	this_3.Write(fw);
}
