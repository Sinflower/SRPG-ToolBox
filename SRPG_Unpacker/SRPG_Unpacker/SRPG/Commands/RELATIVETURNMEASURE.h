#pragma once

#include "../Classes/EDITDATA.h"

struct RELATIVETURNMEASURE : public EDITDATA
{
	DWORD this_3;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
