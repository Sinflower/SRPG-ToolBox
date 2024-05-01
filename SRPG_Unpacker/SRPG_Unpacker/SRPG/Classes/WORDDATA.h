#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct WORDDATA : public EDITDATA, public LEGENDDATA
{
	MemData this_8;
	class CMenuOperation* pDictionaryCondition = nullptr;
	DWORD this_10                              = 0;
	DWORD this_11                              = 0;
	DWORD this_12                              = 0;
	DWORD this_13                              = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
