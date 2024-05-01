#pragma once

#include "../Classes/EDITDATA.h"

struct UNITSTATEADDITION : public EDITDATA
{
	std::array <DWORD, 6> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
