// Compatible up to v1.292

#include "STRINGDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void STRINGDATA::init(FileReader& fw)
{
	initMemData(data, fw);
}

void STRINGDATA::dump(FileWriter& fw) const
{
	data.Write(fw);
}

void STRINGDATA::print(std::ostream& os) const
{
	os << data;
}
