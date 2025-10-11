/*
 *  File: PATTERNDATA.cpp
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

#include "PATTERNDATA.h"
#include "../CMenuOperation.h"
#include "APPROACHPATTERN.h"
#include "CUSTOMPATTERN.h"
#include "EDITDATA.h"
#include "MOVEPATTERN.h"
#include "WAITPATTERN.h"

void PATTERNDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();

	if (this_4)
		this_5.init(fw);

	switch (this_3)
	{
		case 0:
			this_7         = new APPROACHPATTERN();
			this_7->this_1 = fw.ReadDWord(); // This is what happens in the init function ... might want to implement that
			break;
		case 1:
			this_8         = new WAITPATTERN();
			this_8->this_1 = fw.ReadDWord(); // This is what happens in the init function ... might want to implement that
			break;
		case 2:
			this_9 = new MOVEPATTERN();
			this_9->init(fw);
			break;
		case 100:
			this_10 = new CUSTOMPATTERN();
			this_10->init(fw);
			break;
		default:
			break;
	}

	this_12 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_11, SRPGClasses::TYPEIDDATA, fw);

	this_13 = fw.ReadDWord();

	if (g_ArcVersion < 0x424)
	{
		if (this_13)
			this_13 = 2;
	}
	else
	{
		this_14 = fw.ReadDWord();
		allocAndSetCMenuOp(&this_15, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_14))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}

	if (g_ArcVersion >= 0x40D)
	{
		this_16 = fw.ReadDWord();
		allocAndSetCMenuOp(&this_17, SRPGClasses::RPASSDATA, fw);
	}
}

void PATTERNDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);

	if (this_4)
		this_5.dump(fw);

	switch (this_3)
	{
		case 0:
			fw.Write(this_7->this_1);
			break;
		case 1:
			fw.Write(this_8->this_1);
			break;
		case 2:
			this_9->dump(fw);
			break;
		case 100:
			this_10->dump(fw);
			break;
		default:
			break;
	}

	fw.Write(this_12);

	this_11->Dump(fw);

	fw.Write(this_13);

	if (g_ArcVersion >= 0x424)
	{
		fw.Write(this_14);
		this_15->Dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_14))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}

	if (g_ArcVersion >= 0x40D)
	{
		fw.Write(this_16);
		this_17->Dump(fw);
	}
}
