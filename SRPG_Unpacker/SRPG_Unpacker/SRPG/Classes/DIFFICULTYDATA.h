#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct DIFFICULTYDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	class CMenuOperation* m_pTypeIDData1 = nullptr;
	class CMenuOperation* m_pTypeIDData2 = nullptr;
	MemData this_12;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
