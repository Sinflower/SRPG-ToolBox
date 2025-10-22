/*
 *  File: SUPPORTDATA.cpp
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

#include "SUPPORTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SUPPORTDATA::init(FileReader& fw)
{
	this_3  = fw.ReadDWord();
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	if (g_ArcVersion >= 1260)
		this_11 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_4, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1230)
		allocAndSetCMenuOp(&this_12, SRPGClasses::VARIABLECONDITIONDATA, fw);
	else if (g_ArcVersion >= 1043)
	{
		this_13 = fw.ReadDWord();
		if (this_13 != 0)
		{
			// Yes it looks like this is really correct ... -- I hate this engine sooo much
			fw.Seek(fw.GetOffset() - 4);
			fw.ReadBytesArr(this_14);
		}
	}
}

void SUPPORTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);

	if (g_ArcVersion >= 1260)
		fw.Write(this_11);

	this_4->Dump(fw);
	if (g_ArcVersion >= 1230)
		this_12->Dump(fw);
	else if (g_ArcVersion >= 1043)
	{
		fw.Write(this_13);
		if (this_13 != 0)
			fw.WriteBytesArr(this_14);
	}
	else if (g_writingProject)
	{
		// The editor does not contain the v1.043 check and expects at least one DWORD here
		fw.Write(0x0);
	}
}
