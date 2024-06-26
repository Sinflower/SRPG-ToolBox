/*
 *  File: CLASSGROUPENTRYDATA.cpp
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

#include "CLASSGROUPENTRYDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void CLASSGROUPENTRYDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_4.data(), 40);
		this_4[10] = 0;
		this_4[11] = 0;
	}
	else
		fw.ReadBytes(this_4.data(), 48);

	// NOTE: Newer version contain a < 0x4F9 check and set all DWORDs == 3 to 4
	//       this probably has no meaning here but in case of errors check this
	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_16.data(), 40);
		this_16[10] = 3;
		this_16[11] = 3;
	}
	else
		fw.ReadBytes(this_16.data(), 48);

	allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
}

void CLASSGROUPENTRYDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_4.data(), 40);
	else
		fw.WriteBytes(this_4.data(), 48);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_16.data(), 40);
	else
		fw.WriteBytes(this_16.data(), 48);

	m_pTypeIDData->dump(fw);
}
