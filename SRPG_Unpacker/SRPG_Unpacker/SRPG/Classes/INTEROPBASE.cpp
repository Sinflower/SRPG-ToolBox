// Compatible up to v1.292

#include "INTEROPBASE.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void INTEROPBASE::init(FileReader& fw)
{
	initMemData(this_3, fw);
	initMemData(this_4, fw);
}

void INTEROPBASE::dump(FileWriter& fw) const
{
	this_3.Write(fw);
	this_4.Write(fw);
}
