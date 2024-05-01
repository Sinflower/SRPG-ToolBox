#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct GALLERYDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_4;
	DWORD this_5;
	MemData this_6;
	MemData this_7;
	DWORD this_8;
	DWORD this_9;
	MemData this_10;
	class CMenuOperation* this_11 = nullptr;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
