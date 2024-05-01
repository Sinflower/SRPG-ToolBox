// Compatible up to v1.292

#include "UNITALLCOMMAND.h"
#include "../CMenuOperation.h"

void UNITALLCOMMAND::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (this_7 != -1)
	{
		this_10 = createCommand(this_7);
		this_10->init(fw);
	}

	this_8 = fw.ReadDWord();

	allocAndSetCMenuOp(&pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
	if (g_ArcVersion >= 1277 && HIWORD(this_8))
	{
		fw.ReadBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.ReadBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));
		this_26 = fw.ReadDWord();
	}

	if (g_ArcVersion < 1256)
	{
		if (g_ArcVersion < 1134)
		{
			this_11 = 0;
			this_12 = 0;
			this_13 = 0;
			this_14 = 0;
			this_15 = 2;
			this_16 = 1;
		}
		else
		{
			this_11 = fw.ReadDWord();
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
			this_15 = fw.ReadDWord();
			this_16 = fw.ReadDWord();
		}
		this_17 = 0;
	}
	else
	{
		this_11 = fw.ReadDWord();
		this_12 = fw.ReadDWord();
		this_13 = fw.ReadDWord();
		this_14 = fw.ReadDWord();
		this_15 = fw.ReadDWord();
		this_16 = fw.ReadDWord();
		this_17 = fw.ReadDWord();
	}
}

void UNITALLCOMMAND::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	if (this_7 != -1)
	{
		this_10->dump(fw);
	}

	fw.Write(this_8);

	pTypeIDData->dump(fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_8))
	{
		fw.WriteBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.WriteBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));

		if (g_ArcVersion >= 1051)
			fw.Write(this_26);
	}

	if (g_ArcVersion < 1256)
	{
		if (g_ArcVersion >= 1134)
		{
			fw.Write(this_11);
			fw.Write(this_12);
			fw.Write(this_13);
			fw.Write(this_14);
			fw.Write(this_15);
			fw.Write(this_16);
		}
	}
	else
	{
		fw.Write(this_11);
		fw.Write(this_12);
		fw.Write(this_13);
		fw.Write(this_14);
		fw.Write(this_15);
		fw.Write(this_16);
		fw.Write(this_17);
	}
}
