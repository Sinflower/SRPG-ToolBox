#pragma once

#include "../Classes/EDITDATA.h"

struct OBJECTADJUST : public EDITDATA
{
	DWORD this_3;
	DWORD this_4;
	DWORD this_5;
	DWORD this_6;
	DWORD this_7;
	DWORD this_8;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};