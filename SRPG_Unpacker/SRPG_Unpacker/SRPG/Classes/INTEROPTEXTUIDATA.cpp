// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "INTEROPTEXTUIDATA.h"

void INTEROPTEXTUIDATA::init(FileReader& fw)
{
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	INTEROPBASE::init(fw);

	//this_6 = (BYTE0(this_6) << 16) | (BYTE1(this_6) << 8) | BYTE2(this_6);
}

void INTEROPTEXTUIDATA::dump(FileWriter& fw) const
{
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);

	INTEROPBASE::dump(fw);
}
