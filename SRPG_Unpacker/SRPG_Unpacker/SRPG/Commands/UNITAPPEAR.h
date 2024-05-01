#pragma once

#include "../Classes/EDITDATA.h"

struct UNITAPPEAR : public EDITDATA
{
	std::vector<DWORD> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
