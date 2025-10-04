/*
 *  File: CLASSDATA.h
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

#include "LEGENDDATA.h"

struct CLASSDATA : public LEGENDDATA
{
	DWORD res1 = 0;
	DWORD res2 = 0;
	DWORD res3 = 0;

	DWORD this_8      = 0;
	DWORD this_9      = 0;
	DWORD optionalExp = 0;
	DWORD this_12     = 0;
	DWORD this_13     = 0;
	DWORD this_14     = 0;
	DWORD this_15     = 0;
	DWORD this_16     = 0;
	DWORD this_17     = 0;
	DWORD this_18     = 0;
	DWORD this_19     = 0;
	DWORD this_20     = 0;

	class CMenuOperation* m_pUnitStatusData = nullptr;
	class CMenuOperation* m_pTypeIDData1    = nullptr;
	class CMenuOperation* m_pTypeIDData2    = nullptr;
	class CMenuOperation* m_pTypeIDData3    = nullptr;

	DWORD this_25       = 0;
	DWORD paramBonusHp  = 0;
	DWORD paramBonusStr = 0;
	DWORD paramBonusMag = 0;
	DWORD paramBonusSkl = 0;
	DWORD paramBonusSpd = 0;
	DWORD paramBonusLck = 0;
	DWORD paramBonusDef = 0;
	DWORD paramBonusRes = 0;
	DWORD paramBonusMov = 0;
	DWORD paramBonusWlv = 0;
	DWORD paramBonusBld = 0;
	DWORD grothBonusHp  = 0;
	DWORD grothBonusStr = 0;
	DWORD grothBonusMag = 0;
	DWORD grothBonusSkl = 0;
	DWORD grothBonusSpd = 0;
	DWORD grothBonusLck = 0;
	DWORD grothBonusDef = 0;
	DWORD grothBonusRes = 0;
	DWORD grothBonusMov = 0;
	DWORD grothBonusWlv = 0;
	DWORD grothBonusBld = 0;

	class CMenuOperation* m_pMotionIDData1         = nullptr;
	class CMenuOperation* m_pMotionIDData2         = nullptr;
	class CMenuOperation* m_pMotionIDData3         = nullptr;
	struct UNITPROTOTYPEDATA* m_pUnitPrototypeData = nullptr;
	std::array<DWORD, 11> this_53                  = { 0 };

	DWORD this_64 = 0;
	DWORD this_65 = 0;
	DWORD this_66 = 0;
	DWORD this_67 = 0;
	DWORD this_68 = 0;
	DWORD this_69 = 0;
	DWORD this_70 = 0;
	DWORD this_71 = 0;
	DWORD this_72 = 0;
	DWORD this_73 = 0;
	DWORD this_74 = 0;
	DWORD this_75 = 0;
	MemData this_76;
	class CMenuOperation* m_pCharReplaceData = nullptr;

	DWORD this_78 = 0;
	MemData this_79;

	void init(FileReader& fw) override;
	void dump([[maybe_unused]] FileWriter& fw) const override;
	void print(std::ostream& os) const override;

private:
	void sub_360EA0(FileReader& fw);
	void sub_37E310(FileReader& fw);
	void sub_36E310(FileReader& fw);
	void sub_35FF20(FileReader& fw, int a3);
};
