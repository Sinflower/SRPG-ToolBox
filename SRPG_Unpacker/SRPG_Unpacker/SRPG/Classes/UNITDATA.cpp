/*
 *  File: UNITDATA.cpp
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

#include "UNITDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void UNITDATA::init(FileReader& fw)
{
	this_18 = fw.ReadDWord();
	this_19 = fw.ReadDWord();
	lvl     = fw.ReadDWord();
	this_21 = fw.ReadDWord();

	item01 = fw.ReadDWord();
	item02 = fw.ReadDWord();
	item03 = fw.ReadDWord();
	item04 = fw.ReadDWord();
	item05 = fw.ReadDWord();
	item06 = fw.ReadDWord();
	item07 = fw.ReadDWord();
	item08 = fw.ReadDWord();
	item09 = fw.ReadDWord();
	item10 = fw.ReadDWord();
	item11 = fw.ReadDWord();
	item12 = fw.ReadDWord();
	item13 = fw.ReadDWord();
	item14 = fw.ReadDWord();
	item15 = fw.ReadDWord();
	item16 = fw.ReadDWord();
	item17 = fw.ReadDWord();
	item18 = fw.ReadDWord();
	item19 = fw.ReadDWord();
	item20 = fw.ReadDWord();

	this_67 = fw.ReadDWord();
	this_68 = fw.ReadDWord();
	this_69 = fw.ReadDWord();
	this_70 = fw.ReadDWord();
	this_71 = fw.ReadDWord();
	this_72 = fw.ReadDWord();
	this_73 = fw.ReadDWord();
	this_74 = fw.ReadDWord();
	this_75 = fw.ReadDWord();
	this_76 = fw.ReadDWord();

	this_65    = fw.ReadDWord();
	this_66    = fw.ReadDWord();
	this_42    = fw.ReadDWord();
	importance = fw.ReadDWord();
	this_55    = fw.ReadDWord();
	this_57    = fw.ReadDWord();

	if (g_ArcVersion < 0x429)
		this_58 = -1;
	else
		this_58 = fw.ReadWord();

	if (g_ArcVersion < 0x46B)
		this_59 = 0;
	else
		this_59 = fw.ReadDWord();

	this_56 = fw.ReadDWord();

	this_60 = fw.ReadDWord();
	this_61 = fw.ReadDWord();
	this_62 = fw.ReadDWord();
	this_63 = fw.ReadDWord();

	this_64 = fw.ReadDWord();

	sub_F7E930(fw);

	this_90  = fw.ReadDWord();
	this_91  = fw.ReadDWord();
	this_94  = fw.ReadDWord();
	this_95  = fw.ReadDWord();
	this_96  = fw.ReadDWord();
	this_97  = fw.ReadDWord();
	this_99  = fw.ReadDWord();
	this_92  = fw.ReadDWord();
	this_93  = fw.ReadDWord();
	this_100 = fw.ReadDWord();

	sub_F7E130(fw);
	sub_F7E310(fw);

	initMemData(customParameters, fw);
	allocAndSetCMenuOp(&this_81, SRPGClasses::TYPEIDDATA, fw);

	sub_F6F1D0(fw);

	allocAndSetCMenuOp(&unitEvents, SRPGClasses::EVENTDATA, fw);
	allocAndSetCMenuOp(&this_78, SRPGClasses::PATTERNDATA, fw);
	allocAndSetCMenuOp(&this_80, SRPGClasses::TYPEIDDATA, fw);
}

void UNITDATA::dump(FileWriter& fw) const
{
	fw.Write(this_18);
	fw.Write(this_19);
	fw.Write(lvl);
	fw.Write(this_21);

	fw.Write(item01);
	fw.Write(item02);
	fw.Write(item03);
	fw.Write(item04);
	fw.Write(item05);
	fw.Write(item06);
	fw.Write(item07);
	fw.Write(item08);
	fw.Write(item09);
	fw.Write(item10);
	fw.Write(item11);
	fw.Write(item12);
	fw.Write(item13);
	fw.Write(item14);
	fw.Write(item15);
	fw.Write(item16);
	fw.Write(item17);
	fw.Write(item18);
	fw.Write(item19);
	fw.Write(item20);

	fw.Write(this_67);
	fw.Write(this_68);
	fw.Write(this_69);
	fw.Write(this_70);
	fw.Write(this_71);
	fw.Write(this_72);
	fw.Write(this_73);
	fw.Write(this_74);
	fw.Write(this_75);
	fw.Write(this_76);

	fw.Write(this_65);
	fw.Write(this_66);
	fw.Write(this_42);
	fw.Write(importance);
	fw.Write(this_55);
	fw.Write(this_57);

	if (g_ArcVersion >= 0x429)
		fw.Write(this_58);

	if (g_ArcVersion >= 0x46B)
		fw.Write(this_59);

	fw.Write(this_56);
	fw.Write(this_60);
	fw.Write(this_61);
	fw.Write(this_62);
	fw.Write(this_63);
	fw.Write(this_64);

	fw.Write(icon);

	name.Write(fw);
	description.Write(fw);

	fw.Write(this_90);
	fw.Write(this_91);
	fw.Write(this_94);
	fw.Write(this_95);
	fw.Write(this_96);
	fw.Write(this_97);
	fw.Write(this_99);
	fw.Write(this_92);
	fw.Write(this_93);
	fw.Write(this_100);

	fw.Write(hp);
	fw.Write(str);
	fw.Write(mag);
	fw.Write(skl);
	fw.Write(spd);
	fw.Write(lck);
	fw.Write(def);
	fw.Write(res);
	fw.Write(mov);

	if (g_ArcVersion >= 0x418)
	{
		fw.Write(wlv);
		fw.Write(bld);
	}

	if (g_ArcVersion < 0x418)
	{
		fw.Write(grHP);
		fw.Write(grStr);
		fw.Write(grMag);
		fw.Write(grSkl);
		fw.Write(grSpd);
		fw.Write(grLck);
		fw.Write(grDef);
		fw.Write(grRes);
		fw.Write(grMov);
	}
	else
	{
		fw.Write(checkVal);
		if (!checkVal)
		{
			fw.Write(grHP);
			fw.Write(grStr);
			fw.Write(grMag);
			fw.Write(grSkl);
			fw.Write(grSpd);
			fw.Write(grLck);
			fw.Write(grDef);
			fw.Write(grRes);
			fw.Write(grMov);
			fw.Write(grWlv);
			fw.Write(grBld);
		}
	}

	customParameters.Write(fw);
	this_81->dump(fw);

	/////

	if (g_ArcVersion >= 0x3EF)
		this_82->dump(fw);

	if (g_ArcVersion >= 0x3F1)
		this_84->dump(fw);

	if (g_ArcVersion < 0x446)
	{
		NOT_IMPLEMENTED
	}
	else
		this_85->dump(fw);

	if (g_ArcVersion >= 0x491)
		this_86->dump(fw);

	if (g_ArcVersion >= 0x406)
		this_83->dump(fw);

	if (g_ArcVersion >= 0x43F)
	{
		this_87->dump(fw);
		this_88->dump(fw);
		this_89->dump(fw);
	}

	if (g_ArcVersion >= 0x4A4)
	{
		fw.Write(this_102);
		this_103.Write(fw);
	}

	if (g_ArcVersion >= 0x4A5)
		fw.Write(this_105);

	/////

	unitEvents->dump(fw);
	this_78->dump(fw);
	this_80->dump(fw);
}

void UNITDATA::sub_F7E930(FileReader& fw)
{
	icon = fw.ReadQWord();

	initMemData(name, fw);
	initMemData(description, fw);
}

void UNITDATA::sub_F7E130(FileReader& fw)
{
	hp  = fw.ReadDWord();
	str = fw.ReadDWord();
	mag = fw.ReadDWord();
	skl = fw.ReadDWord();
	spd = fw.ReadDWord();
	lck = fw.ReadDWord();
	def = fw.ReadDWord();
	res = fw.ReadDWord();
	mov = fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		wlv = 0;
		bld = 0;
	}
	else
	{
		wlv = fw.ReadDWord();
		bld = fw.ReadDWord();
	}
}

void UNITDATA::sub_F7E310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		grHP  = fw.ReadDWord();
		grStr = fw.ReadDWord();
		grMag = fw.ReadDWord();
		grSkl = fw.ReadDWord();
		grSpd = fw.ReadDWord();
		grLck = fw.ReadDWord();
		grDef = fw.ReadDWord();
		grRes = fw.ReadDWord();
		grMov = fw.ReadDWord();
		grWlv = 0;
		grBld = 0;
	}
	else
	{
		checkVal = fw.ReadDWord();
		if (checkVal)
		{
			grHP  = 0;
			grStr = 0;
			grMag = 0;
			grSkl = 0;
			grSpd = 0;
			grLck = 0;
			grDef = 0;
			grRes = 0;
			grMov = 0;
			grWlv = 0;
			grBld = 0;
		}
		else
		{
			grHP  = fw.ReadDWord();
			grStr = fw.ReadDWord();
			grMag = fw.ReadDWord();
			grSkl = fw.ReadDWord();
			grSpd = fw.ReadDWord();
			grLck = fw.ReadDWord();
			grDef = fw.ReadDWord();
			grRes = fw.ReadDWord();
			grMov = fw.ReadDWord();
			grWlv = fw.ReadDWord();
			grBld = fw.ReadDWord();
		}
	}
}

void UNITDATA::sub_F6F1D0(FileReader& fw)
{
	if (g_ArcVersion < 0x3EF)
		this_82 = new CMenuOperation(SRPGClasses::SUPPORTDATA);
	else
		allocAndSetCMenuOp(&this_82, SRPGClasses::SUPPORTDATA, fw);

	if (g_ArcVersion < 0x3F1)
		this_84 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	else
		allocAndSetCMenuOp(&this_84, SRPGClasses::IMAGEIDDATA, fw);

	if (g_ArcVersion < 0x446)
	{
		this_85 = new CMenuOperation(SRPGClasses::TYPEIDDATA);

		NOT_IMPLEMENTED

		/*if (this_65 != -1)
		{
			v5 = (*(int (__thiscall **)(_DWORD *))*this_85)(this_85);
			*(_DWORD *)(v5 + 8) = 0;
			v6 = this_85[1];
			v7 = v6 + 4;
			if ( *(_DWORD *)(v6 + 4) )
			{
				do
				{
					v6 = *(_DWORD *)v7;
					v8 = *(_DWORD *)(*(_DWORD *)v7 + 4) == 0;
					v7 = *(_DWORD *)v7 + 4;
				}
				while ( !v8 );
			}
			*(_DWORD *)(v6 + 4) = v5;
			*(_DWORD *)(v5 + 12) = v14;
		}

		v15 = this_85;
		if ( this_66 != -1 )
		{
			v10 = (**(int (__thiscall ***)(_DWORD))this_85)(this_85);
			*(_DWORD *)(v10 + 8) = 1;
			v11 = *(_DWORD *)(v15 + 4);
			v12 = v11 + 4;

			if ( *(_DWORD *)(v11 + 4) )
			{
				do
				{
					v11 = *(_DWORD *)v12;
					v8 = *(_DWORD *)(*(_DWORD *)v12 + 4) == 0;
					v12 = *(_DWORD *)v12 + 4;
				}
				while ( !v8 );
			}

			*(_DWORD *)(v11 + 4) = v10;
			*(_DWORD *)(v10 + 12) = v9;
		}*/
	}
	else
		allocAndSetCMenuOp(&this_85, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion < 0x491)
		this_86 = new CMenuOperation(SRPGClasses::REFCUTINDATA);
	else
		allocAndSetCMenuOp(&this_86, SRPGClasses::REFCUTINDATA, fw);

	if (g_ArcVersion < 0x406)
		this_83 = new CMenuOperation(SRPGClasses::NEWSKILLDATA);
	else
		allocAndSetCMenuOp(&this_83, SRPGClasses::NEWSKILLDATA, fw);

	if (g_ArcVersion < 0x43F)
	{
		this_87 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		this_88 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
		this_89 = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	}
	else
	{
		allocAndSetCMenuOp(&this_87, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&this_88, SRPGClasses::IMAGEIDDATA, fw);
		allocAndSetCMenuOp(&this_89, SRPGClasses::IMAGEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x4A4)
	{
		this_102 = fw.ReadDWord();
		initMemData(this_103, fw);
	}

	if (g_ArcVersion >= 0x4A5)
		this_105 = fw.ReadDWord();
}

void UNITDATA::print(std::ostream& os) const
{
	os << "UNITDATA" << std::endl;
	os << "HP: " << hp << std::endl;
	os << "STR: " << str << std::endl;
	os << "MAG: " << mag << std::endl;
	os << "SKL: " << skl << std::endl;
	os << "SPD: " << spd << std::endl;
	os << "LCK: " << lck << std::endl;
	os << "DEF: " << def << std::endl;
	os << "RES: " << res << std::endl;
	os << "MOV: " << mov << std::endl;
	os << "WLV: " << wlv << std::endl;
	os << "BLD: " << bld << std::endl;
	os << "Icon: " << icon << std::endl;
	os << "Name: " << name << std::endl;
	os << "Description: " << description << std::endl;
	os << "this_18: " << this_18 << std::endl;
	os << "this_19: " << this_19 << std::endl;
	os << "LVL: " << lvl << std::endl;
	os << "this_21: " << this_21 << std::endl;
	os << "Item 01: " << item01 << std::endl;
	os << "Item 02: " << item02 << std::endl;
	os << "Item 03: " << item03 << std::endl;
	os << "Item 04: " << item04 << std::endl;
	os << "Item 05: " << item05 << std::endl;
	os << "Item 06: " << item06 << std::endl;
	os << "Item 07: " << item07 << std::endl;
	os << "Item 08: " << item08 << std::endl;
	os << "Item 09: " << item09 << std::endl;
	os << "Item 10: " << item10 << std::endl;
	os << "Item 11: " << item11 << std::endl;
	os << "Item 12: " << item12 << std::endl;
	os << "Item 13: " << item13 << std::endl;
	os << "Item 14: " << item14 << std::endl;
	os << "Item 15: " << item15 << std::endl;
	os << "Item 16: " << item16 << std::endl;
	os << "Item 17: " << item17 << std::endl;
	os << "Item 18: " << item18 << std::endl;
	os << "Item 19: " << item19 << std::endl;
	os << "Item 20: " << item20 << std::endl;
	os << "this_42: " << this_42 << std::endl;
	os << "Importance: " << importance << std::endl;
	os << "Growth Rates HP: " << grHP << std::endl;
	os << "Growth Rates STR: " << grStr << std::endl;
	os << "Growth Rates MAG: " << grMag << std::endl;
	os << "Growth Rates SKL: " << grSkl << std::endl;
	os << "Growth Rates SPD: " << grSpd << std::endl;
	os << "Growth Rates LCK: " << grLck << std::endl;
	os << "Growth Rates DEF: " << grDef << std::endl;
	os << "Growth Rates RES: " << grRes << std::endl;
	os << "Growth Rates MOV: " << grMov << std::endl;
	os << "Growth Rates WLV: " << grWlv << std::endl;
	os << "Growth Rates BLD: " << grBld << std::endl;
	os << "this_55: " << this_55 << std::endl;
	os << "this_56: " << this_56 << std::endl;
	os << "this_57: " << this_57 << std::endl;
	os << "this_58: " << this_58 << std::endl;
	os << "this_59: " << this_59 << std::endl;
	os << "this_60: " << this_60 << std::endl;
	os << "this_61: " << this_61 << std::endl;
	os << "this_62: " << this_62 << std::endl;
	os << "this_63: " << this_63 << std::endl;
	os << "this_64: " << this_64 << std::endl;
	os << "this_65: " << this_65 << std::endl;
	os << "this_66: " << this_66 << std::endl;
	os << "this_67: " << this_67 << std::endl;
	os << "this_68: " << this_68 << std::endl;
	os << "this_69: " << this_69 << std::endl;
	os << "this_70: " << this_70 << std::endl;
	os << "this_71: " << this_71 << std::endl;
	os << "this_72: " << this_72 << std::endl;
	os << "this_73: " << this_73 << std::endl;
	os << "this_74: " << this_74 << std::endl;
	os << "this_75: " << this_75 << std::endl;
	os << "this_76: " << this_76 << std::endl;
	os << "CustomParameters: " << customParameters << std::endl;
	os << "this_103: " << this_103 << std::endl;
	os << "this_80: " << *this_80 << std::endl;
}

nlohmann::ordered_json UNITDATA::toJson() const
{
	nlohmann::ordered_json j;

	j["name"]        = name;
	j["description"] = description;
	unitEvents->ToJson(j, "unitEvents");

	return j;
}