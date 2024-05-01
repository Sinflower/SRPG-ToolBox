#pragma once

#include "../Classes/EDITDATA.h"

struct ANIMATIONPLAY : public EDITDATA
{
	std::array <DWORD, 12> data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
