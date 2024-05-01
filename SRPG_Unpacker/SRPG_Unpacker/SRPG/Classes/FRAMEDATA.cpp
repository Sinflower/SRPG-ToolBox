// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "FRAMEDATA.h"
#include "SPRITEDATA.h"

void FRAMEDATA::init(FileReader& fw)
{
	if (g_ArcVersion < 0x47F)
	{
		sub_36F480(fw);
		return;
	}

	allocAndSetCMenuOp(&m_pSpriteData, SRPGClasses::SPRITEDATA, fw);

	this_4 = fw.ReadDWord();
	this_3 = fw.ReadDWord();
	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();

	initMemData(this_30, fw);

	if ((this_3 & 2) != 0)
	{
		this_12 = fw.ReadDWord();
		this_13 = fw.ReadDWord();
	}

	if ((this_3 & 1) != 0)
	{
		this_6 = fw.ReadDWord();
		this_7 = fw.ReadDWord();
		this_8 = fw.ReadDWord();
		this_9 = fw.ReadDWord();
		this_10 = fw.ReadDWord();
	}

	if ((this_3 & 4) != 0)
		this_16 = fw.ReadDWord();

	if ((this_3 & 8) != 0)
	{
		this_18 = fw.ReadDWord();
		this_19 = fw.ReadDWord();
		this_20 = fw.ReadDWord();
		this_21 = fw.ReadDWord();
		this_22 = fw.ReadDWord();
		this_23 = fw.ReadDWord();
	}

	if ((this_3 & 16) != 0)
	{
		this_24 = fw.ReadDWord();
		this_25 = fw.ReadDWord();
		this_26 = fw.ReadDWord();
		this_27 = fw.ReadDWord();
		this_28 = fw.ReadDWord();
	}
}

void FRAMEDATA::dump(FileWriter& fw) const
{
	if (g_ArcVersion < 0x47F)
	{
		m_pSpriteData->dump(fw);

		fw.Write(this_4);
		fw.Write(this_3);
		fw.Write(this_12);
		fw.Write(this_13);

		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);

		fw.Write(this_14);
		fw.Write(this_15);
		fw.Write(this_16);

		if (g_ArcVersion < 0x409)
		{
			fw.Write(res1);
			if (res1)
			{
				m_pSpriteDataOld->dump(fw);

				fw.Write(res2);
				if (res2)
				{
					m_pSpriteDataOld->pNext->dump(fw);
				}
			}
		}
		if (g_ArcVersion >= 0x461)
			this_30.Write(fw);
		return;
	}

	m_pSpriteData->dump(fw);

	fw.Write(this_4);
	fw.Write(this_3);
	fw.Write(this_14);
	fw.Write(this_15);

	this_30.Write(fw);

	if ((this_3 & 2) != 0)
	{
		fw.Write(this_12);
		fw.Write(this_13);
	}

	if ((this_3 & 1) != 0)
	{
		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);
	}

	if ((this_3 & 4) != 0)
		fw.Write(this_16);

	if ((this_3 & 8) != 0)
	{
		fw.Write(this_18);
		fw.Write(this_19);
		fw.Write(this_20);
		fw.Write(this_21);
		fw.Write(this_22);
		fw.Write(this_23);
	}

	if ((this_3 & 16) != 0)
	{
		fw.Write(this_24);
		fw.Write(this_25);
		fw.Write(this_26);
		fw.Write(this_27);
		fw.Write(this_28);
	}
}

void FRAMEDATA::sub_36F480(FileReader& fw)
{
	allocAndSetCMenuOp(&m_pSpriteData, SRPGClasses::SPRITEDATA, fw);

	this_4 = fw.ReadDWord();
	this_3 = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();
	this_16 = fw.ReadDWord();

	if (g_ArcVersion < 0x409)
	{
		res1 = fw.ReadDWord();
		if (res1)
		{
			m_pSpriteDataOld = new SPRITEDATA();
			m_pSpriteDataOld->init(fw);

			res2 = fw.ReadDWord();
			if (res2)
			{
				m_pSpriteDataOld->pNext = new SPRITEDATA();
				m_pSpriteDataOld->pNext->init(fw);
			}
		}
	}
	if (g_ArcVersion >= 0x461)
		initMemData(this_30, fw);
}
