#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"

struct RESTAREADATA : public EDITDATA
{
	MemData this_3;
	DWORD this_4 = 0;
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	EVENTPAGE_DATA this_11;
	MemData this_12;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
