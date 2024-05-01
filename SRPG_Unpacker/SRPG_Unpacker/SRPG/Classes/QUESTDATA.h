#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"
#include "EVENTPAGE_DATA.h"

struct QUESTDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	EVENTPAGE_DATA this_17;
	DWORD this_18 = 0;
	EVENTPAGE_DATA this_19;
	class CMenuOperation* pRewardData = nullptr;
	MemData this_21;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
