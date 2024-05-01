#pragma once

#include "EDITDATA.h"

struct VARIABLECONDITIONDATA : public EDITDATA
{
	void init(FileReader& fw);
	void dump([[maybe_unused]] FileWriter& fw) const;

	DWORD this_3  = 0;
	DWORD this_4  = 0;
	QWORD this_5  = 0;
	DWORD this_7  = 0;
	QWORD this_8  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	QWORD this_12 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
};
