#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct DAYNIGHTDATA : public EDITDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

	
	MemData this_3;
	DWORD this_4 = 0;
	BYTE this_5 = 0;
	BYTE this_6 = 0;
};
