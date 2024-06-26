/*
 *  File: EVENTPAGE_DATA.h
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

#pragma once

#include "EDITDATA.h"

struct EVENTPAGE_DATA
{
	friend std::ostream& operator<<(std::ostream& os, EVENTPAGE_DATA const& data)
	{
		os << "#######################################" << std::endl;
		os << "EventPageData: " << std::endl;
		os << "this_0: " << data.this_0 << std::endl;
		os << "this_1: " << data.this_1 << std::endl;
		os << "this_2: " << data.this_2 << std::endl;
		os << "this_3: " << data.this_3 << std::endl;
		os << "this_4: " << data.this_4 << std::endl;
		os << "this_5: " << data.this_5 << std::endl;
		os << "this_6: " << data.this_6 << std::endl;
		os << "this_7: " << data.this_7 << std::endl;
		os << "this_8: " << data.this_8 << std::endl;
		os << "this_9: " << data.this_9 << std::endl;
		os << "this_10: " << data.this_10 << std::endl;
		os << "this_11: " << data.this_11 << std::endl;
		os << "this_12: " << data.this_12 << std::endl;
		os << "this_13: " << data.this_13 << std::endl;
		os << "this_14: " << data.this_14 << std::endl;
		os << "this_15: " << data.this_15 << std::endl;
		os << "this_16: " << data.this_16 << std::endl;
		os << "this_17: " << data.this_17 << std::endl;
		os << "this_18: " << data.this_18 << std::endl;
		os << "Enable Turn: " << data.enTurn << std::endl;
		os << "Turn: " << data.turn << std::endl;
		os << "Turn Condition: " << data.turnCondition << std::endl;
		os << "Turn Army: " << data.turnArmy << std::endl;
		os << "Turn Treat as Relative Turn: " << data.turnTreatAsRelativeTurn << std::endl;
		os << "Enable Gold: " << data.enGold << std::endl;
		os << "Gold: " << data.gold << std::endl;
		os << "Gold Condition: " << data.goldCondition << std::endl;
		os << "Enable Unit Total: " << data.enUnitTotal << std::endl;
		os << "Unit Total: " << data.unitTotal << std::endl;
		os << "Unit Total Condition: " << data.unitTotalCondition << std::endl;
		os << "Unit Total Army: " << data.unitTotalArmy << std::endl;
		os << "Unit Total Life Condition: " << data.unitTotalLifeCondition << std::endl;
		os << "this_32: " << data.this_32 << std::endl;
		os << "this_33: " << data.this_33 << std::endl;
		os << "this_34: " << data.this_34 << std::endl;
		os << "this_35: " << data.this_35 << std::endl;
		os << "this_36: " << data.this_36 << std::endl;
		os << "this_37: " << data.this_37 << std::endl;
		os << "this_38: " << data.this_38 << std::endl;
		os << "this_39: " << data.this_39 << std::endl;
		os << "this_40: " << data.this_40 << std::endl;
		os << "this_41: " << data.this_41 << std::endl;
		os << "this_42: " << data.this_42 << std::endl;
		os << "Enable Distance: " << data.enDistance << std::endl;
		os << "this_44: " << data.this_44 << std::endl;
		os << "Distance Range: " << data.distanceRange << std::endl;
		os << "this_46: " << data.this_46 << std::endl;
		os << "this_47: " << data.this_47 << std::endl;
		os << "this_48: " << data.this_48 << std::endl;
		os << "this_49: " << data.this_49 << std::endl;
		os << "this_50: " << data.this_50 << std::endl;
		os << "this_51: " << data.this_51 << std::endl;
		os << "this_52: " << data.this_52 << std::endl;
		os << "this_53: " << data.this_53 << std::endl;
		os << "this_54: " << data.this_54 << std::endl;
		os << "this_55: " << data.this_55 << std::endl;
		os << "this_56: " << data.this_56 << std::endl;
		os << "this_57: " << data.this_57 << std::endl;
		os << "this_58: " << data.this_58 << std::endl;
		os << "this_59: " << data.this_59 << std::endl;
		os << "this_60: " << data.this_60 << std::endl;
		os << "this_61: " << data.this_61 << std::endl;
		os << "this_62: " << data.this_62 << std::endl;
		os << "this_63: " << data.this_63 << std::endl;
		os << "Enable Stat Comparison: " << data.enStatComparison << std::endl;
		os << "this_65: " << data.this_65 << std::endl;
		os << "this_66: " << data.this_66 << std::endl;
		os << "this_67: " << data.this_67 << std::endl;
		os << "Stat Comparison Left Operation: " << data.statComparisonLeftOp << std::endl;
		os << "this_69: " << data.this_69 << std::endl;
		os << "this_70: " << data.this_70 << std::endl;
		os << "this_71: " << data.this_71 << std::endl;
		os << "Stat Comparison Condition: " << data.statComparisonCondition << std::endl;
		os << "this_73: " << data.this_73 << std::endl;
		os << "this_74: " << data.this_74 << std::endl;
		os << "this_75: " << data.this_75 << std::endl;
		os << "Stat Comparison Right Operation: " << data.statComparisonRightOp << std::endl;
		os << "this_77: " << data.this_77 << std::endl;
		os << "this_78: " << data.this_78 << std::endl;
		os << "this_79: " << data.this_79 << std::endl;
		os << "Stat Comparison Enable Paramter Bonus: " << data.statComparisonEnParamBonus << std::endl;
		os << "this_81: " << data.this_81 << std::endl;
		os << "this_82: " << data.this_82 << std::endl;
		os << "Enable Bonus: " << data.enBonus << std::endl;
		os << "Bonus: " << data.bonus << std::endl;
		os << "Bonus Condition: " << data.bonusCondition << std::endl;
		os << "Enable Probability: " << data.enProbability << std::endl;
		os << "Probability: " << data.probability << std::endl;
		os << "Enable Environment: " << data.enEnvironment << std::endl;
		os << "Environment Condition: " << data.environmentCondition << std::endl;
		os << "this_90: " << data.this_90 << std::endl;
		os << "this_91: " << data.this_91 << std::endl;
		os << "this_92: " << data.this_92 << std::endl;
		os << "this_93: " << data.this_93 << std::endl;
		os << "this_94: " << data.this_94 << std::endl;
		os << "this_95: " << data.this_95 << std::endl;
		os << "this_96: " << data.this_96 << std::endl;
		os << "Enable Data Total: " << data.enDataTotal << std::endl;
		os << "Data Total: " << data.dataTotal << std::endl;
		os << "this_99: " << data.this_99 << std::endl;
		os << "Data Total Condition: " << data.dataTotalCondition << std::endl;
		os << "this_101: " << data.this_101 << std::endl;
		os << "this_102: " << data.this_102 << std::endl;
		os << "this_136: " << data.this_136 << std::endl;
		os << "this_137: " << data.this_137 << std::endl;
		os << "this_138: " << data.this_138 << std::endl;
		os << "this_139: " << data.this_139 << std::endl;
		os << "#######################################";
		return os;
	}
	void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

private:
	void sub_D5E70(FileReader& fw);
	void sub_D4F50(FileReader& fw);

public:
	DWORD checkData = 0;

	DWORD this_0                     = 0;
	DWORD this_1                     = 0;
	class CMenuOperation* this_2_new = nullptr;
	struct SWITCHACTION* this_2      = nullptr;
	///////////////////
	DWORD this_3  = 0;
	DWORD this_4  = 0;
	DWORD this_5  = 0;
	DWORD this_6  = 0;
	DWORD this_7  = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	///////////////////
	// New version use the VARIABLECONDITIONDATA class instead of single values
	class CMenuOperation* this_3_new = nullptr;
	///////////////////
	DWORD this_17                    = 0;
	DWORD this_18                    = 0;
	DWORD enTurn                     = 0;
	DWORD turn                       = 1;
	DWORD turnCondition              = 0;
	DWORD turnArmy                   = 0;
	DWORD turnTreatAsRelativeTurn    = 0;
	DWORD enGold                     = 0;
	DWORD gold                       = 0;
	DWORD goldCondition              = 0;
	DWORD enUnitTotal                = 0;
	DWORD unitTotal                  = 1;
	DWORD unitTotalCondition         = 0;
	DWORD unitTotalArmy              = 0;
	DWORD unitTotalLifeCondition     = 0;
	class CMenuOperation* this_32    = nullptr;
	class CMenuOperation* this_33    = nullptr;
	DWORD this_34                    = 0;
	DWORD this_35                    = 0;
	DWORD this_36                    = 0;
	DWORD this_37                    = 0;
	DWORD this_38                    = 0;
	class CMenuOperation* this_39    = nullptr;
	class CMenuOperation* this_40    = nullptr;
	DWORD this_41                    = 0;
	class CMenuOperation* this_42    = nullptr;
	DWORD enDistance                 = 0;
	DWORD this_44                    = 0;
	DWORD distanceRange              = 1;
	class CMenuOperation* this_46    = nullptr;
	DWORD this_47                    = 0;
	DWORD this_48                    = 1;
	class CMenuOperation* this_49    = nullptr;
	DWORD this_50                    = 0;
	class CMenuOperation* this_51    = nullptr;
	DWORD this_52                    = 0;
	DWORD this_53                    = 0;
	DWORD this_54                    = 0;
	DWORD this_55                    = 1;
	DWORD this_56                    = 0;
	class CMenuOperation* this_57    = nullptr;
	DWORD this_58                    = 0;
	class CMenuOperation* this_59    = nullptr;
	DWORD this_60                    = 0;
	DWORD this_61                    = 0;
	DWORD this_62                    = 0;
	DWORD this_63                    = 1;
	DWORD enStatComparison           = 0;
	DWORD this_65                    = 0;
	DWORD this_66                    = 12;
	DWORD this_67                    = 0;
	DWORD statComparisonLeftOp       = 0;
	DWORD this_69                    = 0;
	DWORD this_70                    = 12;
	DWORD this_71                    = 0;
	DWORD statComparisonCondition    = 0;
	DWORD this_73                    = 0;
	DWORD this_74                    = 12;
	DWORD this_75                    = 0;
	DWORD statComparisonRightOp      = 0;
	DWORD this_77                    = 0;
	DWORD this_78                    = 12;
	DWORD this_79                    = 0;
	DWORD statComparisonEnParamBonus = 0;
	DWORD this_81                    = 0;
	DWORD this_82                    = 0;
	DWORD enBonus                    = 0;
	DWORD bonus                      = 0;
	DWORD bonusCondition             = 0;
	DWORD enProbability              = 0;
	DWORD probability                = 0;
	DWORD enEnvironment              = 0;
	DWORD environmentCondition       = 0;
	DWORD this_90                    = 0;
	class CMenuOperation* this_91    = nullptr;
	DWORD this_92                    = 0;
	MemData this_93;
	DWORD this_94                  = 0;
	DWORD this_95                  = 1;
	class CMenuOperation* this_96  = nullptr;
	DWORD enDataTotal              = 0;
	DWORD dataTotal                = 1;
	DWORD this_99                  = 1;
	DWORD dataTotalCondition       = 0;
	DWORD this_101                 = 0;
	class CMenuOperation* this_102 = nullptr;
	DWORD this_136                 = 0;
	DWORD this_137                 = 0;
	DWORD this_138                 = 0;
	DWORD this_139                 = 0;

	// NEW
	DWORD this_140 = 0;
	std::array<DWORD, 12> this_141;
	std::array<DWORD, 12> this_142;
	DWORD this_143 = 0;
};
