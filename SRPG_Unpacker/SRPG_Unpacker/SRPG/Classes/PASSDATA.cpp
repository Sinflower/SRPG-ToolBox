// Compatible up to v1.292

#include "PASSDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void PASSDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();

	initMemData(this_9, fw);

	this_5 = fw.ReadDWord();
	initMemData(this_6, fw, this_5);
	initMemData(this_7, fw, this_5);

	allocAndSetCMenuOp(&m_pPassChipData, SRPGClasses::PASSCHIPDATA, fw);
}

void PASSDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);

	this_9.Write(fw);

	fw.Write(this_5);
	this_6.Write(fw);
	this_7.Write(fw);

	m_pPassChipData->dump(fw);
}
