/*
 *  File: CLASSDATA.cpp
 *  Copyright (c) 2024 Sinflower
 *
 *  MIT License
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

// Compatible up to v1.292

#include "CLASSDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"
#include "UNITPROTOTYPEDATA.h"

void CLASSDATA::init(FileReader& fw)
{
	this_8      = fw.ReadDWord();
	this_9      = fw.ReadDWord();
	optionalExp = fw.ReadDWord();
	this_12     = fw.ReadDWord();
	this_13     = fw.ReadDWord();
	this_18     = fw.ReadDWord();
	this_19     = fw.ReadDWord();

	if (g_ArcVersion >= 0x41D)
	{
		if (g_ArcVersion < 0x461)
		{
			DWORD v19 = fw.ReadDWord();
			NOT_IMPLEMENTED
			/*
			v6 = *(_DWORD **)(this + 96);

			Sizea = (*(int (__thiscall **)(_DWORD *))*v6)(v6);
			*(_DWORD *)(Sizea + 8) = sub_381340(v6);
			v7 = v6[1];
			v8 = v7 + 4;
			if ( *(_DWORD *)(v7 + 4) )
			{
				do
				{
					v7 = *(_DWORD *)v8;
					v9 = *(_DWORD *)(*(_DWORD *)v8 + 4) == 0;
					v8 = *(_DWORD *)v8 + 4;
				}
				while ( !v9 );
			}
			*(_DWORD *)(v7 + 4) = Sizea;
			*(_DWORD *)(Sizea + 12) = v19;
			*/
		}
		else
			allocAndSetCMenuOp(&m_pTypeIDData3, SRPGClasses::TYPEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x42A)
		this_20 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
	allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

	sub_36E310(fw);

	this_25 = fw.ReadDWord();

	sub_35FF20(fw, this_9);

	allocAndSetCMenuOp(&m_pUnitStatusData, SRPGClasses::UNITSTATUSDATA, fw);

	if (!m_pUnitPrototypeData)
		m_pUnitPrototypeData = new UNITPROTOTYPEDATA();
	else
	{
		std::cerr << __FILE__ << ":" << __LINE__ << " : " << __FUNCTION__ << " : "
				  << "m_pUnitPrototypeData is not null, this needs to be checked, as there might be a different function call requried" << std::endl;
		// might require a call to m_pUnitPrototypeData->init()
		// but m_pUnitPrototypeData might actually not be a UNITPROTOTYPEDATA object
		exit(-1);
	}

	/////////////////////////////////////////////
	// Init for UNITPROTOTYPEDATA
	m_pUnitPrototypeData->init(fw);
	//////////////////////////////////////////////

	sub_360EA0(fw);

	initMemData(this_76, fw);

	LEGENDDATA::init(fw);
}

void CLASSDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(optionalExp);
	fw.Write(this_12);
	fw.Write(this_13);
	fw.Write(this_18);
	fw.Write(this_19);

	if (g_ArcVersion >= 0x41D)
	{
		if (g_ArcVersion < 0x461)
		{
			NOT_IMPLEMENTED
			/*
			DWORD v19 = fw.ReadDWord();
			v6 = *(_DWORD **)(this + 96);

			Sizea = (*(int (__thiscall **)(_DWORD *))*v6)(v6);
			*(_DWORD *)(Sizea + 8) = sub_381340(v6);
			v7 = v6[1];
			v8 = v7 + 4;
			if ( *(_DWORD *)(v7 + 4) )
			{
			do
			{
			v7 = *(_DWORD *)v8;
			v9 = *(_DWORD *)(*(_DWORD *)v8 + 4) == 0;
			v8 = *(_DWORD *)v8 + 4;
			}
			while ( !v9 );
			}
			*(_DWORD *)(v7 + 4) = Sizea;
			*(_DWORD *)(Sizea + 12) = v19;
			*/
		}
		else
			m_pTypeIDData3->Dump(fw);
	}

	if (g_ArcVersion >= 0x42A)
		fw.Write(this_20);

	m_pTypeIDData2->Dump(fw);
	m_pTypeIDData1->Dump(fw);

	/////

	if (g_ArcVersion < 0x418)
	{
		fw.Write(paramBonusHp);
		fw.Write(paramBonusStr);
		fw.Write(paramBonusMag);
		fw.Write(paramBonusSkl);
		fw.Write(paramBonusSpd);
		fw.Write(paramBonusLck);
		fw.Write(paramBonusDef);
		fw.Write(paramBonusRes);
		fw.Write(paramBonusMov);
		fw.Write(grothBonusHp);
		fw.Write(grothBonusStr);
		fw.Write(grothBonusMag);
		fw.Write(grothBonusSkl);
		fw.Write(grothBonusSpd);
		fw.Write(grothBonusLck);
		fw.Write(grothBonusDef);
		fw.Write(grothBonusRes);
		fw.Write(grothBonusMov);
	}
	else
	{
		fw.Write(res2);
		if (!res2)
		{
			fw.Write(paramBonusHp);
			fw.Write(paramBonusStr);
			fw.Write(paramBonusMag);
			fw.Write(paramBonusSkl);
			fw.Write(paramBonusSpd);
			fw.Write(paramBonusLck);
			fw.Write(paramBonusDef);
			fw.Write(paramBonusRes);
			fw.Write(paramBonusMov);
			fw.Write(paramBonusWlv);
			fw.Write(paramBonusBld);
		}

		fw.Write(res3);
		if (!res3)
		{
			fw.Write(grothBonusHp);
			fw.Write(grothBonusStr);
			fw.Write(grothBonusMag);
			fw.Write(grothBonusSkl);
			fw.Write(grothBonusSpd);
			fw.Write(grothBonusLck);
			fw.Write(grothBonusDef);
			fw.Write(grothBonusRes);
			fw.Write(grothBonusMov);
			fw.Write(grothBonusWlv);
			fw.Write(grothBonusBld);
		}
	}

	/////

	fw.Write(this_25);

	/////

	if (g_ArcVersion < 0x43F)
	{
		NOT_IMPLEMENTED
		/*
		lpMem = 0;
		v12 = 0;
		v13 = 0;
		sub_360240(&lpMem, a3);
		sub_3602E0(&lpMem, a2, (void*)a3);
		sub_360010(&lpMem, this);
		if (lpMem)
		{
		v8 = lpMem;
		v5 = GetProcessHeap();
		HeapFree(v5, 0, v8);
		}
		if (v12)
		{
		v9 = v12;
		v6 = GetProcessHeap();
		HeapFree(v6, 0, v9);
		}
		result = (int*)v13;
		if (v13)
		{
		v10 = v13;
		v7 = GetProcessHeap();
		result = (int*)HeapFree(v7, 0, v10);
		}
		*/
	}
	else
	{
		m_pMotionIDData1->Dump(fw);
		m_pMotionIDData2->Dump(fw);
		m_pMotionIDData3->Dump(fw);
	}

	/////

	m_pUnitStatusData->Dump(fw);

	/////////////////////////////////////////////
	// Init for UNITPROTOTYPEDATA
	m_pUnitPrototypeData->dump(fw);
	//////////////////////////////////////////////

	/////

	if (g_ArcVersion >= 0x3F3)
	{
		if (g_ArcVersion < 0x418)
		{
			fw.WriteBytes(this_53.data(), 36);
		}
		else
			fw.WriteBytes(this_53.data(), 44);
	}

	if (g_ArcVersion >= 0x3FA)
	{
		fw.Write(this_14);
		fw.Write(this_15);
		fw.Write(this_16);
		fw.Write(this_17);
	}

	if (g_ArcVersion >= 0x40C)
		fw.Write(this_64);

	if (g_ArcVersion >= 0x418)
	{
		if (g_ArcVersion < 0x418)
		{
			fw.Write(this_65);
			fw.Write(this_66);
			fw.Write(this_67);
			fw.Write(this_68);
			fw.Write(this_69);
			fw.Write(this_70);
			fw.Write(this_71);
			fw.Write(this_72);
			fw.Write(this_73);
		}
		else
		{
			fw.Write(res1);
			if (!res1)
			{
				fw.Write(this_65);
				fw.Write(this_66);
				fw.Write(this_67);
				fw.Write(this_68);
				fw.Write(this_69);
				fw.Write(this_70);
				fw.Write(this_71);
				fw.Write(this_72);
				fw.Write(this_73);
				fw.Write(this_74);
				fw.Write(this_75);
			}
		}
	}

	if (g_ArcVersion >= 0x443)
		m_pCharReplaceData->Dump(fw);

	if (g_ArcVersion >= 0x4A4)
	{
		fw.Write(this_78);
		this_79.Write(fw);
	}

	/////

	this_76.Write(fw);

	LEGENDDATA::dump(fw);
}

void CLASSDATA::sub_360EA0(FileReader& fw)
{
	if (g_ArcVersion < 0x3F3)
		memset(this_53.data(), 0, 44);
	else
	{
		if (g_ArcVersion < 0x418)
		{
			fw.ReadBytes(this_53.data(), 36);
			this_53[9]  = 30;
			this_53[10] = 30;
		}
		else
			fw.ReadBytes(this_53.data(), 44);
	}

	if (g_ArcVersion < 0x3FA)
	{
		this_14 = 0;
		this_15 = 0x20000;
		this_16 = 0;
		this_17 = 0x20000;
		if (this_9)
		{
			if (this_9 == 1)
			{
				this_14 = this_12;
				this_9  = 2;
				this_15 = this_13;
				this_12 = 0;
				this_13 = 0x20000;
			}
			else if (this_9 == 2)
			{
				this_16 = this_12;
				this_9  = 4;
				this_17 = this_13;
				this_12 = 0;
				this_13 = 0x20000;
			}
			else
				this_9 = 0;
		}
		else
			this_9 = 1;
	}
	else
	{
		this_14 = fw.ReadDWord();
		this_15 = fw.ReadDWord();
		this_16 = fw.ReadDWord();
		this_17 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x40C)
		this_64 = -1;
	else
		this_64 = fw.ReadDWord();

	if (g_ArcVersion >= 0x418)
		sub_37E310(fw);

	if (g_ArcVersion >= 0x443)
		allocAndSetCMenuOp(&m_pCharReplaceData, SRPGClasses::CHARREPLACEDATA, fw);

	if (g_ArcVersion >= 0x4A4)
	{
		this_78 = fw.ReadDWord();
		initMemData(this_79, fw);
	}
}

void CLASSDATA::sub_37E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_65 = fw.ReadDWord();
		this_66 = fw.ReadDWord();
		this_67 = fw.ReadDWord();
		this_68 = fw.ReadDWord();
		this_69 = fw.ReadDWord();
		this_70 = fw.ReadDWord();
		this_71 = fw.ReadDWord();
		this_72 = fw.ReadDWord();
		this_73 = fw.ReadDWord();

		this_74 = 0;
		this_75 = 0;
	}
	else
	{
		res1 = fw.ReadDWord();
		if (res1)
		{
			this_65 = 0;
			this_66 = 0;
			this_67 = 0;
			this_68 = 0;
			this_69 = 0;
			this_70 = 0;
			this_71 = 0;
			this_72 = 0;
			this_73 = 0;
			this_74 = 0;
			this_75 = 0;
		}
		else
		{
			this_65 = fw.ReadDWord();
			this_66 = fw.ReadDWord();
			this_67 = fw.ReadDWord();
			this_68 = fw.ReadDWord();
			this_69 = fw.ReadDWord();
			this_70 = fw.ReadDWord();
			this_71 = fw.ReadDWord();
			this_72 = fw.ReadDWord();
			this_73 = fw.ReadDWord();
			this_74 = fw.ReadDWord();
			this_75 = fw.ReadDWord();
		}
	}
}
void CLASSDATA::sub_36E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		paramBonusHp  = fw.ReadDWord();
		paramBonusStr = fw.ReadDWord();
		paramBonusMag = fw.ReadDWord();
		paramBonusSkl = fw.ReadDWord();
		paramBonusSpd = fw.ReadDWord();
		paramBonusLck = fw.ReadDWord();
		paramBonusDef = fw.ReadDWord();
		paramBonusRes = fw.ReadDWord();
		paramBonusMov = fw.ReadDWord();
		paramBonusWlv = 0;
		paramBonusBld = 0;
		grothBonusHp  = fw.ReadDWord();
		grothBonusStr = fw.ReadDWord();
		grothBonusMag = fw.ReadDWord();
		grothBonusSkl = fw.ReadDWord();
		grothBonusSpd = fw.ReadDWord();
		grothBonusLck = fw.ReadDWord();
		grothBonusDef = fw.ReadDWord();
		grothBonusRes = fw.ReadDWord();
		grothBonusMov = fw.ReadDWord();
		grothBonusWlv = 0;
		grothBonusBld = 0;
	}
	else
	{
		res2 = fw.ReadDWord();
		if (res2)
		{
			paramBonusHp  = 0;
			paramBonusStr = 0;
			paramBonusMag = 0;
			paramBonusSkl = 0;
			paramBonusSpd = 0;
			paramBonusLck = 0;
			paramBonusDef = 0;
			paramBonusRes = 0;
			paramBonusMov = 0;
			paramBonusWlv = 0;
			paramBonusBld = 0;
		}
		else
		{
			paramBonusHp  = fw.ReadDWord();
			paramBonusStr = fw.ReadDWord();
			paramBonusMag = fw.ReadDWord();
			paramBonusSkl = fw.ReadDWord();
			paramBonusSpd = fw.ReadDWord();
			paramBonusLck = fw.ReadDWord();
			paramBonusDef = fw.ReadDWord();
			paramBonusRes = fw.ReadDWord();
			paramBonusMov = fw.ReadDWord();
			paramBonusWlv = fw.ReadDWord();
			paramBonusBld = fw.ReadDWord();
		}

		res3 = fw.ReadDWord();
		if (res3)
		{
			grothBonusHp  = 0;
			grothBonusStr = 0;
			grothBonusMag = 0;
			grothBonusSkl = 0;
			grothBonusSpd = 0;
			grothBonusLck = 0;
			grothBonusDef = 0;
			grothBonusRes = 0;
			grothBonusMov = 0;
			grothBonusWlv = 0;
			grothBonusBld = 0;
		}
		else
		{
			grothBonusHp  = fw.ReadDWord();
			grothBonusStr = fw.ReadDWord();
			grothBonusMag = fw.ReadDWord();
			grothBonusSkl = fw.ReadDWord();
			grothBonusSpd = fw.ReadDWord();
			grothBonusLck = fw.ReadDWord();
			grothBonusDef = fw.ReadDWord();
			grothBonusRes = fw.ReadDWord();
			grothBonusMov = fw.ReadDWord();
			grothBonusWlv = fw.ReadDWord();
			grothBonusBld = fw.ReadDWord();
		}
	}
}
void CLASSDATA::sub_35FF20(FileReader& fw, int a3)
{
	if (g_ArcVersion < 0x43F)
	{
		NOT_IMPLEMENTED
		/*
		lpMem = 0;
		v12 = 0;
		v13 = 0;
		sub_360240(&lpMem, a3);
		sub_3602E0(&lpMem, a2, (void*)a3);
		sub_360010(&lpMem, this);
		if (lpMem)
		{
			v8 = lpMem;
			v5 = GetProcessHeap();
			HeapFree(v5, 0, v8);
		}
		if (v12)
		{
			v9 = v12;
			v6 = GetProcessHeap();
			HeapFree(v6, 0, v9);
		}
		result = (int*)v13;
		if (v13)
		{
			v10 = v13;
			v7 = GetProcessHeap();
			result = (int*)HeapFree(v7, 0, v10);
		}
		*/
	}
	else
	{
		allocAndSetCMenuOp(&m_pMotionIDData1, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData2, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData3, SRPGClasses::MOTIONIDDATA, fw);
	}
}

void CLASSDATA::print(std::ostream& os) const
{
	os << "CLASSDATA" << std::endl;
	LEGENDDATA::print(os);
	os << "this_8 : " << this_8 << std::endl;
	os << "this_9 : " << this_9 << std::endl;
	os << "Optional Exp: " << optionalExp << std::endl;
	os << "this_12: " << this_12 << std::endl;
	os << "this_13: " << this_13 << std::endl;
	os << "this_14: " << this_14 << std::endl;
	os << "this_15: " << this_15 << std::endl;
	os << "this_16: " << this_16 << std::endl;
	os << "this_17: " << this_17 << std::endl;
	os << "this_18: " << this_18 << std::endl;
	os << "this_19: " << this_19 << std::endl;
	os << "this_20: " << this_20 << std::endl;
	os << "this_25: " << this_25 << std::endl;
	os << "Param Bonus Hp: " << paramBonusHp << std::endl;
	os << "Param Bonus Str: " << paramBonusStr << std::endl;
	os << "Param Bonus Mag: " << paramBonusMag << std::endl;
	os << "Param Bonus Skl: " << paramBonusSkl << std::endl;
	os << "Param Bonus Spd: " << paramBonusSpd << std::endl;
	os << "Param Bonus Lck: " << paramBonusLck << std::endl;
	os << "Param Bonus Def: " << paramBonusDef << std::endl;
	os << "Param Bonus Res: " << paramBonusRes << std::endl;
	os << "Param Bonus Mov: " << paramBonusMov << std::endl;
	os << "Param Bonus Wlv: " << paramBonusWlv << std::endl;
	os << "Param Bonus Bld: " << paramBonusBld << std::endl;
	os << "Groth Bonus Hp: " << grothBonusHp << std::endl;
	os << "Groth Bonus Str: " << grothBonusStr << std::endl;
	os << "Groth Bonus Mag: " << grothBonusMag << std::endl;
	os << "Groth Bonus Skl: " << grothBonusSkl << std::endl;
	os << "Groth Bonus Spd: " << grothBonusSpd << std::endl;
	os << "Groth Bonus Lck: " << grothBonusLck << std::endl;
	os << "Groth Bonus Def: " << grothBonusDef << std::endl;
	os << "Groth Bonus Res: " << grothBonusRes << std::endl;
	os << "Groth Bonus Mov: " << grothBonusMov << std::endl;
	os << "Groth Bonus Wlv: " << grothBonusWlv << std::endl;
	os << "Groth Bonus Bld: " << grothBonusBld << std::endl;
	os << "this_64: " << this_64 << std::endl;
	os << "this_65: " << this_65 << std::endl;
	os << "this_66: " << this_66 << std::endl;
	os << "this_67: " << this_67 << std::endl;
	os << "this_68: " << this_68 << std::endl;
	os << "this_69: " << this_69 << std::endl;
	os << "this_70: " << this_70 << std::endl;
	os << "this_71: " << this_71 << std::endl;
	os << "this_72: " << this_72 << std::endl;
	os << "this_73: " << this_73 << std::endl;
	os << "this_74: " << this_74 << std::endl;
	os << "this_75: " << this_75 << std::endl;

	std::cout << "this_53-63:" << std::endl;
	for (const DWORD& d : this_53)
		os << d << std::endl;
}
