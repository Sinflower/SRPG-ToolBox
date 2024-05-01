#pragma once

#include "EDITDATA.h"

struct ITEMCONDITIONDATA : public EDITDATA
{
	std::array<DWORD, 4> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
