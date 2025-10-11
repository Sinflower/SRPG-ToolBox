/*
 *  File: WEAPONDATA.cpp
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

#include "WEAPONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void WEAPONDATA::init(FileReader& fw)
{
	ITEMBASE::init(fw);

	this_50     = fw.ReadDWord();
	mt          = fw.ReadDWord();
	rangeStart  = fw.ReadDWord();
	rangeEnd    = fw.ReadDWord();
	hit         = fw.ReadDWord();
	crt         = fw.ReadDWord();
	attackCount = fw.ReadDWord();

	if (g_ArcVersion < 1048)
		weaponLevel = 0;
	else
		weaponLevel = fw.ReadDWord();

	this_58 = fw.ReadDWord();
	this_62 = fw.ReadDWord();
	this_63 = fw.ReadDWord();

	this_60 = fw.ReadDWord();
	this_61 = fw.ReadDWord();

	sub_102390(fw);

	this_66 = fw.ReadDWord();

	if (g_ArcVersion < 0x3FA)
		sub_FFF20(fw, this_50);
	else
	{
		DWORD v10 = 0;
		if (this_50)
		{
			if (this_50 == 1)
				sub_FFF20(fw, 2);
			else
			{
				if (this_50 == 2)
					v10 = 4;

				sub_FFF20(fw, v10);
			}
		}
		else
			sub_FFF20(fw, 1);
	}

	sub_102420(fw);
}

void WEAPONDATA::dump(FileWriter& fw) const
{
	ITEMBASE::dump(fw);

	fw.Write(this_50);
	fw.Write(mt);
	fw.Write(rangeStart);
	fw.Write(rangeEnd);
	fw.Write(hit);
	fw.Write(crt);
	fw.Write(attackCount);

	if (g_ArcVersion >= 1048)
		fw.Write(weaponLevel);

	fw.Write(this_58);
	fw.Write(this_62);
	fw.Write(this_63);

	fw.Write(this_60);
	fw.Write(this_61);

	if (g_ArcVersion < 0x41D)
	{
		NOT_IMPLEMENTED
	}
	else
	{
		fw.Write(this_64);
		m_pTypeIDData3->Dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_64))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}

	fw.Write(this_66);

	if (g_ArcVersion < 0x3FA)
		dump_sub_FFF20(fw, this_50);
	else
	{
		DWORD v10 = 0;
		if (this_50)
		{
			if (this_50 == 1)
				dump_sub_FFF20(fw, 2);
			else
			{
				if (this_50 == 2)
					v10 = 4;

				dump_sub_FFF20(fw, v10);
			}
		}
		else
			dump_sub_FFF20(fw, 1);
	}

	//////
	if (g_ArcVersion >= 0x3EB)
		fw.Write(this_70);

	if (g_ArcVersion >= 0x400)
	{
		fw.Write(this_71);
		fw.Write(this_72);
		fw.Write(this_73);
	}

	if (g_ArcVersion >= 0x406)
	{
		if (g_ArcVersion < 0x43F)
		{
			fw.Write(res);
			if (res)
			{
				NOT_IMPLEMENTED
			}
		}
		else
		{
			m_pImageIDData1->Dump(fw);
			m_pImageIDData2->Dump(fw);
		}
	}
	//////
}

void WEAPONDATA::sub_102420(FileReader& fw)
{
	if (g_ArcVersion >= 0x3EB)
		this_70 = fw.ReadDWord();

	if (g_ArcVersion < 0x400)
	{
		this_71 = -1;
		this_73 = 10;
		this_72 = 100;
	}
	else
	{
		this_71 = fw.ReadDWord();
		this_72 = fw.ReadDWord();
		this_73 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x418)
	{
		// if (this_73 == 9 || this_73 == 10)
		//	this_73 += 2;
	}

	if (g_ArcVersion < 0x406)
	{
		m_pImageIDData1 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		m_pImageIDData2 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	}
	else
		sub_100680(fw);
}

void WEAPONDATA::sub_100680(FileReader& fw)
{
	if (g_ArcVersion < 0x43F)
	{
		res = fw.ReadDWord();
		if (res)
		{
			NOT_IMPLEMENTED
			/*
			DWORD v25[10];
			DWORD v26[14];
			fw.ReadBytes(v25, 0x28);
			fw.ReadBytes(v26, 0x38);

			for (uint32_t i = 0; i < 5; ++i )
			{
				DWORD v11 = v25[2 * i + 1];
				if ( v25[2 * i] || v11 != 327680 )
				{
					v12 = *this;
					v13 = (_DWORD *)(**(int (__thiscall ***)(_DWORD))*this)(*this);
					v13[2] = i;
					v14 = *(_DWORD *)(v12 + 4);
					v15 = v14 + 4;
					if ( *(_DWORD *)(v14 + 4) )
					{
						do
						{
							v14 = *(_DWORD *)v15;
							v16 = *(_DWORD *)(*(_DWORD *)v15 + 4) == 0;
							v15 = *(_DWORD *)v15 + 4;
						}
						while ( !v16 );
					}
					v17 = v25[2 * i];
					*(_DWORD *)(v14 + 4) = v13;
					v13[4] = v17;
					v13[5] = v11;
				}
			}

			for (uint32_t j = 0; j < 7; ++j )
			{
				DWORD v19 = v26[2 * j + 1];
				if ( v26[2 * j] || v19 != 327680 )
				{
					v20 = this_75;
					result = (int *)(**(int (__thiscall ***)(int))this_75)(this_75);
					result[2] = j;
					v21 = *(_DWORD *)(v20 + 4);
					v22 = v21 + 4;
					if ( *(_DWORD *)(v21 + 4) )
					{
						do
						{
							v21 = *(_DWORD *)v22;
							v16 = *(_DWORD *)(*(_DWORD *)v22 + 4) == 0;
							v22 = *(_DWORD *)v22 + 4;
						}
						while ( !v16 );
					}
					v23 = v26[2 * j];
					*(_DWORD *)(v21 + 4) = result;
					result[4] = v23;
					result[5] = v19;
				}
			}
			*/
		}
		else
		{
			m_pImageIDData1 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
			m_pImageIDData2 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		}
	}
	else
	{
		allocAndSetCMenuOp(&m_pImageIDData1, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&m_pImageIDData2, SRPGClasses::IMAGEIDDATA, fw);
	}
}

void WEAPONDATA::sub_FFF20(FileReader& fw, int a3)
{
	if (g_ArcVersion < 0x43F)
	{
		NOT_IMPLEMENTED
		/*
		lpMem = 0;
		v12 = 0;
		v13 = 0;
		sub_360240(&lpMem, a3);
		sub_3602E0(&lpMem, a2, (void*)a3);
		sub_360010(&lpMem, this);
		if (lpMem)
		{
		v8 = lpMem;
		v5 = GetProcessHeap();
		HeapFree(v5, 0, v8);
		}
		if (v12)
		{
		v9 = v12;
		v6 = GetProcessHeap();
		HeapFree(v6, 0, v9);
		}
		result = (int*)v13;
		if (v13)
		{
		v10 = v13;
		v7 = GetProcessHeap();
		result = (int*)HeapFree(v7, 0, v10);
		}
		*/
	}
	else
	{
		allocAndSetCMenuOp(&m_pMotionIDData1, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData2, SRPGClasses::MOTIONIDDATA, fw);
		allocAndSetCMenuOp(&m_pMotionIDData3, SRPGClasses::MOTIONIDDATA, fw);
	}
}

void WEAPONDATA::dump_sub_FFF20(FileWriter& fw, int a3) const
{
	if (g_ArcVersion < 0x43F)
	{
		NOT_IMPLEMENTED
	}
	else
	{
		m_pMotionIDData1->Dump(fw);
		m_pMotionIDData2->Dump(fw);
		m_pMotionIDData3->Dump(fw);
	}
}

void WEAPONDATA::sub_102390(FileReader& fw)
{
	if (g_ArcVersion < 0x41D)
	{
		NOT_IMPLEMENTED
		/*
		v3 = alloc_CMenuOperation(SRPGClasses::TYPEIDDATA);
		CMenuInit(v3, a2);
		sub_1019F0((int)v3, (int)(this + 64), 6u);
		if ( v3 )
			sub_1212F0(v3);
		*/
	}
	else
	{
		this_64 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData3, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_64))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
}

void WEAPONDATA::print(std::ostream& os) const
{
	os << "WEAPONDATA" << std::endl;
	ITEMBASE::print(os);
	os << "this_50: " << this_50 << std::endl;
	os << "Mt: " << mt << std::endl;
	os << "Range Start: " << rangeStart << std::endl;
	os << "Range End: " << rangeEnd << std::endl;
	os << "Hit: " << hit << std::endl;
	os << "Crt: " << crt << std::endl;
	os << "Attack Count: " << attackCount << std::endl;
	os << "Weapon Level: " << weaponLevel << std::endl;
	os << "this_58: " << this_58 << std::endl;
	os << "this_60: " << this_60 << std::endl;
	os << "this_61: " << this_61 << std::endl;
	os << "this_62: " << this_62 << std::endl;
	os << "this_63: " << this_63 << std::endl;
	os << "this_64: " << this_64 << std::endl;
	os << "this_66: " << this_66 << std::endl;
	os << "this_70: " << this_70 << std::endl;
	os << "this_71: " << this_71 << std::endl;
	os << "this_72: " << this_72 << std::endl;
	os << "this_73: " << this_73 << std::endl;
}