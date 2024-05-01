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

// Compatible up to v1.292

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
		this_10[10] = 0;
		this_10[11] = 0;
	}
	else
		fw.ReadBytes(this_10.data(), 48);

	// NOTE: Newer version contain a < 0x4F9 check and set all DWORDs == 3 to 4
	//       this probably has no meaning here but in case of errors check this
	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_22.data(), 40);
		this_22[10] = 0;
		this_22[11] = 0;
	}
	else
		fw.ReadBytes(this_22.data(), 48);

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
		NOT_IMPLEMENTED
		/*
		v13 = *a2;
		v14 = 0;
		v31 = 0;
		v26 = *(_DWORD*)(*a2 + v12);
		a2[1] = v12 + 4;
		v25 = *(_DWORD*)(v13 + v12 + 4);
		a2[1] = v12 + 8;
		Block = alloc_CMenuOperation((void*)0x9C6);
		CMenuInit(Block, a2);
		v27 = alloc_CMenuOperation((void*)0x9C6);
		CMenuInit(v27, a2);

		if (g_ArcVersion < 0x412)
			v29 = 0;
		else
		{
			v15 = a2[1];
			v29 = *(_DWORD*)(*a2 + v15);
			a2[1] = v15 + 4;
			v14 = alloc_CMenuOperation((void*)0x9C6);
			v31 = (int)v14;
			CMenuInit(v14, a2);
		}

		v16 = 0;
		v17 = *(_DWORD*)(*((_DWORD*)Block + 1) + 4);

		if (v17)
			goto LABEL_22;

		do
		{
			v17 = *(_DWORD*)(v17 + 4);
			++v16;
		} while (v17);

		if (v16 > 0)
		{
			sub_EB19F0((int)Block, this + 140, 1u);
			v18 = v26;
		}
		else
		{
LABEL_22:
			v19 = 0;
			v20 = *(_DWORD*)(*((_DWORD*)v27 + 1) + 4);

			if (!v20)
				goto LABEL_27;

			do
			{
				v20 = *(_DWORD*)(v20 + 4);
				++v19;
			} while (v20);

			if (v19 > 0)
			{
				sub_EB19F0((int)v27, this + 140, 4u);
				v18 = v25;
			}
			else
			{
LABEL_27:
				if (!v14 || sub_ED12A0(v14) <= 0)
					goto LABEL_30;
				sub_EB19F0(v31, this + 140, 5u);
				v18 = v29;
			}
		}
		v14 = (_DWORD*)v31;
		*(_DWORD*)(this + 140) = v18;
LABEL_30:
		sub_ED12F0(Block);

		if (v27)
			sub_ED12F0(v27);

		if (v14)
			sub_ED12F0(v14);*/
	}

	if (g_ArcVersion < 0x442)
	{
		if (this_37 == 1)
		{
			this_37 = 2;
			this_42 = this_3;
		}
	}
	else
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
		fw.WriteBytes(this_10.data(), 40);
	else
		fw.WriteBytes(this_10.data(), 48);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_22.data(), 40);
	else
		fw.WriteBytes(this_22.data(), 48);

	if (g_ArcVersion >= 0x41B)
		fw.Write(this_34);

	fw.Write(this_38);
	fw.Write(this_39);
	fw.Write(this_40);
	fw.Write(this_37);

	if (g_ArcVersion >= 0x41D)
	{
		fw.Write(this_35);
		pTypeIDData->dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_35))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}
	else
	{
		NOT_IMPLEMENTED
	}

	if (g_ArcVersion >= 0x442)
	{
		fw.Write(this_41);
		fw.Write(this_42);
	}
}
