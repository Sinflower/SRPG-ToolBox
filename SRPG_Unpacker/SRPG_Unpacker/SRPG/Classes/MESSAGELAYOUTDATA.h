#pragma once

#include "EDITDATA.h"

struct MESSAGELAYOUTDATA : public EDITDATA
{
	DWORD this_3  = 0;
	DWORD this_4  = 0;
	DWORD this_5  = 0;
	DWORD this_6  = 0;
	DWORD this_7  = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	DWORD this_17 = 0;
	DWORD this_18 = 0;
	DWORD this_19 = 0;
	DWORD this_20 = 0;
	DWORD this_22 = 0;
	DWORD this_23 = 0;
	DWORD this_24 = 0;
	DWORD this_25 = 0;
	DWORD this_26 = 0;
	DWORD this_27 = 0;
	MemData this_28;
	class CMenuOperation* m_pInterOptextUIData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
