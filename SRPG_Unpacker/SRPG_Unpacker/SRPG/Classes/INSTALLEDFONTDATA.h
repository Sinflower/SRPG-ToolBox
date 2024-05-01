#pragma once

#include "EDITDATA.h"

struct INSTALLEDFONTDATA : public EDITDATA
{
	MemData this_3;
	MemData this_4;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

protected:
	nlohmann::ordered_json toJson() const override;
};
