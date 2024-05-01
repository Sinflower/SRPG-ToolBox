// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "CLASSGROUPENTRYDATA.h"

void CLASSGROUPENTRYDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_4.data(), 40);
		this_4[10] = 0;
		this_4[11] = 0;
	}
	else
		fw.ReadBytes(this_4.data(), 48);

	// NOTE: Newer version contain a < 0x4F9 check and set all DWORDs == 3 to 4
	//       this probably has no meaning here but in case of errors check this
	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_16.data(), 40);
		this_16[10] = 3;
		this_16[11] = 3;
	}
	else
		fw.ReadBytes(this_16.data(), 48);

	allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
}

void CLASSGROUPENTRYDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_4.data(), 40);
	else
		fw.WriteBytes(this_4.data(), 48);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_16.data(), 40);
	else
		fw.WriteBytes(this_16.data(), 48);

	m_pTypeIDData->dump(fw);
}
