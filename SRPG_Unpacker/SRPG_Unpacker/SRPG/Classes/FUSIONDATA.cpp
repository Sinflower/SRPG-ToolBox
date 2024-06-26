/*
 *  File: FUSIONDATA.cpp
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

#include "FUSIONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FUSIONDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();

	initMemData(this_10, fw);
	initMemData(this_11, fw);
	initMemData(this_12, fw);

	this_13 = fw.ReadDWord();
	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();

	if (g_ArcVersion < 0x41D)
	{
		this_16 = fw.ReadDWord();
		this_18 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
	}
	else
	{
		this_16 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_16))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}

		this_18 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_18))
		{
			fw.ReadBytes(this_133.data(), static_cast<DWORD>(this_133.size() * sizeof(DWORD)));
			fw.ReadBytes(this_134.data(), static_cast<DWORD>(this_134.size() * sizeof(DWORD)));
			this_135 = fw.ReadDWord();
		}
	}

	if (g_ArcVersion < 0x492)
	{
		if (g_ArcVersion < 0x491)
			fw.ReadBytes(this_20.data(), 88);
		else
			fw.ReadBytes(this_20.data(), 224);
	}
	else
		fw.ReadBytes(this_20.data(), 264);

	fw.ReadBytes(this_86.data(), 88);

	if (g_ArcVersion < 0x41B)
	{
		fw.ReadBytes(this_108.data(), 64);
		this_108[16] = 0;
	}
	else
		fw.ReadBytes(this_108.data(), 68);

	this_125 = fw.ReadDWord();
	this_126 = fw.ReadDWord();

	LEGENDDATA::init(fw);

	initMemData(this_127, fw);
}

void FUSIONDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);

	this_10.Write(fw);
	this_11.Write(fw);
	this_12.Write(fw);

	fw.Write(this_13);
	fw.Write(this_14);
	fw.Write(this_15);

	if (g_ArcVersion < 0x41D)
	{
		fw.Write(this_16);
		fw.Write(this_18);
		m_pTypeIDData1->dump(fw);
		m_pTypeIDData2->dump(fw);
	}
	else
	{
		fw.Write(this_16);
		m_pTypeIDData1->dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_16))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}

		fw.Write(this_18);
		m_pTypeIDData2->dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_18))
		{
			fw.WriteBytes(this_133.data(), static_cast<DWORD>(this_133.size() * sizeof(DWORD)));
			fw.WriteBytes(this_134.data(), static_cast<DWORD>(this_134.size() * sizeof(DWORD)));
			fw.Write(this_135);
		}
	}

	if (g_ArcVersion < 0x492)
	{
		if (g_ArcVersion < 0x491)
			fw.WriteBytes(this_20.data(), 88);
		else
			fw.WriteBytes(this_20.data(), 224);
	}
	else
		fw.WriteBytes(this_20.data(), 264);

	fw.WriteBytes(this_86.data(), 88);

	if (g_ArcVersion < 0x41B)
		fw.WriteBytes(this_108.data(), 64);
	else
		fw.WriteBytes(this_108.data(), 68);

	fw.Write(this_125);
	fw.Write(this_126);

	LEGENDDATA::dump(fw);

	this_127.Write(fw);
}
