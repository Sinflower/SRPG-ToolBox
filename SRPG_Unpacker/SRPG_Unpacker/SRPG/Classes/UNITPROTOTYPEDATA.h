#pragma once

#include "EDITDATA.h"

struct UNITPROTOTYPEDATA : public EDITDATA
{
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
	DWORD this_14 = 0;
	DWORD this_15 = 0x20000;
	MemData this_16;
	MemData this_17;
	class CMenuOperation* m_pUnitStatusData = nullptr;

	void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
