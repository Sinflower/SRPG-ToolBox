// Compatible up to v1.292

#include "MAPPOSCHOOSE.h"
#include "../CMenuOperation.h"

void MAPPOSCHOOSE::init(FileReader& fw)
{
	if (g_ArcVersion < 1256)
		this_3.resize(6);
	else
		this_3.resize(7);

	fw.ReadBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));

	fw.ReadBytes(this_10.data(), static_cast<DWORD>(this_10.size() * sizeof(DWORD)));

	this_19 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_20, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_19))
	{
		fw.ReadBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.ReadBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));
		this_26 = fw.ReadDWord();
	}

	this_21 = fw.ReadDWord();
	this_22 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_23, SRPGClasses::TYPEIDDATA, fw);
}

void MAPPOSCHOOSE::dump(FileWriter& fw) const
{
	fw.WriteBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));

	fw.WriteBytes(this_10.data(), static_cast<DWORD>(this_10.size() * sizeof(DWORD)));

	fw.Write(this_19);

	if (g_ArcVersion >= 1277 && HIWORD(this_19))
	{
		fw.WriteBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.WriteBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));
		fw.Write(this_26);
	}

	this_20->dump(fw);

	fw.Write(this_21);
	fw.Write(this_22);

	this_23->dump(fw);
}
