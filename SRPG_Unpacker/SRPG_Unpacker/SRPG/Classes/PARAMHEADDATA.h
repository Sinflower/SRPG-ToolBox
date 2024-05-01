#pragma once

#include "EDITDATA.h"

struct PARAMHEADDATA : public EDITDATA
{
	DWORD this_3 = 0;
	MemData this_4;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
