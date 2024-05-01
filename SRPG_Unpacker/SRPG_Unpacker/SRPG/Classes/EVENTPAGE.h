#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"

struct EVENTPAGE : public EDITDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
	class CMenuOperation* this_3 = nullptr;
	DWORD this_4;
	EVENTPAGE_DATA this_5;
};
