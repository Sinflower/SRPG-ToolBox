/*
 *  File: CHARREPLACEDATA.cpp
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

#include "CHARREPLACEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void CHARREPLACEDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	initMemData(this_6, fw);
	this_7 = fw.ReadDWord();
	allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1277)
	{
		if (HIWORD(this_7))
		{
			fw.ReadBytesArr(this_9);

			if (g_ArcVersion >= 1048)
			{
				this_10 = fw.ReadDWord();
				this_11 = fw.ReadDWord();
			}

			fw.ReadBytesArr(this_12);

			if (g_ArcVersion >= 1048)
			{
				this_13 = fw.ReadDWord();
				this_14 = fw.ReadDWord();
			}

			if (g_ArcVersion >= 1051)
				this_15 = fw.ReadDWord();
		}
	}
}

void CHARREPLACEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	this_6.Write(fw);
	fw.Write(this_7);
	m_pTypeIDData->dump(fw);

	if (g_ArcVersion >= 1277)
	{
		if (HIWORD(this_7))
		{
			fw.WriteBytesArr(this_9);

			if (g_ArcVersion >= 1048)
			{
				fw.Write(this_10);
				fw.Write(this_11);
			}

			fw.WriteBytesArr(this_12);

			if (g_ArcVersion >= 1048)
			{
				fw.Write(this_13);
				fw.Write(this_14);
			}

			if (g_ArcVersion >= 1051)
				fw.Write(this_15);
		}
	}
}
