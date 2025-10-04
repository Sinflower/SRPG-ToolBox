/*
 *  File: MAPDATA.h
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
#include "LEGENDDATA.h"

struct MAPDATA : public EDITDATA, public LEGENDDATA
{
	DWORD width    = 0;
	DWORD height   = 0;
	DWORD chapter  = 0;
	DWORD maxUnits = 0;
	std::vector<QWORD> this_12;
	DWORD mapColor        = 0;
	DWORD dispBattlePrep  = 0;
	DWORD mapType         = 0;
	DWORD mapScroll       = 0;
	DWORD this_115        = 0;
	DWORD this_116        = 0;
	QWORD fixedBackground = 0;
	QWORD bgmPlayerPhase  = 0;
	QWORD bgmEnemyPhase   = 0;
	QWORD bgmAllyPhase    = 0;
	QWORD bgmPlayerBattle = 0;
	QWORD bgmEnemyBattle  = 0;
	QWORD bgmAllyBattle   = 0;
	QWORD bgmBattlePrep   = 0;
	MemData this_136;
	MemData this_137;
	class CMenuOperation* pEnemyUnits         = nullptr;
	class CMenuOperation* pEvEnemyUnits       = nullptr;
	class CMenuOperation* pAllyUnits          = nullptr;
	class CMenuOperation* pEvAllyUnits        = nullptr;
	class CMenuOperation* placeEvents         = nullptr;
	class CMenuOperation* autoEvents          = nullptr;
	class CMenuOperation* talkEvents          = nullptr;
	class CMenuOperation* openingEvents       = nullptr;
	class CMenuOperation* endingEvents        = nullptr;
	class CMenuOperation* communicationEvents = nullptr;
	class CMenuOperation* this_148            = nullptr;
	class CMenuOperation* pReinforcementUnits = nullptr;
	DWORD this_150                            = 0;
	class CMenuOperation* this_151            = nullptr;
	class CMenuOperation* localSwitches       = nullptr;
	DWORD this_153                            = 0;
	DWORD this_154                            = 0;
	DWORD this_155                            = 0;
	DWORD this_156                            = 0;
	DWORD this_157                            = 0;
	class CMenuOperation* this_158            = nullptr;
	class CMenuOperation* this_159            = nullptr;
	class CMenuOperation* victoryCond         = nullptr;
	class CMenuOperation* defeatCond          = nullptr;
	class CMenuOperation* this_162            = nullptr;
	MemData mapName;
	MemData customParameters;
	class CMenuOperation* pGuestUnits   = nullptr;
	class CMenuOperation* pEvGuestUnits = nullptr;
	DWORD this_167                      = 0;
	class CMenuOperation* this_168      = nullptr;

	std::array<DWORD, 12> this_200;
	std::array<DWORD, 12> this_201;
	DWORD this_202 = 0;

	virtual void print(std::ostream& os) const;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

protected:
	virtual nlohmann::ordered_json toJson() const override;

private:
	void sub_F7D9C0(FileReader& fw);
	void sub_F7A340(FileReader& fw);
	void sub_F77950(FileReader& fw);
	void sub_F7A3B0(FileReader& fw);
};
