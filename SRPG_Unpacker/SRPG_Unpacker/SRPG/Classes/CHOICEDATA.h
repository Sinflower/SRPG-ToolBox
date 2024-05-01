#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"

struct CHOICEDATA : public EDITDATA
{
	MemData this_3;
	DWORD this_4 = 0;
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	EVENTPAGE_DATA this_9;
	QWORD res = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
