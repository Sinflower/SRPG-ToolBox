#pragma once

#include "EDITDATA.h"

struct MEDIADATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	MemData this_7;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

protected:
	nlohmann::ordered_json toJson() const override;
};
