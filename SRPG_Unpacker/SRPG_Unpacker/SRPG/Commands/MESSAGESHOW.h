#pragma once

#include "../Classes/EDITDATA.h"

struct MESSAGESHOW : public EDITDATA
{
	MemData message;
	DWORD position = 0;
	DWORD type = 0;
	DWORD unit = 0;
	DWORD this_7 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
