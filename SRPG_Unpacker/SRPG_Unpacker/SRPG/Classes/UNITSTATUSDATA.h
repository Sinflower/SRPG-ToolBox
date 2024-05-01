#pragma once

#include "EDITDATA.h"

struct UNITSTATUSDATA : public EDITDATA
{
	DWORD res = 0;

	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
