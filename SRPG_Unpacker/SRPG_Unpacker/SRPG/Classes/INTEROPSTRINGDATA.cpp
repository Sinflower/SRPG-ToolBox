// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "INTEROPSTRINGDATA.h"

void INTEROPSTRINGDATA::init(FileReader& fw)
{
	INTEROPBASE::init(fw);
}

void INTEROPSTRINGDATA::dump(FileWriter& fw) const
{
	INTEROPBASE::dump(fw);
}
