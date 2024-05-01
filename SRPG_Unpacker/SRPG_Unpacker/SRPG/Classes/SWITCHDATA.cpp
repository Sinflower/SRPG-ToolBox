// Compatible up to v1.292

#include "SWITCHDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SWITCHDATA::init(FileReader& fw)
{
	LEGENDDATA::init(fw);
	this_8 = fw.ReadDWord();
}

void SWITCHDATA::dump(FileWriter& fw) const
{
	LEGENDDATA::dump(fw);
	fw.Write(this_8);
}

void SWITCHDATA::print(std::ostream& os) const
{
	LEGENDDATA::print(os);
	os << std::endl
	   << "this_8: " << this_8;
}
