#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct VARIABLEDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
