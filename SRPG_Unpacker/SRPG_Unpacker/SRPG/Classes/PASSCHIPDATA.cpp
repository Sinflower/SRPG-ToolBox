// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "PASSCHIPDATA.h"

void PASSCHIPDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	initMemData(this_15, fw);

	if (g_ArcVersion >= 0x441)
		this_14 = fw.ReadDWord();

	if (g_ArcVersion >= 0x465)
		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 0x487)
	{
		initMemData(this_41, fw);
		this_42 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion > 1277 && HIWORD(this_42))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}

	fw.ReadBytes(this_17.data(), 96);

	LEGENDDATA::init(fw);
}

void PASSCHIPDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_13);

	this_15.Write(fw);

	if (g_ArcVersion >= 0x441)
		fw.Write(this_14);

	if (g_ArcVersion >= 0x465)
		m_pTypeIDData1->dump(fw);

	if (g_ArcVersion >= 0x487)
	{
		this_41.Write(fw);
		fw.Write(this_42);
		m_pTypeIDData2->dump(fw);

		
		if (g_ArcVersion >= 1277 && HIWORD(this_42))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}

	fw.WriteBytes(this_17.data(), 96);

	LEGENDDATA::dump(fw);
}
