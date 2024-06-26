/*
 *  File: EVENTPAGE_DATA.cpp
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

#include "EVENTPAGE_DATA.h"
#include "../CMenuOperation.h"
#include "../Commands/SWITCHACTION.h"
#include "EDITDATA.h"

void EVENTPAGE_DATA::init(FileReader& fw)
{
	if (g_ArcVersion >= 0x432)
	{
		sub_D4F50(fw);
		return;
	}

	if (g_ArcVersion < 0x41B)
	{
		this_0 = fw.ReadDWord();
		this_1 = fw.ReadDWord();
	}
	else
	{
		this_0 = fw.ReadDWord();
		if (this_0 > 0)
			this_1 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x41B)
	{
		this_17 = fw.ReadDWord();
		this_18 = fw.ReadDWord();
	}
	else
	{
		this_17 = fw.ReadDWord();
		if (this_17 > 0)
			this_18 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x41B)
	{
		enTurn                  = fw.ReadDWord();
		turn                    = fw.ReadDWord();
		turnCondition           = fw.ReadDWord();
		turnArmy                = fw.ReadDWord();
		turnTreatAsRelativeTurn = fw.ReadDWord();
	}
	else
	{
		enTurn = fw.ReadDWord();
		if (enTurn > 0)
		{
			turn                    = fw.ReadDWord();
			turnCondition           = fw.ReadDWord();
			turnArmy                = fw.ReadDWord();
			turnTreatAsRelativeTurn = fw.ReadDWord();
		}
	}

	if (g_ArcVersion < 0x41B)
	{
		enGold        = fw.ReadDWord();
		gold          = fw.ReadDWord();
		goldCondition = fw.ReadDWord();
	}
	else
	{
		enGold = fw.ReadDWord();
		if (enGold > 0)
		{
			gold          = fw.ReadDWord();
			goldCondition = fw.ReadDWord();
		}
	}

	if (g_ArcVersion < 0x41B)
	{
		enUnitTotal            = fw.ReadDWord();
		unitTotal              = fw.ReadDWord();
		unitTotalCondition     = fw.ReadDWord();
		unitTotalArmy          = fw.ReadDWord();
		unitTotalLifeCondition = fw.ReadDWord();
	}
	else
	{
		enUnitTotal = fw.ReadDWord();
		if (enUnitTotal > 0)
		{
			unitTotal              = fw.ReadDWord();
			unitTotalCondition     = fw.ReadDWord();
			unitTotalArmy          = fw.ReadDWord();
			unitTotalLifeCondition = fw.ReadDWord();
		}
	}

	if (g_ArcVersion < 0x41B)
	{
		enBonus        = fw.ReadDWord();
		bonus          = fw.ReadDWord();
		bonusCondition = fw.ReadDWord();
	}
	else
	{
		enBonus = fw.ReadDWord();
		if (enBonus > 0)
		{
			bonus          = fw.ReadDWord();
			bonusCondition = fw.ReadDWord();
		}
	}

	if (g_ArcVersion < 0x41B)
	{
		enEnvironment        = fw.ReadDWord();
		environmentCondition = fw.ReadDWord();
	}
	else
	{
		enEnvironment = fw.ReadDWord();
		if (enEnvironment > 0)
			environmentCondition = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x41B)
		this_90 = fw.ReadDWord();
	else
		this_90 = fw.ReadDWord();

	if (g_ArcVersion < 0x41B)
		this_92 = fw.ReadDWord();
	else
		this_92 = fw.ReadDWord();

	if (g_ArcVersion < 0x3F5)
	{
		this_34 = fw.ReadDWord();
		this_35 = fw.ReadDWord();
		this_36 = fw.ReadDWord();
		this_37 = fw.ReadDWord();
		this_38 = 1;
	}
	else
	{
		if (g_ArcVersion < 0x41B)
		{
			this_34 = fw.ReadDWord();
			this_35 = fw.ReadDWord();
			this_36 = fw.ReadDWord();
			this_37 = fw.ReadDWord();
			this_38 = fw.ReadDWord();
		}
		else
		{
			this_34 = fw.ReadDWord();

			if (this_34 > 0)
			{
				this_35 = fw.ReadDWord();
				this_36 = fw.ReadDWord();
				this_37 = fw.ReadDWord();
				this_38 = fw.ReadDWord();
			}
		}

		this_37 = ((this_37 == 0) ? 1 : 7);
	}

	this_41 = 0;
	this_42 = new CMenuOperation(SRPGClasses::TYPEIDDATA);
	sub_D5E70(fw);

	if (!this_2)
		this_2 = new SWITCHACTION;

	this_2->init(fw);

	allocAndSetCMenuOp(&this_39, SRPGClasses::MAPPOSDATA, fw);
	allocAndSetCMenuOp(&this_40, SRPGClasses::MAPPOSDATA, fw);
	allocAndSetCMenuOp(&this_32, SRPGClasses::ITEMCONDITIONDATA, fw);
	allocAndSetCMenuOp(&this_33, SRPGClasses::UNITCONDITIONDATA, fw);
	allocAndSetCMenuOp(&this_91, SRPGClasses::TYPEIDDATA, fw);

	initMemData(this_93, fw);
}

void EVENTPAGE_DATA::dump(FileWriter& fw) const
{
	if (g_ArcVersion >= 0x432)
	{
		fw.Write(checkData);

		if ((checkData & 1) != 0)
		{
			fw.Write(this_0);
			fw.Write(this_1);

			if (g_ArcVersion >= 0x502)
				this_2_new->dump(fw);
		}

		if ((checkData & 2) != 0)
		{
			if (this_2)
				this_2->dump(fw);
		}

		if ((checkData & 4) != 0)
		{
			// NOTE: This was changed in new versions, might cause problems
			if (g_ArcVersion < 0x4CE)
			{
				fw.Write(this_3);
				fw.Write(this_4);
				fw.Write(this_5);
				fw.Write(this_6);
				fw.Write(this_7);
				fw.Write(this_8);
				fw.Write(this_9);
				fw.Write(this_10);
				fw.Write(this_11);
				fw.Write(this_12);
				fw.Write(this_13);
				fw.Write(this_14);
				fw.Write(this_15);
				fw.Write(this_16);
			}
			else
				this_3_new->dump(fw);
		}

		if ((checkData & 8) != 0)
		{
			fw.Write(this_17);
			fw.Write(this_18);
		}

		if ((checkData & 0x10) != 0)
		{
			fw.Write(enTurn);
			fw.Write(turn);
			fw.Write(turnCondition);
			fw.Write(turnArmy);
			fw.Write(turnTreatAsRelativeTurn);
		}

		if ((checkData & 0x20) != 0)
		{
			fw.Write(enUnitTotal);
			fw.Write(unitTotal);
			fw.Write(unitTotalCondition);
			fw.Write(unitTotalArmy);
			fw.Write(unitTotalLifeCondition);
		}

		if ((checkData & 0x40) != 0)
		{
			fw.Write(enGold);
			fw.Write(gold);
			fw.Write(goldCondition);
		}

		if ((checkData & 0x80u) != 0)
			this_32->dump(fw);

		if ((checkData & 0x100) != 0)
			this_33->dump(fw);

		if ((checkData & 0x200) != 0)
		{
			fw.Write(this_34);
			fw.Write(this_35);
			fw.Write(this_36);
			fw.Write(this_37);
			fw.Write(this_38);

			this_39->dump(fw);
			this_40->dump(fw);

			if (g_ArcVersion >= 0x442)
			{
				fw.Write(this_41);
				this_42->dump(fw);
			}
		}

		if ((checkData & 0x400) != 0)
		{
			fw.Write(enDistance);
			fw.Write(this_44);
			fw.Write(distanceRange);

			this_46->dump(fw);

			if (g_ArcVersion >= 0x442)
			{
				fw.Write(this_48);
				fw.Write(this_47);

				this_49->dump(fw);

				fw.Write(this_50);

				this_51->dump(fw);
			}

			if (g_ArcVersion >= 1278)
				fw.Write(this_140);
		}

		if ((checkData & 0x800) != 0)
		{
			fw.Write(this_52);
			fw.Write(this_53);
			fw.Write(this_54);
			fw.Write(this_55);
			fw.Write(this_56);

			this_57->dump(fw);

			if (g_ArcVersion >= 0x487)
			{
				fw.Write(this_58);
				this_59->dump(fw);
			}
		}

		if ((checkData & 0x1000) != 0)
		{
			fw.Write(this_60);
			fw.Write(this_61);
			fw.Write(this_62);
			fw.Write(this_63);
		}

		if ((checkData & 0x2000) != 0)
		{
			fw.Write(enStatComparison);
			fw.Write(this_65);
			fw.Write(this_66);
			fw.Write(this_67);
			fw.Write(statComparisonLeftOp);
			fw.Write(this_69);
			fw.Write(this_70);
			fw.Write(this_71);
			fw.Write(statComparisonCondition);
			fw.Write(this_73);
			fw.Write(this_74);
			fw.Write(this_75);
			fw.Write(statComparisonRightOp);
			fw.Write(this_77);
			fw.Write(this_78);
			fw.Write(this_79);
			fw.Write(statComparisonEnParamBonus);
			fw.Write(this_81);
			fw.Write(this_82);
		}

		if ((checkData & 0x4000) != 0)
		{
			fw.Write(enBonus);
			fw.Write(bonus);
			fw.Write(bonusCondition);
		}

		if ((checkData & 0x8000) != 0)
		{
			fw.Write(enProbability);
			fw.Write(probability);
		}

		if ((checkData & 0x10000) != 0)
		{
			fw.Write(enEnvironment);
			fw.Write(environmentCondition);
		}

		if ((checkData & 0x20000) != 0)
		{
			fw.Write(this_90);
			this_91->dump(fw);
		}

		if ((checkData & 0x40000) != 0)
		{
			fw.Write(this_92);
			this_93.Write(fw);
		}

		if ((checkData & 0x80000) != 0)
		{
			fw.Write(this_94);
			fw.Write(this_95);

			this_96->dump(fw);
		}

		if ((checkData & 0x100000) != 0)
		{
			fw.Write(enDataTotal);
			fw.Write(dataTotal);
			fw.Write(this_99);
			fw.Write(dataTotalCondition);
			fw.Write(this_101);

			this_102->dump(fw);

			if (g_ArcVersion >= 1277 && HIWORD(this_101))
			{
				fw.WriteBytes(this_141.data(), static_cast<DWORD>(this_141.size() * sizeof(DWORD)));
				fw.WriteBytes(this_142.data(), static_cast<DWORD>(this_142.size() * sizeof(DWORD)));

				if (g_ArcVersion >= 1051)
					fw.Write(this_143);
			}
		}

		return;
	}

	fw.Write(this_0);

	if (g_ArcVersion < 0x41B)
		fw.Write(this_1);
	else
	{
		if (this_0 > 0)
			fw.Write(this_1);
	}

	fw.Write(this_17);

	if (g_ArcVersion < 0x41B)
		fw.Write(this_18);
	else
	{
		if (this_17 > 0)
			fw.Write(this_18);
	}

	fw.Write(enTurn);

	if (g_ArcVersion < 0x41B)
	{
		fw.Write(turn);
		fw.Write(turnCondition);
		fw.Write(turnArmy);
		fw.Write(turnTreatAsRelativeTurn);
	}
	else
	{
		if (enTurn > 0)
		{
			fw.Write(turn);
			fw.Write(turnCondition);
			fw.Write(turnArmy);
			fw.Write(turnTreatAsRelativeTurn);
		}
	}

	fw.Write(enGold);
	if (g_ArcVersion < 0x41B)
	{
		fw.Write(gold);
		fw.Write(goldCondition);
	}
	else
	{
		if (enGold > 0)
		{
			fw.Write(gold);
			fw.Write(goldCondition);
		}
	}

	fw.Write(enUnitTotal);
	if (g_ArcVersion < 0x41B)
	{
		fw.Write(unitTotal);
		fw.Write(unitTotalCondition);
		fw.Write(unitTotalArmy);
		fw.Write(unitTotalLifeCondition);
	}
	else
	{
		if (enUnitTotal > 0)
		{
			fw.Write(unitTotal);
			fw.Write(unitTotalCondition);
			fw.Write(unitTotalArmy);
			fw.Write(unitTotalLifeCondition);
		}
	}

	fw.Write(enBonus);
	if (g_ArcVersion < 0x41B)
	{
		fw.Write(bonus);
		fw.Write(bonusCondition);
	}
	else
	{
		if (enBonus > 0)
		{
			fw.Write(bonus);
			fw.Write(bonusCondition);
		}
	}

	fw.Write(enEnvironment);
	if (g_ArcVersion < 0x41B)
	{
		fw.Write(environmentCondition);
	}
	else
	{
		if (enEnvironment > 0)
			fw.Write(environmentCondition);
	}

	fw.Write(this_90);
	fw.Write(this_92);

	if (g_ArcVersion < 0x3F5)
	{
		fw.Write(this_34);
		fw.Write(this_35);
		fw.Write(this_36);
		fw.Write(this_37);
	}
	else
	{
		if (g_ArcVersion < 0x41B)
		{
			fw.Write(this_34);
			fw.Write(this_35);
			fw.Write(this_36);
			fw.Write(this_37);
			fw.Write(this_38);
		}
		else
		{
			fw.Write(this_34);

			if (this_34 > 0)
			{
				fw.Write(this_35);
				fw.Write(this_36);
				fw.Write(this_37);
				fw.Write(this_38);
			}
		}
	}

	this_42->dump(fw);

	////

	if (g_ArcVersion >= 0x3F4)
	{
		fw.Write(this_12);
		if (g_ArcVersion >= 0x41B)
		{
			if (this_12 > 0)
			{
				fw.Write(this_13);
				fw.Write(this_14);
				fw.Write(this_15);
				fw.Write(this_16);
				fw.Write(this_17);
				fw.Write(this_18);
				fw.Write(enTurn);
				fw.Write(turn);
				fw.Write(turnCondition);
				fw.Write(turnArmy);
				fw.Write(turnTreatAsRelativeTurn);
				fw.Write(enGold);
				fw.Write(gold);
			}
		}
		else
		{
			fw.Write(this_13);
			fw.Write(this_14);
			fw.Write(this_15);
			fw.Write(this_16);
			fw.Write(this_17);
			fw.Write(this_18);
			fw.Write(enTurn);
			fw.Write(turn);
			fw.Write(turnCondition);
			fw.Write(turnArmy);
			fw.Write(turnTreatAsRelativeTurn);
			fw.Write(enGold);
			fw.Write(gold);
		}

		fw.Write(enProbability);
		if (g_ArcVersion < 0x41B)
			fw.Write(probability);
		else
		{
			if (enProbability > 0)
				fw.Write(probability);
		}
	}

	if (g_ArcVersion >= 0x411)
	{
		fw.Write(enDistance);
		if (g_ArcVersion < 0x41B)
		{
			fw.Write(this_44);
			fw.Write(distanceRange);
		}
		else
		{
			if (enDistance > 0)
			{
				fw.Write(this_44);
				fw.Write(distanceRange);
			}
		}

		this_46->dump(fw);
	}
	else
	{
		if (g_ArcVersion >= 0x3F9)
		{
			fw.Write(enDistance);
			fw.Write(this_44);

			this_46->dump(fw);
		}
	}

	if (g_ArcVersion >= 0x418)
	{
		fw.Write(this_52);

		if (g_ArcVersion < 0x41B)
		{
			fw.Write(this_53);
			fw.Write(this_54);
			fw.Write(this_55);
			fw.Write(this_56);
		}
		else
		{
			if (this_52)
			{
				fw.Write(this_53);
				fw.Write(this_54);
				fw.Write(this_55);
				fw.Write(this_56);
			}
		}

		this_57->dump(fw);
	}

	if (g_ArcVersion >= 0x41B)
	{
		fw.Write(this_60);
		if (this_60)
		{
			fw.Write(this_61);
			fw.Write(this_62);
			fw.Write(this_63);
		}

		fw.Write(enStatComparison);

		if (enStatComparison)
		{
			fw.Write(this_65);
			fw.Write(this_66);
			fw.Write(this_67);
			fw.Write(statComparisonLeftOp);
			fw.Write(this_69);
			fw.Write(this_70);
			fw.Write(this_71);
			fw.Write(statComparisonCondition);
			fw.Write(this_73);
			fw.Write(this_74);
			fw.Write(this_75);
			fw.Write(statComparisonRightOp);
			fw.Write(this_77);
			fw.Write(this_78);
			fw.Write(this_79);
			fw.Write(statComparisonEnParamBonus);
			fw.Write(this_81);
			fw.Write(this_82);
		}
	}

	////

	this_2->dump(fw);

	this_39->dump(fw);
	this_40->dump(fw);
	this_32->dump(fw);
	this_33->dump(fw);
	this_91->dump(fw);

	this_93.Write(fw);
}

void EVENTPAGE_DATA::sub_D5E70(FileReader& fw)
{
	if (g_ArcVersion < 0x3F4)
	{
		this_12                 = 0;
		this_13                 = 0;
		this_14                 = 0;
		this_15                 = 0;
		this_16                 = 0;
		this_17                 = 0;
		this_18                 = 0;
		enTurn                  = 0;
		turn                    = 1;
		turnCondition           = 0;
		turnArmy                = 0;
		turnTreatAsRelativeTurn = 0;
		enGold                  = 0;
		gold                    = 0;

		enProbability = 0;
		probability   = 0;
	}
	else
	{
		if (g_ArcVersion >= 0x41B)
		{
			this_12 = fw.ReadDWord();
			if (this_12 > 0)
			{
				this_13                 = fw.ReadDWord();
				this_14                 = fw.ReadDWord();
				this_15                 = fw.ReadDWord();
				this_16                 = fw.ReadDWord();
				this_17                 = fw.ReadDWord();
				this_18                 = fw.ReadDWord();
				enTurn                  = fw.ReadDWord();
				turn                    = fw.ReadDWord();
				turnCondition           = fw.ReadDWord();
				turnArmy                = fw.ReadDWord();
				turnTreatAsRelativeTurn = fw.ReadDWord();
				enGold                  = fw.ReadDWord();
				gold                    = fw.ReadDWord();
			}
		}
		else
		{
			this_12                 = fw.ReadDWord();
			this_13                 = fw.ReadDWord();
			this_14                 = fw.ReadDWord();
			this_15                 = fw.ReadDWord();
			this_16                 = fw.ReadDWord();
			this_17                 = fw.ReadDWord();
			this_18                 = fw.ReadDWord();
			enTurn                  = fw.ReadDWord();
			turn                    = fw.ReadDWord();
			turnCondition           = fw.ReadDWord();
			turnArmy                = fw.ReadDWord();
			turnTreatAsRelativeTurn = fw.ReadDWord();
			enGold                  = fw.ReadDWord();
			gold                    = fw.ReadDWord();
		}

		if (g_ArcVersion < 0x41B)
		{
			enProbability = fw.ReadDWord();
			probability   = fw.ReadDWord();
		}
		else
		{
			enProbability = fw.ReadDWord();
			if (enProbability > 0)
				probability = fw.ReadDWord();
		}
	}

	if (g_ArcVersion >= 0x411)
	{
		if (g_ArcVersion < 0x41B)
		{
			enDistance    = fw.ReadDWord();
			this_44       = fw.ReadDWord();
			distanceRange = fw.ReadDWord();
		}
		else
		{
			enDistance = fw.ReadDWord();

			if (enDistance > 0)
			{
				this_44       = fw.ReadDWord();
				distanceRange = fw.ReadDWord();
			}
		}

		allocAndSetCMenuOp(&this_46, SRPGClasses::TYPEIDDATA, fw);
	}
	else
	{
		if (g_ArcVersion < 0x3F9)
		{
			enDistance = 0;
			this_44    = 0;
			this_46    = new CMenuOperation(SRPGClasses::TYPEIDDATA);
		}
		else
		{
			enDistance = fw.ReadDWord();
			this_44    = fw.ReadDWord();

			allocAndSetCMenuOp(&this_46, SRPGClasses::TYPEIDDATA, fw);
		}
		distanceRange = 1;
	}

	this_47 = 0;
	this_48 = 1;

	this_49 = new CMenuOperation(SRPGClasses::TYPEIDDATA);
	this_50 = 0;
	this_51 = new CMenuOperation(SRPGClasses::TYPEIDDATA);

	if (g_ArcVersion >= 0x418)
	{
		if (g_ArcVersion < 0x41B)
		{
			this_52 = fw.ReadDWord();
			this_53 = fw.ReadDWord();
			this_54 = fw.ReadDWord();
			this_55 = fw.ReadDWord();
			this_56 = fw.ReadDWord();
		}
		else
		{
			this_52 = fw.ReadDWord();
			if (this_52)
			{
				this_53 = fw.ReadDWord();
				this_54 = fw.ReadDWord();
				this_55 = fw.ReadDWord();
				this_56 = fw.ReadDWord();
			}
		}

		allocAndSetCMenuOp(&this_57, SRPGClasses::TYPEIDDATA, fw);
	}
	else
	{
		this_52 = 0;
		this_53 = 0;
		this_54 = 0;
		this_55 = 1;
		this_56 = 0;
		this_57 = new CMenuOperation(SRPGClasses::TYPEIDDATA);

		if (this_6 == 4)
		{
			if (this_8 > 9)
				this_8 += +2;
		}
		if (this_9 == 4)
		{
			if (this_11 > 9)
				this_11 += 2;
		}
		if (this_13 == 4)
		{
			if (this_15 > 9)
				this_15 += 2;
		}
	}

	this_58 = 0;
	this_59 = new CMenuOperation(SRPGClasses::TYPEIDDATA);

	if (g_ArcVersion < 0x41B)
	{
		this_60                    = 0;
		this_61                    = 0;
		this_62                    = 0;
		this_63                    = 1;
		enStatComparison           = 0;
		this_65                    = 0;
		this_66                    = 12;
		this_67                    = 0;
		statComparisonLeftOp       = 0;
		this_69                    = 0;
		this_70                    = 12;
		this_71                    = 0;
		statComparisonCondition    = 0;
		this_73                    = 0;
		this_74                    = 12;
		this_75                    = 0;
		statComparisonRightOp      = 0;
		this_77                    = 0;
		this_78                    = 12;
		this_79                    = 0;
		statComparisonEnParamBonus = 0;
		this_81                    = 0;
		this_82                    = 0;
	}
	else
	{
		this_60 = fw.ReadDWord();
		if (this_60)
		{
			this_61 = fw.ReadDWord();
			this_62 = fw.ReadDWord();
			this_63 = fw.ReadDWord();
		}

		enStatComparison = fw.ReadDWord();
		if (enStatComparison)
		{
			this_65                    = fw.ReadDWord();
			this_66                    = fw.ReadDWord();
			this_67                    = fw.ReadDWord();
			statComparisonLeftOp       = fw.ReadDWord();
			this_69                    = fw.ReadDWord();
			this_70                    = fw.ReadDWord();
			this_71                    = fw.ReadDWord();
			statComparisonCondition    = fw.ReadDWord();
			this_73                    = fw.ReadDWord();
			this_74                    = fw.ReadDWord();
			this_75                    = fw.ReadDWord();
			statComparisonRightOp      = fw.ReadDWord();
			this_77                    = fw.ReadDWord();
			this_78                    = fw.ReadDWord();
			this_79                    = fw.ReadDWord();
			statComparisonEnParamBonus = fw.ReadDWord();
			this_81                    = fw.ReadDWord();
			this_82                    = fw.ReadDWord();
		}
	}
}

void EVENTPAGE_DATA::sub_D4F50(FileReader& fw)
{
	checkData = fw.ReadDWord();

	// this_2 = new SWITCHACTION();

	// this_2->sub_D1B60();

	if ((checkData & 1) != 0)
	{
		this_0 = fw.ReadDWord();
		this_1 = fw.ReadDWord();

		if (g_ArcVersion >= 0x502)
			allocAndSetCMenuOp(&this_2_new, SRPGClasses::TYPEIDDATA, fw);
	}

	if ((checkData & 2) != 0)
	{
		if (!this_2)
			this_2 = new SWITCHACTION();

		this_2->init(fw);
	}

	if ((checkData & 4) != 0)
	{
		// NOTE: This was changed in new versions, might cause problems
		if (g_ArcVersion < 0x4CE)
		{
			this_3  = fw.ReadDWord();
			this_4  = fw.ReadDWord();
			this_5  = fw.ReadDWord();
			this_6  = fw.ReadDWord();
			this_7  = fw.ReadDWord();
			this_8  = fw.ReadDWord();
			this_9  = fw.ReadDWord();
			this_10 = fw.ReadDWord();
			this_11 = fw.ReadDWord();
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
			this_15 = fw.ReadDWord();
			this_16 = fw.ReadDWord();
		}
		else
			allocAndSetCMenuOp(&this_3_new, SRPGClasses::VARIABLECONDITIONDATA, fw);
	}

	if ((checkData & 8) != 0)
	{
		this_17 = fw.ReadDWord();
		this_18 = fw.ReadDWord();
	}

	if ((checkData & 0x10) != 0)
	{
		enTurn                  = fw.ReadDWord();
		turn                    = fw.ReadDWord();
		turnCondition           = fw.ReadDWord();
		turnArmy                = fw.ReadDWord();
		turnTreatAsRelativeTurn = fw.ReadDWord();
	}

	if ((checkData & 0x20) != 0)
	{
		enUnitTotal            = fw.ReadDWord();
		unitTotal              = fw.ReadDWord();
		unitTotalCondition     = fw.ReadDWord();
		unitTotalArmy          = fw.ReadDWord();
		unitTotalLifeCondition = fw.ReadDWord();
	}

	if ((checkData & 0x40) != 0)
	{
		enGold        = fw.ReadDWord();
		gold          = fw.ReadDWord();
		goldCondition = fw.ReadDWord();
	}

	if ((checkData & 0x80u) != 0)
		allocAndSetCMenuOp(&this_32, SRPGClasses::ITEMCONDITIONDATA, fw);

	if ((checkData & 0x100) != 0)
		allocAndSetCMenuOp(&this_33, SRPGClasses::UNITCONDITIONDATA, fw);

	if ((checkData & 0x200) != 0)
	{
		this_34 = fw.ReadDWord();
		this_35 = fw.ReadDWord();
		this_36 = fw.ReadDWord();
		this_37 = fw.ReadDWord();
		this_38 = fw.ReadDWord();

		allocAndSetCMenuOp(&this_39, SRPGClasses::MAPPOSDATA, fw);
		allocAndSetCMenuOp(&this_40, SRPGClasses::MAPPOSDATA, fw);

		if (g_ArcVersion < 0x442)
			this_37 = (this_37 > 0) ? 7 : 1;
		else
		{
			this_41 = fw.ReadDWord();
			allocAndSetCMenuOp(&this_42, SRPGClasses::TYPEIDDATA, fw);
		}
	}

	if ((checkData & 0x400) != 0)
	{
		enDistance    = fw.ReadDWord();
		this_44       = fw.ReadDWord();
		distanceRange = fw.ReadDWord();

		allocAndSetCMenuOp(&this_46, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 0x442)
		{
			this_48 = fw.ReadDWord();
			this_47 = fw.ReadDWord();

			allocAndSetCMenuOp(&this_49, SRPGClasses::TYPEIDDATA, fw);

			this_50 = fw.ReadDWord();

			allocAndSetCMenuOp(&this_51, SRPGClasses::TYPEIDDATA, fw);
		}

		if (g_ArcVersion >= 1278)
			this_140 = fw.ReadDWord();
	}

	if ((checkData & 0x800) != 0)
	{
		this_52 = fw.ReadDWord();
		this_53 = fw.ReadDWord();
		this_54 = fw.ReadDWord();
		this_55 = fw.ReadDWord();
		this_56 = fw.ReadDWord();

		allocAndSetCMenuOp(&this_57, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 0x487)
		{
			this_58 = fw.ReadDWord();
			allocAndSetCMenuOp(&this_59, SRPGClasses::TYPEIDDATA, fw);
		}
	}

	if ((checkData & 0x1000) != 0)
	{
		this_60 = fw.ReadDWord();
		this_61 = fw.ReadDWord();
		this_62 = fw.ReadDWord();
		this_63 = fw.ReadDWord();
	}

	if ((checkData & 0x2000) != 0)
	{
		enStatComparison           = fw.ReadDWord();
		this_65                    = fw.ReadDWord();
		this_66                    = fw.ReadDWord();
		this_67                    = fw.ReadDWord();
		statComparisonLeftOp       = fw.ReadDWord();
		this_69                    = fw.ReadDWord();
		this_70                    = fw.ReadDWord();
		this_71                    = fw.ReadDWord();
		statComparisonCondition    = fw.ReadDWord();
		this_73                    = fw.ReadDWord();
		this_74                    = fw.ReadDWord();
		this_75                    = fw.ReadDWord();
		statComparisonRightOp      = fw.ReadDWord();
		this_77                    = fw.ReadDWord();
		this_78                    = fw.ReadDWord();
		this_79                    = fw.ReadDWord();
		statComparisonEnParamBonus = fw.ReadDWord();
		this_81                    = fw.ReadDWord();
		this_82                    = fw.ReadDWord();
	}

	if ((checkData & 0x4000) != 0)
	{
		enBonus        = fw.ReadDWord();
		bonus          = fw.ReadDWord();
		bonusCondition = fw.ReadDWord();
	}

	if ((checkData & 0x8000) != 0)
	{
		enProbability = fw.ReadDWord();
		probability   = fw.ReadDWord();
	}

	if ((checkData & 0x10000) != 0)
	{
		enEnvironment        = fw.ReadDWord();
		environmentCondition = fw.ReadDWord();
	}

	if ((checkData & 0x20000) != 0)
	{
		this_90 = fw.ReadDWord();
		allocAndSetCMenuOp(&this_91, SRPGClasses::TYPEIDDATA, fw);
	}

	if ((checkData & 0x40000) != 0)
	{
		this_92 = fw.ReadDWord();
		initMemData(this_93, fw);
	}

	if ((checkData & 0x80000) != 0)
	{
		this_94 = fw.ReadDWord();
		this_95 = fw.ReadDWord();

		allocAndSetCMenuOp(&this_96, SRPGClasses::TYPEIDDATA, fw);
	}

	if ((checkData & 0x100000) != 0)
	{
		enDataTotal        = fw.ReadDWord();
		dataTotal          = fw.ReadDWord();
		this_99            = fw.ReadDWord();
		dataTotalCondition = fw.ReadDWord();
		this_101           = fw.ReadDWord();

		allocAndSetCMenuOp(&this_102, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 1277 && HIWORD(this_101))
		{
			fw.ReadBytes(this_141.data(), static_cast<DWORD>(this_141.size() * sizeof(DWORD)));
			fw.ReadBytes(this_142.data(), static_cast<DWORD>(this_142.size() * sizeof(DWORD)));
			this_143 = fw.ReadDWord();
		}
	}
}
