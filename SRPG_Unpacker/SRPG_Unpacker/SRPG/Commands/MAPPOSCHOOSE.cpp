/*
 *  File: MAPPOSCHOOSE.cpp
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

#include "MAPPOSCHOOSE.h"
#include "../CMenuOperation.h"

void MAPPOSCHOOSE::init(FileReader& fw)
{
	if (g_ArcVersion < 1256)
		this_3.resize(6);
	else
		this_3.resize(7);

	fw.ReadBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));

	fw.ReadBytes(this_10.data(), static_cast<DWORD>(this_10.size() * sizeof(DWORD)));

	this_19 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_20, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_19))
	{
		fw.ReadBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.ReadBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));
		this_26 = fw.ReadDWord();
	}

	this_21 = fw.ReadDWord();
	this_22 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_23, SRPGClasses::TYPEIDDATA, fw);
}

void MAPPOSCHOOSE::dump(FileWriter& fw) const
{
	fw.WriteBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));

	fw.WriteBytes(this_10.data(), static_cast<DWORD>(this_10.size() * sizeof(DWORD)));

	fw.Write(this_19);

	if (g_ArcVersion >= 1277 && HIWORD(this_19))
	{
		fw.WriteBytes(this_24.data(), static_cast<DWORD>(this_24.size() * sizeof(DWORD)));
		fw.WriteBytes(this_25.data(), static_cast<DWORD>(this_25.size() * sizeof(DWORD)));
		fw.Write(this_26);
	}

	this_20->Dump(fw);

	fw.Write(this_21);
	fw.Write(this_22);

	this_23->Dump(fw);
}
