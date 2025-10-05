/*
 *  File: METAMORDATA.cpp
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

#include "METAMORDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void METAMORDATA::init(FileReader& fw)
{
	this_14 = fw.ReadDWord();
	this_15 = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_17.data(), 40);
		this_17[10] = 0;
		this_17[11] = 0;
	}
	else
		fw.ReadBytes(this_17.data(), 48);

	// NOTE: Newer version contain a < 0x4F9 check and set all DWORDs == 3 to 4
	//       this probably has no meaning here but in case of errors check this
	if (g_ArcVersion < 0x418)
	{
		fw.ReadBytes(this_29.data(), 40);
		this_29[10] = 3;
		this_29[11] = 3;
	}
	else
		fw.ReadBytes(this_29.data(), 48);

	if (g_ArcVersion >= 1051)
		this_41 = fw.ReadDWord();

	this_42 = fw.ReadDWord();

	allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_42))
	{
		fw.ReadBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
		fw.ReadBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
		this_132 = fw.ReadDWord();
	}

	allocAndSetCMenuOp(&m_pItemConvertData, SRPGClasses::ITEMCONVERTDATA, fw);

	initMemData(command, fw);

	LEGENDDATA::init(fw);

	initMemData(this_45, fw);

	if (g_ArcVersion < 0x4F0)
		this_48 = 0;
	else
	{
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
		fw.ReadBytes(this_47.data(), 264);
		this_49 = fw.ReadDWord();
		this_50 = fw.ReadDWord();
		this_48 = 0;
	}
}

void METAMORDATA::dump(FileWriter& fw) const
{
	fw.Write(this_14);
	fw.Write(this_15);
	fw.Write(this_8);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_13);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_17.data(), 40);
	else
		fw.WriteBytes(this_17.data(), 48);

	if (g_ArcVersion < 0x418)
		fw.WriteBytes(this_29.data(), 40);
	else
		fw.WriteBytes(this_29.data(), 48);

	fw.Write(this_41);
	fw.Write(this_42);

	m_pTypeIDData1->dump(fw);

	if (g_ArcVersion >= 1277 && HIWORD(this_42))
	{
		fw.WriteBytes(this_130.data(), static_cast<DWORD>(this_130.size() * sizeof(DWORD)));
		fw.WriteBytes(this_131.data(), static_cast<DWORD>(this_131.size() * sizeof(DWORD)));
		fw.Write(this_132);
	}

	m_pItemConvertData->dump(fw);

	command.Write(fw);

	LEGENDDATA::dump(fw);

	this_45.Write(fw);

	if (g_ArcVersion >= 0x4F0)
	{
		m_pTypeIDData2->dump(fw);
		fw.WriteBytes(this_47.data(), 264);
		fw.Write(this_49);
		fw.Write(this_50);
	}
}

nlohmann::ordered_json METAMORDATA::toJson() const
{
	nlohmann::ordered_json j = LEGENDDATA::toJson();
	j["command"]             = command.ToString();
	return j;
}

void METAMORDATA::applyPatch(const nlohmann::ordered_json& json)
{
	LEGENDDATA::applyPatch(json);
	SET_STRING_IF_IN_JSON(json, "command", command);
}
