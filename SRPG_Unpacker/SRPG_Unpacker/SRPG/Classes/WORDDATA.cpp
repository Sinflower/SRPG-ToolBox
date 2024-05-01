/*
 *  File: WORDDATA.cpp
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

#include "WORDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void WORDDATA::init(FileReader& fw)
{
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	initMemData(this_8, fw);
	allocAndSetCMenuOp(&pDictionaryCondition, SRPGClasses::DICTIONARYCONDITION, fw);

	LEGENDDATA::init(fw);

	if (g_ArcVersion >= 0x48D)
	{
		this_10 = fw.ReadDWord();
		this_11 = fw.ReadDWord();
	}
}

void WORDDATA::dump(FileWriter& fw) const
{
	fw.Write(this_12);
	fw.Write(this_13);

	this_8.Write(fw);
	pDictionaryCondition->dump(fw);

	LEGENDDATA::dump(fw);

	if (g_ArcVersion >= 0x48D)
	{
		fw.Write(this_10);
		fw.Write(this_11);
	}
}
