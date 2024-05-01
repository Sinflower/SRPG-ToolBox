/*
 *  File: UNITDATA.h
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

struct UNITDATA : public EDITDATA
{
	DWORD checkVal = 0;

	DWORD hp   = 0;
	DWORD str  = 0;
	DWORD mag  = 0;
	DWORD skl  = 0;
	DWORD spd  = 0;
	DWORD lck  = 0;
	DWORD def  = 0;
	DWORD res  = 0;
	DWORD mov  = 0;
	DWORD wlv  = 0;
	DWORD bld  = 0;
	QWORD icon = 0;
	MemData name;
	MemData description;
	DWORD this_18    = 0;
	DWORD this_19    = 0;
	DWORD lvl        = 0;
	DWORD this_21    = 0;
	DWORD item01     = 0;
	DWORD item02     = 0;
	DWORD item03     = 0;
	DWORD item04     = 0;
	DWORD item05     = 0;
	DWORD item06     = 0;
	DWORD item07     = 0;
	DWORD item08     = 0;
	DWORD item09     = 0;
	DWORD item10     = 0;
	DWORD item11     = 0;
	DWORD item12     = 0;
	DWORD item13     = 0;
	DWORD item14     = 0;
	DWORD item15     = 0;
	DWORD item16     = 0;
	DWORD item17     = 0;
	DWORD item18     = 0;
	DWORD item19     = 0;
	DWORD item20     = 0;
	DWORD this_42    = 0;
	DWORD importance = 0;
	DWORD grHP       = 0;
	DWORD grStr      = 0;
	DWORD grMag      = 0;
	DWORD grSkl      = 0;
	DWORD grSpd      = 0;
	DWORD grLck      = 0;
	DWORD grDef      = 0;
	DWORD grRes      = 0;
	DWORD grMov      = 0;
	DWORD grWlv      = 0;
	DWORD grBld      = 0;
	DWORD this_55    = 0;
	DWORD this_56    = 0;
	DWORD this_57    = 0;
	WORD this_58     = 0;
	DWORD this_59    = 0;
	DWORD this_60    = 0;
	DWORD this_61    = 0;
	DWORD this_62    = 0;
	DWORD this_63    = 0;
	DWORD this_64    = 0;
	DWORD this_65    = 0;
	DWORD this_66    = 0;
	DWORD this_67    = 0;
	DWORD this_68    = 0;
	DWORD this_69    = 0;
	DWORD this_70    = 0;
	DWORD this_71    = 0;
	DWORD this_72    = 0;
	DWORD this_73    = 0;
	DWORD this_74    = 0;
	DWORD this_75    = 0;
	DWORD this_76    = 0;
	MemData customParameters;
	class CMenuOperation* this_78 = nullptr;
	class CMenuOperation* this_79 = nullptr;
	class CMenuOperation* this_80 = nullptr;
	class CMenuOperation* this_81 = nullptr;
	class CMenuOperation* this_82 = nullptr;
	class CMenuOperation* this_83 = nullptr;
	class CMenuOperation* this_84 = nullptr;
	class CMenuOperation* this_85 = nullptr;
	class CMenuOperation* this_86 = nullptr;
	class CMenuOperation* this_87 = nullptr;
	class CMenuOperation* this_88 = nullptr;
	class CMenuOperation* this_89 = nullptr;
	DWORD this_90                 = 0;
	DWORD this_91                 = 0;
	DWORD this_92                 = 0;
	DWORD this_93                 = 0;
	DWORD this_94                 = 0;
	DWORD this_95                 = 0;
	DWORD this_96                 = 0;
	DWORD this_97                 = 0;
	DWORD this_99                 = 0;
	DWORD this_100                = 0;
	DWORD this_102                = 0;
	MemData this_103;
	DWORD this_105 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	void sub_F7E930(FileReader& fw);
	void sub_F7E130(FileReader& fw);
	void sub_F7E310(FileReader& fw);
	void sub_F6F1D0(FileReader& fw);

	void print(std::ostream& os) const;
};
