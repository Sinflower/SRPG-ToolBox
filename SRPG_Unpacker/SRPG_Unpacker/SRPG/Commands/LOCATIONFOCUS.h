#pragma once

#include "../Classes/EDITDATA.h"

struct LOCATIONFOCUS : public EDITDATA
{
	std::array<DWORD, 5> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
