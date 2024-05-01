#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct FACIALDATA : public EDITDATA, public LEGENDDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
