#pragma once

#include "EDITDATA.h"

struct SHOPDATA : public EDITDATA
{
	DWORD this_3                 = 0;
	class CMenuOperation* this_4 = nullptr;
	MemData this_4_old;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
