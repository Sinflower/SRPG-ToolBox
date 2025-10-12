/*
 *  File: UNITINFOCHANGE.cpp
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

#include "UNITINFOCHANGE.h"
#include "../CMenuOperation.h"

void UNITINFOCHANGE::init(FileReader& fw)
{
	this_3  = fw.ReadDWord();
	this_4  = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();

	if (g_ArcVersion < 0x446)
	{
		NOT_IMPLEMENTED
		/*
		v6 = *(_DWORD *)Size;
		Sizea = *(_DWORD *)(*(_DWORD *)Size + v4);
		*(_DWORD *)(Size + 4) = v4 + 4;
		v29 = *(_DWORD *)(v6 + v4 + 4);
		*(_DWORD *)(Size + 4) = v4 + 8;
		v7 = alloc_CMenuOperation((void *)0x9C6);
		v8 = v7;
		*(_DWORD *)(this + 68) = v7;

		if ( Sizea != -1 )
		{
			v9 = (*(int (__thiscall **)(_DWORD *))*v7)(v7);
			*(_DWORD *)(v9 + 8) = 0;
			v10 = v8[1];
			v11 = v10 + 4;

			if ( *(_DWORD *)(v10 + 4) )
			{
				do
				{
					v10 = *(_DWORD *)v11;
					v12 = *(_DWORD *)(*(_DWORD *)v11 + 4) == 0;
					v11 = *(_DWORD *)v11 + 4;
				}
				while ( !v12 );
			}
			*(_DWORD *)(v10 + 4) = v9;
			*(_DWORD *)(v9 + 12) = Sizea;
		}
		v13 = *(_DWORD *)(this + 68);

		if ( v29 != -1 )
		{
			v14 = (**(int (__thiscall ***)(_DWORD))v13)(*(_DWORD *)(this + 68));
			*(_DWORD *)(v14 + 8) = 1;
			v15 = *(_DWORD *)(v13 + 4);
			v16 = v15 + 4;
			if ( *(_DWORD *)(v15 + 4) )
			{
				do
				{
					v15 = *(_DWORD *)v16;
					v12 = *(_DWORD *)(*(_DWORD *)v16 + 4) == 0;
					v16 = *(_DWORD *)v16 + 4;
				}
				while ( !v12 );
			}
			*(_DWORD *)(v15 + 4) = v14;
			*(_DWORD *)(v14 + 12) = v29;
		}*/
	}
	else
		allocAndSetCMenuOp(&pTypeIDData, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion < 0x436)
		pImageIDData1 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	else
		allocAndSetCMenuOp(&pImageIDData1, SRPGClasses::IMAGEIDDATA, fw);

	if (g_ArcVersion < 0x43F)
	{
		pImageIDData2 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		pImageIDData3 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		pImageIDData4 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	}
	else
	{
		allocAndSetCMenuOp(&pImageIDData2, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&pImageIDData3, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&pImageIDData4, SRPGClasses::IMAGEIDDATA, fw);
	}

	initMemData(name, fw);
	initMemData(description, fw);
}

void UNITINFOCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_12);
	fw.Write(this_13);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);

	if (g_ArcVersion < 0x446)
		NOT_IMPLEMENTED
	else
		pTypeIDData->Dump(fw);

	if (g_ArcVersion >= 0x436)
		pImageIDData1->Dump(fw);

	if (g_ArcVersion >= 0x43F)
	{
		pImageIDData2->Dump(fw);
		pImageIDData3->Dump(fw);
		pImageIDData4->Dump(fw);
	}

	name.Write(fw);
	description.Write(fw);
}

nlohmann::ordered_json UNITINFOCHANGE::toJson() const
{
	nlohmann::ordered_json j;
	j["name"]        = name.ToString();
	j["description"] = description.ToString();
	return j;
}

void UNITINFOCHANGE::applyPatch(const nlohmann::ordered_json& json)
{
	SET_STRING_IF_IN_JSON(json, "name", name);
	SET_STRING_IF_IN_JSON(json, "description", description);
}
