/*
 *  File: ANIMEDATA.cpp
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

#include "ANIMEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ANIMEDATA::init(FileReader& fw)
{
	allocAndSetCMenuOp(&m_pFrameList, SRPGClasses::FRAMELIST, fw);

	this_9  = fw.ReadWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();

	this_20 = fw.ReadDWord();
	this_21 = fw.ReadDWord();

	sub_36EF00(fw);

	initMemData(this_13, fw);

	LEGENDDATA::init(fw);
}

void ANIMEDATA::dump(FileWriter& fw) const
{
	m_pFrameList->Dump(fw);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_20);
	fw.Write(this_21);

	if (g_ArcVersion >= 0x3F3)
		fw.Write(this_22);

	if (g_ArcVersion >= 0x409)
	{
		fw.Write(this_15);
		fw.Write(this_16);
		fw.Write(this_17);

		m_pTypeIDData->Dump(fw);
	}

	if (g_ArcVersion >= 0x40D)
		this_18.Write(fw);

	if (g_ArcVersion >= 0x411)
		fw.Write(this_19);

	this_13.Write(fw);

	LEGENDDATA::dump(fw);
}

void ANIMEDATA::sub_36EF00(FileReader& fw)
{
	if (g_ArcVersion >= 0x3F3)
		this_22 = fw.ReadDWord();

	if (g_ArcVersion >= 0x409)
	{
		this_15 = fw.ReadDWord();
		this_16 = fw.ReadDWord();
		this_17 = fw.ReadDWord();

		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x40D)
		initMemData(this_18, fw);

	if (g_ArcVersion >= 0x411)
		this_19 = fw.ReadDWord();
}
