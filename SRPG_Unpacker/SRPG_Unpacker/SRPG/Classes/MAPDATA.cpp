/*
 *  File: MAPDATA.cpp
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

#include "MAPDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void MAPDATA::print(std::ostream& os) const
{
	os << "MAPDATA: " << std::endl
	   << "ID: " << id << std::endl;

	LEGENDDATA::print(os);
	os << std::endl
	   << "Wdith: " << width << std::endl
	   << "Height: " << height << std::endl
	   << "Chapter: " << chapter << std::endl
	   << "Max Units: " << maxUnits << std::endl
	   << "Map Color: " << mapColor << std::endl
	   << "Display Battle Prep: " << std::hex << dispBattlePrep << std::dec << std::endl
	   << "Map Type: " << mapType << std::endl
	   << "Map Scroll: " << mapScroll << std::endl
	   << "this_115: " << this_115 << std::endl
	   << "this_116: " << this_116 << std::endl
	   << "Fixed Background: " << std::hex << fixedBackground << std::endl
	   << "BGM Player Phase: " << bgmPlayerPhase << std::endl
	   << "BGM Enemy Phase: " << bgmEnemyPhase << std::endl
	   << "BGM Ally Phase: " << bgmAllyPhase << std::endl
	   << "BGM Player Battle: " << bgmPlayerBattle << std::endl
	   << "BGM Enemy Battle: " << bgmEnemyBattle << std::endl
	   << "BGM Ally Battle: " << bgmAllyBattle << std::endl
	   << "BGM Battle Prep: " << bgmBattlePrep << std::dec << std::endl
	   << "this_150: " << this_150 << std::endl
	   << "this_153: " << this_153 << std::endl
	   << "this_154: " << this_154 << std::endl
	   << "this_155: " << this_155 << std::endl
	   << "this_156: " << this_156 << std::endl
	   << "this_157: " << this_157 << std::endl
	   << "this_167: " << this_167 << std::endl
	   << "Victory Conditions: " << *victoryCond << std::endl
	   << "Defeat Conditions: " << *defeatCond;

	os << std::endl
	   << "Map Name: " << mapName << std::endl;
	os << "Custom Parameters: " << customParameters << std::endl;
	os << "Local Switches: " << std::endl
	   << *localSwitches << std::endl;
}

void MAPDATA::init(FileReader& fw)
{
	width    = fw.ReadDWord();
	height   = fw.ReadDWord();
	maxUnits = fw.ReadDWord();

	this_12 = std::vector<QWORD>(maxUnits, 0);
	fw.ReadBytes(this_12.data(), sizeof(QWORD) * maxUnits);

	chapter        = fw.ReadDWord();
	mapColor       = fw.ReadDWord();
	dispBattlePrep = fw.ReadDWord();
	mapType        = fw.ReadDWord();

	sub_F7A3B0(fw);

	fixedBackground = fw.ReadQWord();

	bgmPlayerPhase  = fw.ReadQWord();
	bgmEnemyPhase   = fw.ReadQWord();
	bgmAllyPhase    = fw.ReadQWord();
	bgmPlayerBattle = fw.ReadQWord();
	bgmEnemyBattle  = fw.ReadQWord();
	bgmAllyBattle   = fw.ReadQWord();
	bgmBattlePrep   = fw.ReadQWord();

	if (g_ArcVersion < 0x404)
	{
		NOT_IMPLEMENTED
		// sub_F77950((_DWORD*)Size, *(_DWORD*)(this_162));
	}

	DWORD v8 = 4 * width * height;

	initMemData(this_136, fw, v8);
	initMemData(this_137, fw, v8);
	initMemData(mapName, fw);
	initMemData(customParameters, fw);

	LEGENDDATA::init(fw);

	allocAndSetCMenuOp(&victoryCond, SRPGClasses::STRINGDATA, fw);
	allocAndSetCMenuOp(&defeatCond, SRPGClasses::STRINGDATA, fw);
	allocAndSetCMenuOp(&localSwitches, SRPGClasses::SWITCHDATA, fw);
	allocAndSetCMenuOp(&this_138, SRPGClasses::UNITDATA, fw);
	allocAndSetCMenuOp(&this_140, SRPGClasses::UNITDATA, fw);

	if (g_ArcVersion < 0x3EE)
	{
		if (this_165)
			delete (this_165);
		this_165 = new CMenuOperation(SRPGClasses::UNITDATA);
	}
	else
		allocAndSetCMenuOp(&this_165, SRPGClasses::UNITDATA, fw);

	allocAndSetCMenuOp(&this_139, SRPGClasses::UNITDATA, fw);
	allocAndSetCMenuOp(&this_141, SRPGClasses::UNITDATA, fw);

	sub_F7A340(fw);

	allocAndSetCMenuOp(&placeEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&autoEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&talkEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&openingEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&endingEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&communicationEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&this_148, SRPGClasses::REINFORCECONTAINER, fw);
	allocAndSetCMenuOp(&this_149, SRPGClasses::UNITDATA, fw);

	// std::cout << "======================================" << std::endl
	//	<< "Place Events:" << std::endl << *placeEvents << std::endl
	//	<< "======================================" << std::endl;
	// std::cout << *autoEvents << std::endl;
	// std::cout << *talkEvents << std::endl;
	// std::cout << *openingEvents << std::endl;
	// std::cout << *endingEvents << std::endl;
	// std::cout << *communicationEvents << std::endl;

	this_150 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_151, SRPGClasses::TESTMEMBER, fw);

	sub_F7D9C0(fw);

	allocAndSetCMenuOp(&this_159, SRPGClasses::FORCESORTIEDATA, fw);

	if (g_ArcVersion >= 0x404)
		allocAndSetCMenuOp(&this_162, SRPGClasses::SHOPDATA, fw);

	if (g_ArcVersion >= 0x48A)
	{
		this_167 = fw.ReadDWord();

		allocAndSetCMenuOp(&this_168, SRPGClasses::TYPEIDDATA, fw);

		if (g_ArcVersion >= 0x4FD)
		{
			if (HIWORD(this_167) == 1)
			{
				fw.ReadBytes(this_200.data(), static_cast<DWORD>(this_200.size() * sizeof(DWORD)));
				fw.ReadBytes(this_201.data(), static_cast<DWORD>(this_201.size() * sizeof(DWORD)));
				this_202 = fw.ReadDWord();
			}
		}
	}
}

nlohmann::ordered_json MAPDATA::toJson() const
{
	nlohmann::ordered_json j;
	j["id"]          = id;
	j["name"]        = LEGENDDATA::name;
	j["description"] = LEGENDDATA::description;
	j["mapName"]     = mapName.ToString();
	j["victoryConds"] = victoryCond->ToJson();
	j["defeatConds"]  = defeatCond->ToJson();

	// No idea what this is but it's not relevant for now ... probably
	// j["this_136"]            = this_136.ToString();
	// j["this_137"]            = this_137.ToString();

	this_138->ToJson(j, "this_138");
	this_139->ToJson(j, "this_139");
	this_140->ToJson(j, "this_140");
	this_141->ToJson(j, "this_141");
	placeEvents->ToJson(j, "placeEvents");
	autoEvents->ToJson(j, "autoEvents");
	talkEvents->ToJson(j, "talkEvents");
	openingEvents->ToJson(j, "openingEvents");
	endingEvents->ToJson(j, "endingEvents");
	communicationEvents->ToJson(j, "communicationEvents");
	this_148->ToJson(j, "this_148");
	this_149->ToJson(j, "this_149");
	this_162->ToJson(j, "this_162");
	this_165->ToJson(j, "this_165");
	this_166->ToJson(j, "this_166");

	return j;
}

void MAPDATA::dump(FileWriter& fw) const
{
	fw.Write(width);
	fw.Write(height);
	fw.Write(maxUnits);

	fw.WriteBytes(this_12.data(), sizeof(QWORD) * maxUnits);

	fw.Write(chapter);
	fw.Write(mapColor);
	fw.Write(dispBattlePrep);
	fw.Write(mapType);

	if (g_ArcVersion >= 0x406)
		fw.Write(mapScroll);

	if (g_ArcVersion >= 0x43D)
	{
		fw.Write(this_115);
		fw.Write(this_116);
	}

	fw.Write(fixedBackground);

	fw.Write(bgmPlayerPhase);
	fw.Write(bgmEnemyPhase);
	fw.Write(bgmAllyPhase);
	fw.Write(bgmPlayerBattle);
	fw.Write(bgmEnemyBattle);
	fw.Write(bgmAllyBattle);
	fw.Write(bgmBattlePrep);

	if (g_ArcVersion < 0x404)
	{
		NOT_IMPLEMENTED
		// sub_F77950((_DWORD*)Size, *(_DWORD*)(this_162));
	}

	this_136.Write(fw);
	this_137.Write(fw);
	mapName.Write(fw);
	customParameters.Write(fw);

	LEGENDDATA::dump(fw);

	victoryCond->dump(fw);
	defeatCond->dump(fw);
	localSwitches->dump(fw);
	this_138->dump(fw);
	this_140->dump(fw);

	if (g_ArcVersion >= 0x3EE)
		this_165->dump(fw);

	this_139->dump(fw);
	this_141->dump(fw);

	if (g_ArcVersion >= 0x3EE)
		this_166->dump(fw);

	placeEvents->dump(fw);
	autoEvents->dump(fw);
	talkEvents->dump(fw);
	openingEvents->dump(fw);
	endingEvents->dump(fw);
	communicationEvents->dump(fw);
	this_148->dump(fw);
	this_149->dump(fw);

	fw.Write(this_150);

	this_151->dump(fw);

	fw.Write(this_153);
	fw.Write(this_154);
	fw.Write(this_155);
	fw.Write(this_156);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_157);

	this_158->dump(fw);

	this_159->dump(fw);

	if (g_ArcVersion >= 0x404)
		this_162->dump(fw);

	if (g_ArcVersion >= 0x48A)
	{
		fw.Write(this_167);

		this_168->dump(fw);

		if (g_ArcVersion >= 0x4FD)
		{
			if (HIWORD(this_167) == 1)
			{
				fw.WriteBytes(this_200.data(), static_cast<DWORD>(this_200.size() * sizeof(DWORD)));
				fw.WriteBytes(this_201.data(), static_cast<DWORD>(this_201.size() * sizeof(DWORD)));
				fw.Write(this_202);
			}
		}
	}
}

void MAPDATA::sub_F7D9C0(FileReader& fw)
{
	this_153 = fw.ReadDWord();
	this_154 = fw.ReadDWord();
	this_155 = fw.ReadDWord();
	this_156 = fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
		this_157 = 0;
	else
		this_157 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_158, SRPGClasses::ITEMGROUPDATA, fw);
}

void MAPDATA::sub_F7A340(FileReader& fw)
{
	if (g_ArcVersion < 0x3EE)
	{
		if (this_166)
			delete (this_166);
		this_166 = new CMenuOperation(SRPGClasses::UNITDATA);
	}
	else
		allocAndSetCMenuOp(&this_166, SRPGClasses::UNITDATA, fw);
}

void MAPDATA::sub_F77950(FileReader& fw)
{
	NOT_IMPLEMENTED
	/*
	int32_t v14[15];

	fw.ReadBytes(v14, 0x3Cu);
	for (uint32_t i = 0; i < 15; ++i)
	{
		if (v14[i] != -1)
		{
			int16_t v6 = 0;
			v12 = (**(int(__thiscall***)(int))a2)(a2);
			do
			{
				v7 = *(_DWORD*)(*(_DWORD*)(a2 + 4) + 4);
				if (!v7)
				{
LABEL_7:
					v8 = v6;
					goto LABEL_8;
				}
				while (v6 != *(unsigned __int16*)(v7 + 8))
				{
					v7 = *(_DWORD*)(v7 + 4);
					if (!v7)
						goto LABEL_7;
				}
				++v6;
			} while (v6 < 9999);
			v8 = -1;
LABEL_8:
			*(_DWORD*)(v12 + 8) = v8;
			v9 = *(_DWORD*)(a2 + 4);
			v10 = v9 + 4;
			if (*(_DWORD*)(v9 + 4))
			{
				do
				{
					v9 = *(_DWORD*)v10;
					v11 = *(_DWORD*)(*(_DWORD*)v10 + 4) == 0;
					v10 = *(_DWORD*)v10 + 4;
				} while (!v11);
			}
			result = v14[i];
			*(_DWORD*)(v9 + 4) = v12;
			*(_DWORD*)(v12 + 12) = result;
		}
	}*/
}

void MAPDATA::sub_F7A3B0(FileReader& fw)
{
	if (g_ArcVersion < 0x406)
		mapScroll = 1;
	else
		mapScroll = fw.ReadDWord();

	if (g_ArcVersion < 0x43D)
	{
		this_115 = 0;
		this_116 = -1;
	}
	else
	{
		this_115 = fw.ReadDWord();
		this_116 = fw.ReadDWord();
	}
}
