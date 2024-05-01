#pragma once

#include "../Classes/EDITDATA.h"

struct CHOICESHOW : public EDITDATA
{
	class CMenuOperation* pChoiceData = nullptr;
	DWORD this_4                      = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
