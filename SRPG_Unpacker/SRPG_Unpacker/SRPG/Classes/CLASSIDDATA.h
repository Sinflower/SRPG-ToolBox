#pragma once

#include "EDITDATA.h"

struct CLASSIDDATA : public EDITDATA
{
	DWORD id = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
