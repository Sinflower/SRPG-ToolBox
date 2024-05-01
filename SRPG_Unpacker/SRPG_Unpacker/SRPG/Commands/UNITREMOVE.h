#pragma once

#include "../Classes/EDITDATA.h"

struct UNITREMOVE : public EDITDATA
{
	std::array <DWORD, 7> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
