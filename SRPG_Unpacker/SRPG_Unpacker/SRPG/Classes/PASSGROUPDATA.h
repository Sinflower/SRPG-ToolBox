#pragma once

#include "EDITDATA.h"

struct PASSGROUPDATA : public EDITDATA
{
	MemData this_3;
	MemData this_4;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
