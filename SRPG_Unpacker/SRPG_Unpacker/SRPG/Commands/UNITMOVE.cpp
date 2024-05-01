// Compatible up to v1.292

#include "UNITMOVE.h"

void UNITMOVE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	initMemData(this_8, fw, 4 * this_7);

	this_11 = fw.ReadDWord();
	this_9 = fw.ReadDWord();

	if (g_ArcVersion < 0x47F)
		this_10 = 1;
	else
		this_10 = fw.ReadDWord();

	this_12 = fw.ReadDWord();
	this_16 = fw.ReadDWord();
	this_17 = fw.ReadDWord();


	if (g_ArcVersion < 0x431)
	{
		this_18 = 0;
		this_19 = 0;
		this_20 = 0;
		this_21 = 0;
		this_22 = 0;
		this_23 = 0;
	}
	else
	{
		this_18 = fw.ReadDWord();
		this_19 = fw.ReadDWord();
		this_20 = fw.ReadDWord();
		this_21 = fw.ReadDWord();
		this_22 = fw.ReadDWord();
		this_23 = fw.ReadDWord();
	}

	if (this_17 == 1)
		this_14.init(fw);

	res = fw.ReadDWord();

	if (res)
		this_15.init(fw);

	if (g_ArcVersion >= 0x503)
		this_24 = fw.ReadDWord();
}

void UNITMOVE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	this_8.Write(fw);

	fw.Write(this_11);
	fw.Write(this_9);

	if (g_ArcVersion >= 0x47F)
		fw.Write(this_10);

	fw.Write(this_12);
	fw.Write(this_16);
	fw.Write(this_17);


	if (g_ArcVersion >= 0x431)
	{
		fw.Write(this_18);
		fw.Write(this_19);
		fw.Write(this_20);
		fw.Write(this_21);
		fw.Write(this_22);
		fw.Write(this_23);
	}

	if (this_17 == 1)
		this_14.dump(fw);

	fw.Write(res);

	if (res)
		this_15.dump(fw);

	if (g_ArcVersion >= 0x503)
		fw.Write(this_24);
}
