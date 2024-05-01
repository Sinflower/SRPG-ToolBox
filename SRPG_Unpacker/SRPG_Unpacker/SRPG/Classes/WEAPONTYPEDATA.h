#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct WEAPONTYPEDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	class CMenuOperation* m_pCompatibledata = nullptr;
	MemData this_11;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
