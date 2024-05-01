#pragma once

#include "EDITDATA.h"
#include "INTEROPBASE.h"

struct INTEROPSTRINGDATA : public EDITDATA, public INTEROPBASE
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
