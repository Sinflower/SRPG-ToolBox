#pragma once

#include "EDITDATA.h"

struct TYPEIDDATA : public EDITDATA
{
	DWORD id = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

	virtual void print(std::ostream& os) const
	{
		os << "ID: " << id;
	}
};
