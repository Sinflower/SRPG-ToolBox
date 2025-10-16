/*
 *  File: UNITCONDITIONDATA.cpp
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

#include "UNITCONDITIONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void UNITCONDITIONDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion >= 0x488)
		this_8 = fw.ReadDWord();

	this_9 = fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_10.data(), 40);
		fw.ReadBytes(this_22.data(), 40);
	}
	else
	{
		fw.ReadBytes(this_10.data(), 48);
		fw.ReadBytes(this_22.data(), 48);
	}

	if (g_ArcVersion >= 0x41B)
		this_34 = fw.ReadDWord();

	this_38 = fw.ReadDWord();
	this_39 = fw.ReadDWord();
	this_40 = fw.ReadDWord();
	this_37 = fw.ReadDWord();

	if (g_ArcVersion >= 0x41D)
	{
		this_35 = fw.ReadDWord();
		allocAndSetCMenuOp(&pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_35))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
	else
	{
		this_30 = fw.ReadDWord();
		this_32 = fw.ReadDWord();
		allocAndSetCMenuOp(&this_29, SRPGClasses::TYPEIDDATA, fw);
		allocAndSetCMenuOp(&this_31, SRPGClasses::TYPEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x442)
	{
		this_41 = fw.ReadDWord();
		this_42 = fw.ReadDWord();
	}
}

void UNITCONDITIONDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion >= 0x488)
		fw.Write(this_8);

	fw.Write(this_9);

	if (g_ArcVersion < 0x418)
	{
		fw.WriteBytes(this_10.data(), 40);
		fw.WriteBytes(this_22.data(), 40);
	}
	else
	{
		fw.WriteBytes(this_10.data(), 48);
		fw.WriteBytes(this_22.data(), 48);
	}

	if (g_ArcVersion >= 0x41B)
		fw.Write(this_34);

	fw.Write(this_38);
	fw.Write(this_39);
	fw.Write(this_40);
	fw.Write(this_37);

	if (g_ArcVersion >= 0x41D)
	{
		fw.Write(this_35);
		pTypeIDData->Dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_35))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}
	else
	{
		fw.Write(this_30);
		fw.Write(this_32);
		this_29->Dump(fw);
		this_31->Dump(fw);
	}

	if (g_ArcVersion >= 0x442)
	{
		fw.Write(this_41);
		fw.Write(this_42);
	}
}
