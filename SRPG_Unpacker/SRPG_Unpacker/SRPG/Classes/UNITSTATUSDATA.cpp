// Compatible up to v1.292

#include "UNITSTATUSDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void UNITSTATUSDATA::init(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_3  = fw.ReadDWord();
		this_4  = fw.ReadDWord();
		this_5  = fw.ReadDWord();
		this_6  = fw.ReadDWord();
		this_7  = fw.ReadDWord();
		this_8  = fw.ReadDWord();
		this_9  = fw.ReadDWord();
		this_10 = fw.ReadDWord();
		this_11 = fw.ReadDWord();
		this_12 = 0;
		this_13 = 0;
	}
	else
	{
		res = fw.ReadDWord();
		if (res)
		{
			this_3  = 0;
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
		}
		else
		{
			this_3  = fw.ReadDWord();
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
		}
	}
}

void UNITSTATUSDATA::dump(FileWriter& fw) const
{
	if (g_ArcVersion < 0x418)
	{
		fw.Write(this_3);
		fw.Write(this_4);
		fw.Write(this_5);
		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);
		fw.Write(this_11);
	}
	else
	{
		fw.Write(res);
		if (!res)
		{
			fw.Write(this_3);
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
		}
	}
}
