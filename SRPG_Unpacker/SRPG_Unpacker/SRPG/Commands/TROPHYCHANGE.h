#pragma once

#include "../Classes/EDITDATA.h"

struct TROPHYCHANGE : public EDITDATA
{
	std::array<DWORD, 8> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
