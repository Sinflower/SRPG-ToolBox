#pragma once

#include "../CMenuOperation.h"
#include "../Classes/EDITDATA.h"
#include "UNITAPPEAR.h"
#include "UNITREMOVE.h"

struct UNITMOVE : public EDITDATA
{
	DWORD res = 0;

	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	MemData this_8;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	UNITAPPEAR this_14;
	UNITREMOVE this_15;
	DWORD this_16 = 0;
	DWORD this_17 = 0;
	DWORD this_18 = 0;
	DWORD this_19 = 0;
	DWORD this_20 = 0;
	DWORD this_21 = 0;
	DWORD this_22 = 0;
	DWORD this_23 = 0;
	DWORD this_24 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
