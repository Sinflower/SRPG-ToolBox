/*
 *  File: CHOICEDATA.cpp
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

#include "CHOICEDATA.h"
#include "../CMenuOperation.h"
#include "../Commands/SWITCHACTION.h"
#include "EDITDATA.h"

void CHOICEDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);
	this_4 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();

	if (g_ArcVersion < 0x432)
	{
		if (g_ArcVersion < 0x404)
			res = fw.ReadQWord(); // Skip the next 8 byte

		this_9.this_2 = new SWITCHACTION();
		this_9.this_2->init(fw);
	}
	else
	{
		this_8 = fw.ReadDWord();
		if (this_8)
			this_9.init(fw);
	}
}

void CHOICEDATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);
	fw.Write(this_4);
	fw.Write(this_6);
	fw.Write(this_7);

	if (g_ArcVersion < 0x432)
	{
		if (g_ArcVersion < 0x404)
			fw.Write(res);

		this_9.this_2->dump(fw);
	}
	else
	{
		fw.Write(this_8);
		if (this_8)
			this_9.dump(fw);
	}
}
