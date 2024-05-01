// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "COMMANDLAYOUTDATA.h"

void COMMANDLAYOUTDATA::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	initMemData(this_3, fw);
}

void COMMANDLAYOUTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);

	m_pTypeIDData->dump(fw);
	this_3.Write(fw);
}
