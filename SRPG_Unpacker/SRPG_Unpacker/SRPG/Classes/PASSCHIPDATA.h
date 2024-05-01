#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct PASSCHIPDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	MemData this_15;
	class CMenuOperation* m_pTypeIDData1 = nullptr;
	std::array <DWORD, 24> this_17 = { 0 };
	MemData this_41;
	DWORD this_42 = 0;
	class CMenuOperation* m_pTypeIDData2 = nullptr;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
