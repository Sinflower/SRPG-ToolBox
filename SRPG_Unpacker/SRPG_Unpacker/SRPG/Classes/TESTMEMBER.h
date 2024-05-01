#pragma once

#include "EDITDATA.h"

struct TESTMEMBER : public EDITDATA
{
	class CMenuOperation* this_3;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
