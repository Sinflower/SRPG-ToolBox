// Compatible up to v1.292

#include "PARAMATERCHANGE.h"

void PARAMATERCHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	sub_EBE310(fw);

	this_15 = fw.ReadDWord();
}

void PARAMATERCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);

	//////

	if (g_ArcVersion < 0x418)
	{
		fw.Write(this_4);
		fw.Write(this_5);
		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);
		fw.Write(this_11);
		fw.Write(this_12);
	}
	else
	{
		fw.Write(res);

		if (!res)
		{
			fw.Write(this_4);
			fw.Write(this_5);
			fw.Write(this_6);
			fw.Write(this_7);
			fw.Write(this_8);
			fw.Write(this_9);
			fw.Write(this_10);
			fw.Write(this_11);
			fw.Write(this_12);
			fw.Write(this_13);
			fw.Write(this_14);
		}
	}

	//////

	fw.Write(this_15);
}

void PARAMATERCHANGE::sub_EBE310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_4  = fw.ReadDWord();
		this_5  = fw.ReadDWord();
		this_6  = fw.ReadDWord();
		this_7  = fw.ReadDWord();
		this_8  = fw.ReadDWord();
		this_9  = fw.ReadDWord();
		this_10 = fw.ReadDWord();
		this_11 = fw.ReadDWord();
		this_12 = fw.ReadDWord();
	}
	else
	{
		res = fw.ReadDWord();

		if (res)
		{
			this_4  = 0;
			this_5  = 0;
			this_6  = 0;
			this_7  = 0;
			this_8  = 0;
			this_9  = 0;
			this_10 = 0;
			this_11 = 0;
			this_12 = 0;
			this_13 = 0;
			this_14 = 0;
		}
		else
		{
			this_4  = fw.ReadDWord();
			this_5  = fw.ReadDWord();
			this_6  = fw.ReadDWord();
			this_7  = fw.ReadDWord();
			this_8  = fw.ReadDWord();
			this_9  = fw.ReadDWord();
			this_10 = fw.ReadDWord();
			this_11 = fw.ReadDWord();
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
		}
	}
}
