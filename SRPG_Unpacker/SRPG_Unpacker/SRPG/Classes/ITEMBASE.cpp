/*
 *  File: ITEMBASE.cpp
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

// Compatible up to v1.317

#include "ITEMBASE.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ITEMBASE::init(FileReader& fw)
{
	this_8  = fw.ReadDWord();
	uses    = fw.ReadDWord();
	this_37 = fw.ReadDWord();
	price   = fw.ReadDWord();
	weight  = fw.ReadDWord();
	this_34 = fw.ReadDWord();
	this_35 = fw.ReadDWord();

	sub_36E310(fw);

	allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

	sub_101AB0(fw);
	LEGENDDATA::init(fw);

	initMemData(this_41, fw);

	if (g_ArcVersion >= 1002)
		this_36 = fw.ReadDWord();

	if (g_ArcVersion >= 1188)
	{
		this_42 = fw.ReadDWord();
		initMemData(this_43, fw);
	}
}

void ITEMBASE::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(uses);
	fw.Write(this_37);
	fw.Write(price);
	fw.Write(weight);
	fw.Write(this_34);
	fw.Write(this_35);

	//////
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
		fw.Write(res1);
		if (!res1)
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

		fw.Write(res2);
		if (!res2)
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
	//////

	m_pTypeIDData1->Dump(fw);

	//////
	if (g_ArcVersion < 0x41D)
	{
		m_pTypeIDDataOld0->Dump(fw);
		m_pTypeIDDataOld1->Dump(fw);
	}
	else
	{
		fw.Write(this_39);
		m_pTypeIDData2->Dump(fw);
		if (g_ArcVersion >= 1277 && this_39)
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}
	//////

	LEGENDDATA::dump(fw);

	this_41.Write(fw);

	if (g_ArcVersion >= 0x3EA)
		fw.Write(this_36);

	if (g_ArcVersion >= 0x4A4)
	{
		fw.Write(this_42);
		this_43.Write(fw);
	}
}

void ITEMBASE::sub_101AB0(FileReader& fw)
{
	if (g_ArcVersion < 1053)
	{
		allocAndSetCMenuOp(&m_pTypeIDDataOld0, SRPGClasses::TYPEIDDATA, fw);
		allocAndSetCMenuOp(&m_pTypeIDDataOld1, SRPGClasses::TYPEIDDATA, fw);
	}
	else
	{
		this_39 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
		if (g_ArcVersion >= 1277 && this_39)
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
}

void ITEMBASE::sub_36E310(FileReader& fw)
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

		grothBonusHp  = fw.ReadDWord();
		grothBonusStr = fw.ReadDWord();
		grothBonusMag = fw.ReadDWord();
		grothBonusSkl = fw.ReadDWord();
		grothBonusSpd = fw.ReadDWord();
		grothBonusLck = fw.ReadDWord();
		grothBonusDef = fw.ReadDWord();
		grothBonusRes = fw.ReadDWord();
		grothBonusMov = fw.ReadDWord();
	}
	else
	{
		res1 = fw.ReadDWord();
		if (!res1)
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

		res2 = fw.ReadDWord();
		if (!res2)
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

void ITEMBASE::print(std::ostream& os) const
{
	LEGENDDATA::print(os);
	os << "==== ITEMBASE ====" << std::endl;
	os << "this_8:" << this_8 << std::endl;
	os << "Price:" << price << std::endl;
	os << "Uses:" << uses << std::endl;
	os << "Weight:" << weight << std::endl;
	os << "Param Bonus Hp:" << paramBonusHp << std::endl;
	os << "Param Bonus Str:" << paramBonusStr << std::endl;
	os << "Param Bonus Mag:" << paramBonusMag << std::endl;
	os << "Param Bonus Skl:" << paramBonusSkl << std::endl;
	os << "Param Bonus Spd:" << paramBonusSpd << std::endl;
	os << "Param Bonus Lck:" << paramBonusLck << std::endl;
	os << "Param Bonus Def:" << paramBonusDef << std::endl;
	os << "Param Bonus Res:" << paramBonusRes << std::endl;
	os << "Param Bonus Mov:" << paramBonusMov << std::endl;
	os << "Param Bonus Wlv:" << paramBonusWlv << std::endl;
	os << "Param Bonus Bld:" << paramBonusBld << std::endl;
	os << "Groth Bonus Hp:" << grothBonusHp << std::endl;
	os << "Groth Bonus Str:" << grothBonusStr << std::endl;
	os << "Groth Bonus Mag:" << grothBonusMag << std::endl;
	os << "Groth Bonus Skl:" << grothBonusSkl << std::endl;
	os << "Groth Bonus Spd:" << grothBonusSpd << std::endl;
	os << "Groth Bonus Lck:" << grothBonusLck << std::endl;
	os << "Groth Bonus Def:" << grothBonusDef << std::endl;
	os << "Groth Bonus Res:" << grothBonusRes << std::endl;
	os << "Groth Bonus Mov:" << grothBonusMov << std::endl;
	os << "Groth Bonus Wlv:" << grothBonusWlv << std::endl;
	os << "Groth Bonus Bld:" << grothBonusBld << std::endl;
	os << "this_34 :" << this_34 << std::endl;
	os << "this_35 :" << this_35 << std::endl;
	os << "this_36 :" << this_36 << std::endl;
	os << "this_37 :" << this_37 << std::endl;
	os << "this_39 :" << this_39 << std::endl;
	os << "this_41 :" << this_41 << std::endl;
	os << "this_42 :" << this_42 << std::endl;
	os << "this_43 :" << this_43 << std::endl;
	os << "==== ITEMBASE ====" << std::endl;
}
