#pragma once

#include "../Classes/EDITDATA.h"

struct INFOWINDOW : public EDITDATA
{
	DWORD this_3;
	MemData this_4;
	DWORD this_5;
	DWORD this_6;
	DWORD this_7;
	DWORD this_8;
	DWORD this_9;
	DWORD this_10;
	DWORD this_11;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
