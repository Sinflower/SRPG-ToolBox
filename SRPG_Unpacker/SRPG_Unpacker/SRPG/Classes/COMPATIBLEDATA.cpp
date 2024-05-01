// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "COMPATIBLEDATA.h"

void COMPATIBLEDATA::init(FileReader& fw)
{
	fw.ReadBytes(m_data.data(), 28);

	if (g_ArcVersion >= 0x4EC)
		m_data[7] = fw.ReadDWord();
}

void COMPATIBLEDATA::dump(FileWriter& fw) const
{
	fw.WriteBytes(m_data.data(), 28);

	if (g_ArcVersion >= 0x4EC)
		fw.Write(m_data[7]);
}
