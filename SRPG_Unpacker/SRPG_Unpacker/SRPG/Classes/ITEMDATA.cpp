/*
 *  File: ITEMDATA.cpp
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

#include "ITEMDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ITEMDATA::init(FileReader& fw)
{
	ITEMBASE::init(fw);

	itemType = fw.ReadDWord();

	switch (itemType)
	{
		case 1:
			this_62[0] = fw.ReadDWord();
			this_62[1] = fw.ReadDWord();
			this_62[2] = fw.ReadDWord();
			break;
		case 2:
			this_63[0] = fw.ReadDWord();
			this_63[1] = fw.ReadDWord();
			this_63[2] = fw.ReadDWord();
			break;
		case 3:
			this_64[0] = fw.ReadDWord();
			this_64[1] = fw.ReadDWord();

			if (g_ArcVersion < 0x488)
				this_64[2] = 0;
			else
				this_64[2] = fw.ReadDWord();
			break;
		case 5:
			this_65.this_0 = fw.ReadDWord();
			this_65.this_1 = fw.ReadDWord();

			allocAndSetCMenuOp(&(this_65.pTypeIDData), SRPGClasses::TYPEIDDATA, fw);
			break;
		case 4:
			sub_10E310(fw);
			if (g_ArcVersion < 0x3EB)
				this_66[11] = 0;
			else
				this_66[11] = fw.ReadDWord();
			break;
		case 6:
			this_67[0] = fw.ReadDWord();
			this_67[1] = fw.ReadDWord();
			break;
		case 7:
			this_68[0] = fw.ReadDWord();
			this_68[1] = fw.ReadDWord();
			this_68[2] = fw.ReadDWord();
			break;
		case 8:
			this_69 = fw.ReadDWord();
			break;
		case 9:
			this_70[0] = fw.ReadDWord();
			this_70[1] = fw.ReadDWord();
			break;
		case 11:
			this_71 = fw.ReadDWord();
			break;
		case 12:
			this_72[0] = fw.ReadDWord();
			this_72[1] = fw.ReadDWord();
			break;
		case 13:
			this_73 = fw.ReadDWord();
			break;
		case 14:
			this_74[0] = fw.ReadDWord();
			this_74[1] = fw.ReadDWord();
			this_74[2] = fw.ReadDWord();
			this_74[3] = fw.ReadDWord();

			if (g_ArcVersion < 0x418)
			{
				// if (this_74[2] == 9 || this_74[2] == 10)
				//	this_74[2] += 2;
			}
			break;
		case 15:
			this_75.this_0 = fw.ReadDWord();
			this_75.this_1 = fw.ReadDWord();
			this_75.this_2 = fw.ReadDWord();
			allocAndSetCMenuOp(&(this_75.pTypeIDData), SRPGClasses::TYPEIDDATA, fw);
			break;
		case 16:
			this_76.init(fw);
			break;
		case 17:
			this_77[0] = fw.ReadDWord();
			this_77[1] = fw.ReadDWord();
			this_77[2] = fw.ReadDWord();
			break;
		case 18:
			allocAndSetCMenuOp(&(this_78.pTypeIDData), SRPGClasses::TYPEIDDATA, fw);
			break;
		case 100:
			initMemData(this_79, fw);
			break;
		default:
			break;
	}

	expGain = fw.ReadDWord();

	if (g_ArcVersion >= 0x411)
		this_52 = fw.ReadDWord();

	this_54 = fw.ReadDWord();
	this_55 = fw.ReadDWord();
	this_56 = fw.ReadDWord();
	this_57 = fw.ReadDWord();

	if (g_ArcVersion < 0x400)
	{
		this_58        = 0;
		m_pTypeIDData1 = new CMenuOperation(SRPGClasses::TYPEIDDATA);
	}
	else
	{
		this_58 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);
	}
	if (g_ArcVersion >= 0x41D)
	{
		this_60 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_60))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
}

void ITEMDATA::dump(FileWriter& fw) const
{
	ITEMBASE::dump(fw);

	fw.Write(itemType);

	switch (itemType)
	{
		case 1:
			fw.Write(this_62[0]);
			fw.Write(this_62[1]);
			fw.Write(this_62[2]);
			break;
		case 2:
			fw.Write(this_63[0]);
			fw.Write(this_63[1]);
			fw.Write(this_63[2]);
			break;
		case 3:
			fw.Write(this_64[0]);
			fw.Write(this_64[1]);

			if (g_ArcVersion >= 0x488)
				fw.Write(this_64[2]);
			break;
		case 5:
			fw.Write(this_65.this_0);
			fw.Write(this_65.this_1);

			this_65.pTypeIDData->Dump(fw);
			break;
		case 4:
			if (g_ArcVersion < 0x418)
			{
				fw.Write(this_66[0]);
				fw.Write(this_66[1]);
				fw.Write(this_66[2]);
				fw.Write(this_66[3]);
				fw.Write(this_66[4]);
				fw.Write(this_66[5]);
				fw.Write(this_66[6]);
				fw.Write(this_66[7]);
				fw.Write(this_66[8]);
			}
			else
			{
				fw.Write(res);
				if (!res)
				{
					fw.Write(this_66[0]);
					fw.Write(this_66[1]);
					fw.Write(this_66[2]);
					fw.Write(this_66[3]);
					fw.Write(this_66[4]);
					fw.Write(this_66[5]);
					fw.Write(this_66[6]);
					fw.Write(this_66[7]);
					fw.Write(this_66[8]);
					fw.Write(this_66[9]);
					fw.Write(this_66[10]);
				}
			}

			if (g_ArcVersion >= 0x3EB)
				fw.Write(this_66[11]);
			break;
		case 6:
			fw.Write(this_67[0]);
			fw.Write(this_67[1]);
			break;
		case 7:
			fw.Write(this_68[0]);
			fw.Write(this_68[1]);
			fw.Write(this_68[2]);
			break;
		case 8:
			fw.Write(this_69);
			break;
		case 9:
			fw.Write(this_70[0]);
			fw.Write(this_70[1]);
			break;
		case 11:
			fw.Write(this_71);
			break;
		case 12:
			fw.Write(this_72[0]);
			fw.Write(this_72[1]);
			break;
		case 13:
			fw.Write(this_73);
			break;
		case 14:
			fw.Write(this_74[0]);
			fw.Write(this_74[1]);
			fw.Write(this_74[2]);
			fw.Write(this_74[3]);

			break;
		case 15:
			fw.Write(this_75.this_0);
			fw.Write(this_75.this_1);
			fw.Write(this_75.this_2);
			this_75.pTypeIDData->Dump(fw);
			break;
		case 16:
			this_76.dump(fw);
			break;
		case 17:
			fw.Write(this_77[0]);
			fw.Write(this_77[1]);
			fw.Write(this_77[2]);
			break;
		case 18:
			this_78.pTypeIDData->Dump(fw);
			break;
		case 100:
			this_79.Write(fw);
			break;
		default:
			break;
	}

	fw.Write(expGain);

	if (g_ArcVersion >= 0x411)
		fw.Write(this_52);

	fw.Write(this_54);
	fw.Write(this_55);
	fw.Write(this_56);
	fw.Write(this_57);

	if (g_ArcVersion >= 0x400)
	{
		fw.Write(this_58);
		m_pTypeIDData1->Dump(fw);
	}
	if (g_ArcVersion >= 0x41D)
	{
		fw.Write(this_60);
		m_pTypeIDData2->Dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_60))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}
}

void ITEMDATA::sub_10E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_66[0]  = fw.ReadDWord();
		this_66[1]  = fw.ReadDWord();
		this_66[2]  = fw.ReadDWord();
		this_66[3]  = fw.ReadDWord();
		this_66[4]  = fw.ReadDWord();
		this_66[5]  = fw.ReadDWord();
		this_66[6]  = fw.ReadDWord();
		this_66[7]  = fw.ReadDWord();
		this_66[8]  = fw.ReadDWord();
		this_66[9]  = 0;
		this_66[10] = 0;
	}
	else
	{
		res = fw.ReadDWord();
		if (res)
		{
			this_66[0]  = 0;
			this_66[1]  = 0;
			this_66[2]  = 0;
			this_66[3]  = 0;
			this_66[4]  = 0;
			this_66[5]  = 0;
			this_66[6]  = 0;
			this_66[7]  = 0;
			this_66[8]  = 0;
			this_66[9]  = 0;
			this_66[10] = 0;
		}
		else
		{
			this_66[0]  = fw.ReadDWord();
			this_66[1]  = fw.ReadDWord();
			this_66[2]  = fw.ReadDWord();
			this_66[3]  = fw.ReadDWord();
			this_66[4]  = fw.ReadDWord();
			this_66[5]  = fw.ReadDWord();
			this_66[6]  = fw.ReadDWord();
			this_66[7]  = fw.ReadDWord();
			this_66[8]  = fw.ReadDWord();
			this_66[9]  = fw.ReadDWord();
			this_66[10] = fw.ReadDWord();
		}
	}
}

void ITEMDATA::print(std::ostream& os) const
{
	os << "ITEMDATA" << std::endl;
	ITEMBASE::print(os);
	os << "Item Type: " << itemType << std::endl;
	os << "Exp Gain: " << expGain << std::endl;
	os << "this_52: " << this_52 << std::endl;
	os << "this_54: " << this_54 << std::endl;
	os << "this_55: " << this_55 << std::endl;
	os << "this_56: " << this_56 << std::endl;
	os << "this_57: " << this_57 << std::endl;
	os << "this_58: " << this_58 << std::endl;
	os << "this_60: " << this_60 << std::endl;

	for (uint32_t i = 0; i < 3; i++)
		os << "this_62[" << i << "]: " << this_62[i] << std::endl;

	for (uint32_t i = 0; i < 3; i++)
		os << "this_63[" << i << "]: " << this_63[i] << std::endl;

	for (uint32_t i = 0; i < 3; i++)
		os << "this_64[" << i << "]: " << this_64[i] << std::endl;

	os << "this_65.this_0: " << this_65.this_0 << std::endl;
	os << "this_65.this_1: " << this_65.this_1 << std::endl;
	os << "this_65.pTypeIDData: " << this_65.pTypeIDData << std::endl;

	for (uint32_t i = 0; i < 12; i++)
		os << "this_66[" << i << "]: " << this_66[i] << std::endl;

	for (uint32_t i = 0; i < 2; i++)
		os << "this_67[" << i << "]: " << this_67[i] << std::endl;

	for (uint32_t i = 0; i < 3; i++)
		os << "this_68[" << i << "]: " << this_68[i] << std::endl;

	os << "this_69: " << this_69 << std::endl;

	for (uint32_t i = 0; i < 2; i++)
		os << "this_70[" << i << "]: " << this_70[i] << std::endl;

	os << "this_71: " << this_71 << std::endl;

	for (uint32_t i = 0; i < 2; i++)
		os << "this_72[" << i << "]: " << this_72[i] << std::endl;

	os << "this_73: " << this_73 << std::endl;

	for (uint32_t i = 0; i < 4; i++)
		os << "this_74[" << i << "]: " << this_74[i] << std::endl;

	os << "this_75.this_0: " << this_75.this_0 << std::endl;
	os << "this_75.this_1: " << this_75.this_1 << std::endl;
	os << "this_75.this_2: " << this_75.this_2 << std::endl;
	os << "this_75.pTypeIDData: " << this_75.pTypeIDData << std::endl;

	os << "this_76: " << this_76 << std::endl;

	for (uint32_t i = 0; i < 3; i++)
		os << "this_77[" << i << "]: " << this_77[i] << std::endl;

	os << "this_78.pTypeIDData: " << this_78.pTypeIDData << std::endl;
	os << "this_78.this_1: " << this_78.this_1 << std::endl;

	os << "this_79: " << this_79 << std::endl;

	/*
	ELEM_78 this_78;
	MemData this_79;
	*/
}