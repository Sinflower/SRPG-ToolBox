#pragma once

#include "EDITDATA.h"
#include "INTEROPSCREENDATA.h"

struct SHOPLAYOUT : public EDITDATA
{
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	std::array<MemData, 12> this_6;
	INTEROPSCREENDATA m_interOpScreenData;
	DWORD this_19 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
