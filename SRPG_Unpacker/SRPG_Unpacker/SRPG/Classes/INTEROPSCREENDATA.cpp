// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "INTEROPSCREENDATA.h"

void INTEROPSCREENDATA::init(FileReader& fw)
{
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion < 0x404)
		this_8 = 11;
	else
		this_8 = fw.ReadDWord();

	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pInterOptextUIData, SRPGClasses::INTEROPTEXTUIDATA, fw);

	INTEROPBASE::init(fw);
}

void INTEROPSCREENDATA::dump(FileWriter& fw) const
{
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion >= 0x404)
		fw.Write(this_8);

	fw.Write(this_10);
	fw.Write(this_11);

	m_pInterOptextUIData->dump(fw);

	INTEROPBASE::dump(fw);
}
