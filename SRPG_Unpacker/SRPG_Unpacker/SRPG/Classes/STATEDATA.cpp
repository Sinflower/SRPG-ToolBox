// Compatible up to v1.292

#include "STATEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void STATEDATA::init(FileReader& fw)
{
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();
	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();
	this_31 = fw.ReadDWord();
	this_16 = fw.ReadDWord();

	if (g_ArcVersion < 0x446)
		this_17 = 0;
	else
		this_17 = fw.ReadDWord();

	if (g_ArcVersion >= 0x48E)
	{
		this_32 = fw.ReadDWord();
		this_33 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x404)
		m_pTypeIDData = new CMenuOperation(SRPGClasses::TYPEIDDATA);
	else
		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	sub_10E310(fw);

	initMemData(this_18, fw);

	LEGENDDATA::init(fw);

	if (g_ArcVersion >= 0x4A4)
	{
		this_34 = fw.ReadDWord();
		initMemData(this_35, fw);
	}
}

void STATEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_13);
	fw.Write(this_14);
	fw.Write(this_15);
	fw.Write(this_31);
	fw.Write(this_16);

	if (g_ArcVersion >= 0x446)
		fw.Write(this_17);

	if (g_ArcVersion >= 0x48E)
	{
		fw.Write(this_32);
		fw.Write(this_33);
	}

	if (g_ArcVersion >= 0x404)
		m_pTypeIDData->dump(fw);

	if (g_ArcVersion < 0x418)
	{
		fw.Write(this_19);
		fw.Write(this_20);
		fw.Write(this_21);
		fw.Write(this_22);
		fw.Write(this_23);
		fw.Write(this_24);
		fw.Write(this_25);
		fw.Write(this_26);
		fw.Write(this_27);
	}
	else
	{
		fw.Write(res);
		if (!res)
		{
			fw.Write(this_19);
			fw.Write(this_20);
			fw.Write(this_21);
			fw.Write(this_22);
			fw.Write(this_23);
			fw.Write(this_24);
			fw.Write(this_25);
			fw.Write(this_26);
			fw.Write(this_27);
			fw.Write(this_28);
			fw.Write(this_29);
		}
	}

	this_18.Write(fw);

	LEGENDDATA::dump(fw);

	if (g_ArcVersion >= 0x4A4)
	{
		fw.Write(this_34);
		this_35.Write(fw);
	}
}

void STATEDATA::sub_10E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_19 = fw.ReadDWord();
		this_20 = fw.ReadDWord();
		this_21 = fw.ReadDWord();
		this_22 = fw.ReadDWord();
		this_23 = fw.ReadDWord();
		this_24 = fw.ReadDWord();
		this_25 = fw.ReadDWord();
		this_26 = fw.ReadDWord();
		this_27 = fw.ReadDWord();
		this_28 = 0;
		this_29 = 0;
	}
	else
	{
		res = fw.ReadDWord();
		if (res)
		{
			this_19 = 0;
			this_20 = 0;
			this_21 = 0;
			this_22 = 0;
			this_23 = 0;
			this_24 = 0;
			this_25 = 0;
			this_26 = 0;
			this_27 = 0;
			this_28 = 0;
			this_29 = 0;
		}
		else
		{
			this_19 = fw.ReadDWord();
			this_20 = fw.ReadDWord();
			this_21 = fw.ReadDWord();
			this_22 = fw.ReadDWord();
			this_23 = fw.ReadDWord();
			this_24 = fw.ReadDWord();
			this_25 = fw.ReadDWord();
			this_26 = fw.ReadDWord();
			this_27 = fw.ReadDWord();
			this_28 = fw.ReadDWord();
			this_29 = fw.ReadDWord();
		}
	}
}
