#pragma once

#include "EDITDATA.h"

struct GALLERYGROUPDATA : public EDITDATA
{
	DWORD this_3;
	DWORD this_4;
	DWORD this_5;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
