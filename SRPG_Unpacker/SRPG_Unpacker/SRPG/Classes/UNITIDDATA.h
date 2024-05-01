#pragma once

#include "EDITDATA.h"

struct UNITIDDATA : public EDITDATA
{
	DWORD id = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
