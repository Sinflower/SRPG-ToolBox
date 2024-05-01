/*
 *  File: PATTERNDATA.h
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
#include "EVENTPAGE_DATA.h"

struct PATTERNDATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	EVENTPAGE_DATA this_5;
	struct APPROACHPATTERN* this_7 = nullptr;
	struct WAITPATTERN* this_8     = nullptr;
	struct MOVEPATTERN* this_9     = nullptr;
	struct CUSTOMPATTERN* this_10  = nullptr;
	class CMenuOperation* this_11  = nullptr;
	DWORD this_12                  = 0;
	DWORD this_13                  = 0;
	DWORD this_14                  = 0;
	class CMenuOperation* this_15  = nullptr;
	DWORD this_16                  = 0;
	class CMenuOperation* this_17  = nullptr;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
