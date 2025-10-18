/*
 *  File: ORIGINALDATA.cpp
 *  Copyright (c) 2025 Sinflower
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

#include "ORIGINALDATA.h"
#include "../CMenuOperation.h"

void ORIGINALDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);
	LEGENDDATA::init(fw);

	fw.ReadArr(this_4);
	fw.ReadArr(this_5);
	this_6 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_7, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_6))
	{
		fw.ReadArr(this_8);
		fw.ReadArr(this_9);
		this_10 = fw.ReadDWord();
	}

	initMemData(this_11, fw);
}

void ORIGINALDATA::dump([[maybe_unused]] FileWriter& fw) const
{
	this_3.Write(fw);
	LEGENDDATA::dump(fw);

	fw.WriteArr(this_4);
	fw.WriteArr(this_5);
	fw.Write(this_6);

	this_7->Dump(fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_6))
	{
		fw.WriteArr(this_8);
		fw.WriteArr(this_9);
		fw.Write(this_10);
	}

	this_11.Write(fw);
}
