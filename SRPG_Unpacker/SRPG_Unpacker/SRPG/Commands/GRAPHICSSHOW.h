#pragma once

#include "../Classes/EDITDATA.h"

struct GRAPHICSSHOW : public EDITDATA
{
	std::vector<DWORD> m_data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
