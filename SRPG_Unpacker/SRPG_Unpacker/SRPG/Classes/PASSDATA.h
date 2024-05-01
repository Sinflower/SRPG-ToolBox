#pragma once

#include "EDITDATA.h"

struct PASSDATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	MemData this_6;
	MemData this_7;
	class CMenuOperation* m_pPassChipData = nullptr;
	MemData this_9;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
