/*
 *  File: WEAPONDATA.cpp
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

#include "WEAPONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void WEAPONDATA::init(FileReader& fw)
{
	ITEMBASE::init(fw);

	this_50     = fw.ReadDWord();
	mt          = fw.ReadDWord();
	rangeStart  = fw.ReadDWord();
	rangeEnd    = fw.ReadDWord();
	hit         = fw.ReadDWord();
	crt         = fw.ReadDWord();
	attackCount = fw.ReadDWord();

	if (g_ArcVersion >= 1048)
		weaponLevel = fw.ReadDWord();

	this_58 = fw.ReadDWord();
	this_62 = fw.ReadDWord();
	this_63 = fw.ReadDWord();

	this_60 = fw.ReadDWord();
	this_61 = fw.ReadDWord();

	sub_102390(fw);

	this_66 = fw.ReadDWord();

	sub_FFF20(fw);

	sub_102420(fw);
}

void WEAPONDATA::dump(FileWriter& fw) const
{
	ITEMBASE::dump(fw);

	fw.Write(this_50);
	fw.Write(mt);
	fw.Write(rangeStart);
	fw.Write(rangeEnd);
	fw.Write(hit);
	fw.Write(crt);
	fw.Write(attackCount);

	if (g_ArcVersion >= 1048)
		fw.Write(weaponLevel);

	fw.Write(this_58);
	fw.Write(this_62);
	fw.Write(this_63);

	fw.Write(this_60);
	fw.Write(this_61);

	if (g_ArcVersion < 1053)
		m_pTypeIDData3->Dump(fw);
	else
	{
		fw.Write(this_64);
		m_pTypeIDData3->Dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_64))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}

	fw.Write(this_66);

	dump_sub_FFF20(fw);

	//////
	if (g_ArcVersion >= 1003)
		fw.Write(this_70);

	if (g_ArcVersion >= 1024)
	{
		fw.Write(this_71);
		fw.Write(this_72);
		fw.Write(this_73);
	}

	if (g_ArcVersion >= 1030)
	{
		if (g_ArcVersion < 1087)
		{
			fw.Write(res);
			if (res)
				fw.WriteBytes(old_4.data(), static_cast<DWORD>(old_4.size() * sizeof(DWORD)));
		}
		else
		{
			m_pImageIDData1->Dump(fw);
			m_pImageIDData2->Dump(fw);
		}
	}
	//////
}

void WEAPONDATA::sub_102420(FileReader& fw)
{
	if (g_ArcVersion >= 1003)
		this_70 = fw.ReadDWord();

	if (g_ArcVersion >= 1024)
	{
		this_71 = fw.ReadDWord();
		this_72 = fw.ReadDWord();
		this_73 = fw.ReadDWord();
	}

	if (g_ArcVersion < 1030)
	{
		m_pImageIDData1 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		m_pImageIDData2 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	}
	else
		sub_100680(fw);
}

void WEAPONDATA::sub_100680(FileReader& fw)
{
	if (g_ArcVersion < 1087)
	{
		res = fw.ReadDWord();
		if (res)
			fw.ReadBytes(old_4.data(), static_cast<DWORD>(old_4.size() * sizeof(DWORD)));
		else
		{
			m_pImageIDData1 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
			m_pImageIDData2 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		}
	}
	else
	{
		allocAndSetCMenuOp(&m_pImageIDData1, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&m_pImageIDData2, SRPGClasses::IMAGEIDDATA, fw);
	}
}

void WEAPONDATA::sub_FFF20(FileReader& fw)
{
	if (g_ArcVersion < 1087)
	{
		const DWORD size_1034_up[] = { 18, 7, 7 };
		const DWORD size_1033[]    = { 15, 7, 7 };
		const DWORD size_older[]   = { 11, 5, 5 };

		const DWORD* sizes = nullptr;
		if (g_ArcVersion >= 1034)
			sizes = size_1034_up;
		else if (g_ArcVersion == 1033)
			sizes = size_1033;
		else
			sizes = size_older;

		old_0.resize(sizes[0]);
		old_1.resize(sizes[1]);
		old_2.resize(sizes[2]);

		if (this_50 == 0)
			fw.ReadBytes(old_0.data(), sizes[0] * sizeof(DWORD));
		if (this_50 == 1)
			fw.ReadBytes(old_1.data(), sizes[1] * sizeof(DWORD));
		if (this_50 == 2)
			fw.ReadBytes(old_2.data(), sizes[2] * sizeof(DWORD));
	}
	else
	{
		allocAndSetCMenuOp(&m_pMotionIDData1, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData2, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData3, SRPGClasses::MOTIONIDDATA, fw);
	}
}

void WEAPONDATA::dump_sub_FFF20(FileWriter& fw) const
{
	if (g_ArcVersion < 1087)
	{
		if (this_50 == 0)
			fw.WriteBytes(old_0.data(), static_cast<DWORD>(old_0.size() * 4));
		if (this_50 == 1)
			fw.WriteBytes(old_1.data(), static_cast<DWORD>(old_1.size() * 4));
		if (this_50 == 2)
			fw.WriteBytes(old_2.data(), static_cast<DWORD>(old_2.size() * 4));
	}
	else
	{
		m_pMotionIDData1->Dump(fw);
		m_pMotionIDData2->Dump(fw);
		m_pMotionIDData3->Dump(fw);
	}
}

void WEAPONDATA::sub_102390(FileReader& fw)
{
	if (g_ArcVersion < 1053)
		allocAndSetCMenuOp(&m_pTypeIDData3, SRPGClasses::TYPEIDDATA, fw);
	else
	{
		this_64 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData3, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_64))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
}

void WEAPONDATA::print(std::ostream& os) const
{
	os << "WEAPONDATA" << std::endl;
	ITEMBASE::print(os);
	os << "this_50: " << this_50 << std::endl;
	os << "Mt: " << mt << std::endl;
	os << "Range Start: " << rangeStart << std::endl;
	os << "Range End: " << rangeEnd << std::endl;
	os << "Hit: " << hit << std::endl;
	os << "Crt: " << crt << std::endl;
	os << "Attack Count: " << attackCount << std::endl;
	os << "Weapon Level: " << weaponLevel << std::endl;
	os << "this_58: " << this_58 << std::endl;
	os << "this_60: " << this_60 << std::endl;
	os << "this_61: " << this_61 << std::endl;
	os << "this_62: " << this_62 << std::endl;
	os << "this_63: " << this_63 << std::endl;
	os << "this_64: " << this_64 << std::endl;
	os << "this_66: " << this_66 << std::endl;
	os << "this_70: " << this_70 << std::endl;
	os << "this_71: " << this_71 << std::endl;
	os << "this_72: " << this_72 << std::endl;
	os << "this_73: " << this_73 << std::endl;
}