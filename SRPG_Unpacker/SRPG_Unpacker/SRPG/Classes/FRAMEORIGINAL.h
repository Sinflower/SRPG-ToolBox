#pragma once

#include "EDITDATA.h"

struct FRAMEORIGINAL : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	MemData this_5;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
