#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"
#include "LEGENDDATA.h"

struct RESTSHOPDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8                         = 0;
	class CMenuOperation* pItemGroupData = nullptr;
	DWORD this_10                        = 0;
	EVENTPAGE_DATA this_11;
	MemData this_12;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
