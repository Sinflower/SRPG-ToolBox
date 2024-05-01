#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct SWITCHDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
