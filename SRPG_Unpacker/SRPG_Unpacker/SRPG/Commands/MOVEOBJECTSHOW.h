#pragma once

#include "../Classes/EDITDATA.h"

struct MOVEOBJECTSHOW : public EDITDATA
{
	std::array<DWORD, 11> data;
	class CMenuOperation* m_pLinePosData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
