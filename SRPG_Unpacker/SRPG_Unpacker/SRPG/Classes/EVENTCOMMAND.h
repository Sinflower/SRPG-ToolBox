#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"

struct EVENTCOMMAND : public EDITDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;

	DWORD res = 0;
	DWORD this_3;
	WORD this_4;
	DWORD this_5;
	EVENTPAGE_DATA this_6;
	EDITDATA* this_7;
	MemData comment;
};
