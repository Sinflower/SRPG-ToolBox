// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "SHOPLAYOUT.h"

void SHOPLAYOUT::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	m_interOpScreenData.init(fw);

	for (MemData& ph : this_6)
		initMemData(ph, fw);

	if (g_ArcVersion >= 0x43D)
		this_19 = fw.ReadDWord();
}

void SHOPLAYOUT::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);

	m_interOpScreenData.dump(fw);

	for (const MemData& ph : this_6)
		ph.Write(fw);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_19);
}
