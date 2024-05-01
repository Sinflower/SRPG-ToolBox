#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct CLASSTYPEDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	MemData this_13;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
