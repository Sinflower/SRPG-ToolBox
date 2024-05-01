#pragma once

#include "EDITDATA.h"

struct DICTIONARYCONDITION : public EDITDATA
{
	MemData this_3;
	class CMenuOperation* pSwitchActionData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
