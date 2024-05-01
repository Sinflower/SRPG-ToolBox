// Compatible up to v1.292

#include "SKILLDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SKILLDATA::init(FileReader& fw)
{
	this_9 = fw.ReadDWord();

	this_8  = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();

	sub_1046E0(fw);

	initMemData(this_10, fw);
	initMemData(this_21, fw);

	LEGENDDATA::init(fw);

	if (g_ArcVersion < 0x409)
	{
		this_14 = 0;
		this_15 = 0x20000;
		this_16 = 0;
		this_17 = 0x20000;
	}
	else
	{
		this_14 = fw.ReadDWord();
		this_15 = fw.ReadDWord();
		this_16 = fw.ReadDWord();
		this_17 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x418)
	{
		// if (this_11 == 9 || this_11 == 10)
		//	this_11 += 2;
	}

	if (g_ArcVersion >= 0x41D)
	{
		this_25 = fw.ReadDWord();
		this_26 = fw.ReadDWord();

		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

		this_27 = fw.ReadDWord();

		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_27))
		{
			fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			this_132 = fw.ReadDWord();
		}
	}
}

void SKILLDATA::dump(FileWriter& fw) const
{
	fw.Write(this_9);
	fw.Write(this_8);
	fw.Write(this_11);
	fw.Write(this_12);

	/////

	if (g_ArcVersion >= 0x3F8)
	{
		fw.Write(this_18);
		fw.Write(this_19);

		if (this_9 == 33)
		{
			if (g_ArcVersion < 0x41D)
			{
				fw.Write(this_25);
				fw.Write(this_26);

				fw.Write(this_23[0]);
				fw.Write(this_23[1]);
				fw.Write(this_23[2]);
				fw.Write(this_23[3]);
				fw.Write(this_23[4]);
				fw.Write(this_23[5]);

				if (g_ArcVersion >= 0x4EC)
					fw.Write(this_23[6]);

				if (g_ArcVersion >= 0x415)
				{
					fw.Write(this_27);
					m_pTypeIDData2->dump(fw);
				}
			}
			else
			{
				fw.Write(this_23[0]);
				fw.Write(this_23[1]);
				fw.Write(this_23[2]);
				fw.Write(this_23[3]);
				fw.Write(this_23[4]);
				fw.Write(this_23[5]);

				if (g_ArcVersion >= 0x4EC)
					fw.Write(this_23[6]);
			}
		}
		else if (this_9 == 34)
		{
			if (g_ArcVersion < 0x418)
			{
				fw.Write(this_22[0]);
				fw.Write(this_22[1]);
				fw.Write(this_22[2]);
				fw.Write(this_22[3]);
				fw.Write(this_22[4]);
				fw.Write(this_22[5]);
				fw.Write(this_22[6]);
				fw.Write(this_22[7]);
				fw.Write(this_22[8]);
			}
			else
			{
				fw.Write(res);

				if (!res)
				{
					fw.Write(this_22[0]);
					fw.Write(this_22[1]);
					fw.Write(this_22[2]);
					fw.Write(this_22[3]);
					fw.Write(this_22[4]);
					fw.Write(this_22[5]);
					fw.Write(this_22[6]);
					fw.Write(this_22[7]);
					fw.Write(this_22[8]);
					fw.Write(this_22[9]);
					fw.Write(this_22[10]);
				}
			}
		}
		else if (this_9 == 44)
		{
			if (g_ArcVersion < 0x41D)
				m_pTypeIDData1->dump(fw);
		}
	}
	if (g_ArcVersion >= 0x446)
		fw.Write(this_20);

	if (g_ArcVersion >= 0x4A4)
	{
		fw.Write(this_29);
		this_30.Write(fw);
	}

	/////

	this_10.Write(fw);
	this_21.Write(fw);

	LEGENDDATA::dump(fw);

	if (g_ArcVersion >= 0x409)
	{
		fw.Write(this_14);
		fw.Write(this_15);
		fw.Write(this_16);
		fw.Write(this_17);
	}

	if (g_ArcVersion >= 0x41D)
	{
		fw.Write(this_25);
		fw.Write(this_26);

		m_pTypeIDData1->dump(fw);

		fw.Write(this_27);

		m_pTypeIDData2->dump(fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_27))
		{
			fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
			fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
			fw.Write(this_132);
		}
	}
}

void SKILLDATA::sub_1046E0(FileReader& fw)
{
	if (g_ArcVersion < 0x3F8)
	{
		this_18 = 0;
		this_19 = 0;

		if (this_9 == 22)
			this_18 = 1;
		else if (this_9 == 30)
			this_18 = 5;
		else if (this_9 == 31)
			this_18 = 200;
		else if (this_9 == 32)
			this_18 = 50;
	}
	else
	{
		this_18 = fw.ReadDWord();
		this_19 = fw.ReadDWord();

		if (this_9 == 33)
		{
			if (g_ArcVersion < 0x41D)
			{
				this_25 = fw.ReadDWord();
				this_26 = fw.ReadDWord();

				sub_10E620(fw);

				if (g_ArcVersion >= 0x415)
				{
					this_27 = fw.ReadDWord();
					allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
				}
			}
			else
				sub_10E620(fw);
		}
		else if (this_9 == 34)
			sub_10E310(fw);
		else if (this_9 == 44)
		{
			if (g_ArcVersion < 0x41D)
				allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);
		}
		else if (this_9 == 10)
		{
			if (g_ArcVersion < 0x436)
				this_19 = this_19 ? 100 : 50;
		}
		else if (this_9 == 32 && g_ArcVersion < 0x436)
			this_19 = 50;
	}
	if (g_ArcVersion < 0x446)
		this_20 = 0;
	else
		this_20 = fw.ReadDWord();

	if (g_ArcVersion >= 0x4A4)
	{
		this_29 = fw.ReadDWord();
		initMemData(this_30, fw);
	}
}

void SKILLDATA::sub_10E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_22[0]  = fw.ReadDWord();
		this_22[1]  = fw.ReadDWord();
		this_22[2]  = fw.ReadDWord();
		this_22[3]  = fw.ReadDWord();
		this_22[4]  = fw.ReadDWord();
		this_22[5]  = fw.ReadDWord();
		this_22[6]  = fw.ReadDWord();
		this_22[7]  = fw.ReadDWord();
		this_22[8]  = fw.ReadDWord();
		this_22[9]  = 0;
		this_22[10] = 0;
	}
	else
	{
		res = fw.ReadDWord();

		if (res)
		{
			this_22[0]  = 0;
			this_22[1]  = 0;
			this_22[2]  = 0;
			this_22[3]  = 0;
			this_22[4]  = 0;
			this_22[5]  = 0;
			this_22[6]  = 0;
			this_22[7]  = 0;
			this_22[8]  = 0;
			this_22[9]  = 0;
			this_22[10] = 0;
		}
		else
		{
			this_22[0]  = fw.ReadDWord();
			this_22[1]  = fw.ReadDWord();
			this_22[2]  = fw.ReadDWord();
			this_22[3]  = fw.ReadDWord();
			this_22[4]  = fw.ReadDWord();
			this_22[5]  = fw.ReadDWord();
			this_22[6]  = fw.ReadDWord();
			this_22[7]  = fw.ReadDWord();
			this_22[8]  = fw.ReadDWord();
			this_22[9]  = fw.ReadDWord();
			this_22[10] = fw.ReadDWord();
		}
	}
}

void SKILLDATA::sub_10E620(FileReader& fw)
{
	this_23[0] = fw.ReadDWord();
	this_23[1] = fw.ReadDWord();
	this_23[2] = fw.ReadDWord();
	this_23[3] = fw.ReadDWord();
	this_23[4] = fw.ReadDWord();
	this_23[5] = fw.ReadDWord();

	if (g_ArcVersion >= 0x4EC)
		this_23[6] = fw.ReadDWord();
}

void SKILLDATA::print(std::ostream& os) const
{
	os << "SkillData" << std::endl;
	os << "this_8 : " << this_8 << std::endl;
	os << "this_9 : " << this_9 << std::endl;
	os << "this_10: " << this_10 << std::endl;
	os << "this_11: " << this_11 << std::endl;
	os << "this_12: " << this_12 << std::endl;
	os << "this_14: " << this_14 << std::endl;
	os << "this_15: " << this_15 << std::endl;
	os << "this_16: " << this_16 << std::endl;
	os << "this_17: " << this_17 << std::endl;
	os << "this_20: " << this_20 << std::endl;
	os << "this_21: " << this_21 << std::endl;

	for (uint32_t i = 0; i < 11; i++)
		os << "this_22[" << i << "]: " << this_22[i] << std::endl;

	for (uint32_t i = 0; i < 7; i++)
		os << "this_23[" << i << "]: " << this_23[i] << std::endl;

	os << "m_pTypeIDData1: " << *m_pTypeIDData1 << std::endl;

	os << "this_25: " << this_25 << std::endl;
	os << "this_26: " << this_26 << std::endl;
	os << "this_27: " << this_27 << std::endl;

	os << "m_pTypeIDData2: " << *m_pTypeIDData2 << std::endl;

	os << "this_29: " << this_29 << std::endl;
	os << "this_30: " << this_30 << std::endl;
}