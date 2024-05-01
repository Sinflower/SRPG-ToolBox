// Compatible up to v1.292

#include "SCRIPTEXECUTE.h"
#include "../CMenuOperation.h"

void SCRIPTEXECUTE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	initMemData(this_4, fw);
	initMemData(this_5, fw);

	if (g_ArcVersion >= 0x49F)
		sub_EB6050(fw);

	// NOTE: This was added and if it causes problems check the actual
	//       execution in the binary
	if (HIWORD(this_3) == 1)
		this_26 = fw.ReadDWord();
}

void SCRIPTEXECUTE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	this_4.Write(fw);
	this_5.Write(fw);

	if (g_ArcVersion >= 0x49F)
	{
		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);
		fw.Write(this_12);
		fw.Write(this_13);
		fw.Write(this_14);
		fw.Write(this_15);
		fw.Write(this_16);
		fw.Write(this_17);
		fw.Write(this_18);
		fw.Write(this_19);
		fw.Write(this_20);

		m_pTypeIDData->dump(fw);

		this_22.Write(fw);
	}

	if (HIWORD(this_3) == 1)
		fw.Write(this_26);
}

void SCRIPTEXECUTE::sub_EB6050(FileReader& fw)
{
	this_6  = fw.ReadDWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();
	this_16 = fw.ReadDWord();
	this_17 = fw.ReadDWord();
	this_18 = fw.ReadDWord();
	this_19 = fw.ReadDWord();

	this_20 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	initMemData(this_22, fw);
}
