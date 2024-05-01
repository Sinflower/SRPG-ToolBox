// Compatible up to v1.292

#include "INTEROPSTRINGDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void INTEROPSTRINGDATA::init(FileReader& fw)
{
	INTEROPBASE::init(fw);
}

void INTEROPSTRINGDATA::dump(FileWriter& fw) const
{
	INTEROPBASE::dump(fw);
}
