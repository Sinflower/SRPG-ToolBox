#pragma once

#include "../Classes/EDITDATA.h"

struct MAPINFOCHANGE : public EDITDATA
{
	std::array<DWORD, 19> this_3;
	MemData this_22;
	class CMenuOperation* this_23 = nullptr;
	class CMenuOperation* this_24 = nullptr;
	class CMenuOperation* this_25 = nullptr;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
