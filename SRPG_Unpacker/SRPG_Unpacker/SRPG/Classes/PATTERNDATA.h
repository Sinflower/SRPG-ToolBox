#pragma once

#include "EDITDATA.h"
#include "EVENTPAGE_DATA.h"

struct PATTERNDATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	EVENTPAGE_DATA this_5;
	struct APPROACHPATTERN* this_7 = nullptr;
	struct WAITPATTERN* this_8     = nullptr;
	struct MOVEPATTERN* this_9     = nullptr;
	struct CUSTOMPATTERN* this_10  = nullptr;
	class CMenuOperation* this_11  = nullptr;
	DWORD this_12                  = 0;
	DWORD this_13                  = 0;
	DWORD this_14                  = 0;
	class CMenuOperation* this_15  = nullptr;
	DWORD this_16                  = 0;
	class CMenuOperation* this_17  = nullptr;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
