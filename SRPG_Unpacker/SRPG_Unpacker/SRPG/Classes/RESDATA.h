#pragma once

#include "EDITDATA.h"
#include "IMAGEDATA.h"

struct RESDATA : public IMAGEDATA
{
	DWORD this_35 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
